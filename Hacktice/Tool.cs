using System;
using System.Drawing;
using System.IO;
using System.Threading;
using System.Windows.Forms;
using System.Xml.Serialization;

namespace Hacktice
{
    public partial class Tool : Form
    {
        enum State
        {
            INVALIDATED,
            EMULATOR,
            ROM,
            HACKTICE_CORRUPTED,
            HACKTICE_INJECTED,
            HACKTICE_RUNNING,
        };

        readonly System.Threading.Timer _timer;

        // Access from '_timer' thread only
        State _stateValue = State.INVALIDATED;
        Emulator _emulator = new Emulator();
        Config _lastSeenEmulatorConfig = new Config();
        private State EmulatorState
        {
            get { return _stateValue; }
            set { var oldValue = _stateValue; _stateValue = value; if (oldValue != _stateValue) { UpdateEmulatorState(); } }
        }

        // Used from UI thread to avoid event loops
        bool _muteConfigEvents = false;

        // Whenever user wants to do anything with emulator, these vars are set
        // These are shared between UI & timer_ thread. 
        // This is incredibly ugly but I do not know other way to do it in C# as dispatch queues can do
        // Might want to use 'Interlocked' access because of multithreading, be careful
        volatile int _wantToInjectHacktice = 0;
        volatile Config _wantToUpdateConfig;
        volatile Config _config;

        private bool NeedToInjectHacktice
        {
            get { return 0 != Interlocked.Exchange(ref _wantToInjectHacktice, 0); }
        }
        private Config NeedToUpdateConfig
        {
            get { return Interlocked.Exchange(ref _wantToUpdateConfig, null); }
        }

        class MuteScope : IDisposable
        {
            Tool _tool;

            public MuteScope(Tool tool)
            {
                _tool = tool;
                _tool._muteConfigEvents = true;
            }
            public void Dispose()
            {
                _tool._muteConfigEvents = false;
            }
        }

        const string DEFAULT_CONFIG_NAME = "hacktice_config.xml";

        public Tool()
        {
            InitializeComponent();
            _timer = new System.Threading.Timer(EmulatorStateUpdate, null, 1, Timeout.Infinite);
            using (MuteScope mute = new MuteScope(this))
            {
                comboBoxStick.SelectedIndex = 0;
                comboBoxL.SelectedIndex = 0;
                comboBoxLR.SelectedIndex = 0;
                comboBoxFC.SelectedIndex = 0;
                comboBoxDpadDown.SelectedIndex = 0;
                comboBoxDpadUp.SelectedIndex = 0;
                comboBoxTimerStyle.SelectedIndex = 0;
                comboBoxStateStyle.SelectedIndex = 0;
                comboBoxDeathAction.SelectedIndex = 0;
            }

            try
            {
                var path = Path.Combine(Application.LocalUserAppDataPath, DEFAULT_CONFIG_NAME);
                var ser = new XmlSerializer(typeof(Config));
                using (var reader = new FileStream(path, FileMode.Open))
                {
                    UpdateUIFromConfig((Config)ser.Deserialize(reader));
                }
            }
            catch (Exception)
            { }

            _config = MakeConfig();
        }

        ~Tool()
        {
            _timer.Change(Timeout.Infinite, Timeout.Infinite);
            WaitHandle handle = new AutoResetEvent(false);
            _timer.Dispose(handle);
            handle.WaitOne();
            _timer.Dispose();
        }

        // Call from other thread for safe UI invoke
        private void SafeInvoke(MethodInvoker updater, bool forceSynchronous = false)
        {
            if (InvokeRequired)
            {
                if (forceSynchronous)
                {
                    Invoke((MethodInvoker)delegate { SafeInvoke(updater, forceSynchronous); });
                }
                else
                {
                    BeginInvoke((MethodInvoker)delegate { SafeInvoke(updater, forceSynchronous); });
                }
            }
            else
            {
                if (IsDisposed)
                {
                    throw new ObjectDisposedException("Control is already disposed.");
                }

                updater();
            }
        }

        private string GetHackticeName()
        {
            try 
            {
                var version = _emulator.ReadVersion();
                return $"hacktice v{version}";
            }
            catch (Exception)
            {
                return "hacktice";
            }
        }

        private string GetStateString()
        {
            switch (_stateValue)
            {
                case State.INVALIDATED:
                    return "No supported emulator is running.";
                case State.EMULATOR:
                    return "Emulator is running but no running ROM found";
                case State.ROM:
                    return "ROM is found but hacktice is not injected.\nUse 'Inject in Emulator' button";
                case State.HACKTICE_CORRUPTED:
                    var version = _emulator.ReadVersion();
                    return $"{GetHackticeName()} is found but it is in unknown state.\nReset emulator and try injecting again";
                case State.HACKTICE_INJECTED:
                    return $"{GetHackticeName()} payload is found but it is inactive.\nMake a savestate and load it";
                case State.HACKTICE_RUNNING:
                    return $"{ GetHackticeName()} is running";
            }

            return "Corrupted";
        }

        private Color GetStateColor()
        {
            switch (_stateValue)
            {
                case State.INVALIDATED:
                    return Color.DarkGray;
                case State.EMULATOR:
                    return Color.MediumPurple;
                case State.ROM:
                    return Color.DarkKhaki;
                case State.HACKTICE_CORRUPTED:
                    return Color.IndianRed;
                case State.HACKTICE_INJECTED:
                    return Color.Yellow;
                case State.HACKTICE_RUNNING:
                    return Color.Green;
            }

            return Color.Red;
        }

        private void UpdateEmulatorState()
        {
            var state = GetStateString();
            var color = GetStateColor();
            bool canUseConfig = _stateValue == State.HACKTICE_RUNNING;
            bool canInjectInEmu = _stateValue >= State.ROM;
            var version = new Version(1, 0, 0);
            if (!canUseConfig)
            {
                _lastSeenEmulatorConfig = null;
            }
            else
            {
                try
                {
                    version = _emulator.ReadVersion();
                }
                catch (Exception)
                { }
            }

            SafeInvoke(delegate {
                pictureBoxState.BackColor = color;
                labelEmulatorState.Text = state;
                groupBoxConfig.Enabled = canUseConfig;
                buttonInjectInEmulator.Enabled = canInjectInEmu;

                checkBoxWarpWheel.Enabled = version >= new Version(1, 3, 3);
                comboBoxDpadUp.Enabled = version >= new Version(1, 3, 3);

                if (canUseConfig)
                {
                    labelInfo.Text = "Config files can be saved and loaded as necessary.\nShown config is synchronized with a running emulator.";
                }
                else
                {
                    labelInfo.Text = "Welcome to hacktice control!In order to use the tool, either a payload\nneeds to be injected in the emulator or patched ROM needs to be created.";
                }
            });
        }

        private void InjectHacktice()
        {
            _emulator.WriteToEmulator(0x7f2000, Resource.data);
            XmlPatches patches = new XmlPatches();
            foreach (var patch in patches)
            {
                // Ignore code that copies from ROM to RAM
                if (patch.Offset == 0x396c || patch.Offset == 0x7f1200)
                    continue;

                _emulator.WriteToEmulator((uint)patch.Offset, patch.Data);
            }
        }

        private void PrepareHacktice()
        {
            // 0C0134C0 00000000
            State newState = State.ROM;
            try
            {
                {
                    int val = _emulator.ReadHackticeCanary();
                    if (val != 0x484B5443)
                    {
                        return;
                    }
                }
                {
                    long val = _emulator.ReadOnFrameHook();
                    if (val != 0x000000000c0134c0)
                    {
                        return;
                    }
                }

                newState = State.HACKTICE_CORRUPTED;
                {
                    int val = _emulator.ReadHackticeStatus();
                    if (val == 0x494E4954)
                    {
                        newState = State.HACKTICE_INJECTED;
                        return;
                    }
                    if (val == 0x41435456)
                    {
                        newState = State.HACKTICE_RUNNING;
                        return;
                    }
                }
            }
            finally
            {
                EmulatorState = newState;
            }
        }

        private bool IsEmulatorReady()
        {
            return EmulatorState >= State.ROM && _emulator.Ok();
        }

        private void EmulatorStateUpdate(object state)
        {
            try
            {
                bool injectHacktice = NeedToInjectHacktice;
                if (!IsEmulatorReady())
                {
                    var res = _emulator.Prepare();
                    switch (res)
                    {
                        case Emulator.PrepareResult.NOT_FOUND:
                            EmulatorState = State.INVALIDATED;
                            break;
                        case Emulator.PrepareResult.ONLY_EMULATOR:
                            EmulatorState = State.EMULATOR;
                            break;
                        case Emulator.PrepareResult.OK:
                            EmulatorState = State.ROM;
                            break;
                    }
                }

                if (EmulatorState >= State.ROM)
                {
                    if (injectHacktice)
                        InjectHacktice();

                    PrepareHacktice();
                }

                if (EmulatorState == State.HACKTICE_RUNNING)
                {
                    var userUpdatedConfig = NeedToUpdateConfig;

                    // TODO: This logic gets complicated, separate this away
                    // the first time emulator is good
                    if (!(_lastSeenEmulatorConfig is object))
                    {
                        // we are replacing emu configs, so use stuff we have even if user did not change anything
                        userUpdatedConfig = _config;
                    }

                    if (userUpdatedConfig is object)
                    {
                        _lastSeenEmulatorConfig = userUpdatedConfig;
                        _emulator.Write(userUpdatedConfig);
                    }

                    var currentEmuConfig = _emulator.ReadConfig();
                    if (!_lastSeenEmulatorConfig.Equals(currentEmuConfig))
                    {
                        SafeInvoke(delegate {
                            UpdateUIFromConfig(currentEmuConfig);
                        });
                        _lastSeenEmulatorConfig = currentEmuConfig;
                    }
                }
            }
            catch (Exception)
            {
                EmulatorState = State.INVALIDATED;
            }

            _timer.Change(IsEmulatorReady() ? 30 : 1000, Timeout.Infinite);
        }

        private void buttonPatch_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog
            {
                Filter = "ROMs (*.z64)|*.z64|All files (*.*)|*.*",
                FilterIndex = 1,
            };

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    Patcher patcher = new Patcher(openFileDialog.FileName);
                    patcher.Apply();
                    MessageBox.Show("Patch applied successfully!", "hacktice", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                catch (Exception)
                {
                    MessageBox.Show("Failed to patch!", "hacktice", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
            }
        }

        private int FindHackticeConfigPosition(byte[] payload)
        {
            // The main payload has part that is constant and part that is in the end and has 'HCFG' magic in it
            // round to 4, most likely it is unnecessary but just in case
            int off = payload.Length - (payload.Length % 4) - 4;
            while (off != 0)
            {
                if (payload[off] == 'H' && payload[off + 1] == 'C' && payload[off + 2] == 'F' && payload[off + 3] == 'G')
                {
                    return off;
                }

                off -= 4;
            }

            throw new ArgumentException("Failed to find Hacktice config in the payload");
        }

        // Unused currently
        private void buttonGSCode_Click(object sender, EventArgs e)
        {
            GameSharkCodeGenerator generator;
            generator = new GameSharkCodeGenerator();

            XmlPatches patches = new XmlPatches();
            foreach (var patch in patches)
            {
                // Ignore code that copies from ROM to RAM
                if (patch.Offset == 0x396c || patch.Offset == 0x7f1200)
                    continue;

                generator.Add((uint)patch.Offset, patch.Data, 0, patch.Data.Length, true);
            }

            int hcfgOff = FindHackticeConfigPosition(Resource.data);
            generator.Add(0x7f2000, Resource.data, 0, hcfgOff, true);
            generator.Add(0x7f2000 + (uint) hcfgOff, Resource.data, hcfgOff, Resource.data.Length - hcfgOff, false);
        }

        private void buttonInjectInEmulator_Click(object sender, EventArgs e)
        {
            _wantToInjectHacktice = 1;
            _timer.Change(0 /*now*/, Timeout.Infinite);
        }

        private Config MakeConfig()
        {
            return new Config
            {
                speed = Convert.ToByte(checkBoxShowSpeed.Checked),
                stickStyle = (byte)comboBoxStick.SelectedIndex,
                showButtons = Convert.ToByte(checkBoxButtons.Checked),
                lAction = (byte)comboBoxL.SelectedIndex,
                lRAction = (byte)comboBoxLR.SelectedIndex,
                cButtonsAction = (byte)comboBoxFC.SelectedIndex,
                dpadDownAction = (byte)comboBoxDpadDown.SelectedIndex,
                dpadUpAction = (byte)comboBoxDpadUp.SelectedIndex,
                wallkickFrame = Convert.ToByte(checkBoxWKFrame.Checked),
                distanceFromClosestRed = Convert.ToByte(checkBoxDistanceToRedCoin.Checked),
                distanceFromClosestSecret = Convert.ToByte(checkBoxDistanceToSecret.Checked),
                distanceFromClosestPiranha = 0,
                distanceFromClosestPanel = 0,
                timerShow = Convert.ToByte(checkBoxShowTimer.Checked),
                timerStyle = (byte)comboBoxTimerStyle.SelectedIndex,
                timerStopOnCoinStar = Convert.ToByte(checkBoxStopTimer100s.Checked),
                stateSaveStyle = (byte)comboBoxStateStyle.SelectedIndex,
                muteMusic = Convert.ToByte(checkBoxMuteMusic.Checked),
                deathAction = (byte)comboBoxDeathAction.SelectedIndex,
                warpWheel = Convert.ToByte(checkBoxWarpWheel.Checked),

                checkpointWallkick = Convert.ToByte(checkBoxMTWallkick.Checked),
                checkpointDoor = Convert.ToByte(checkBoxMTDoor.Checked),
                checkpointPole = Convert.ToByte(checkBoxMTPole.Checked),
                checkpointLava = Convert.ToByte(checkBoxMTLava.Checked),
                checkpointGroundpound = Convert.ToByte(checkBoxMTGroundpound.Checked),
                checkpointBurning = Convert.ToByte(checkBoxMTBurning.Checked),
                checkpointCannon = Convert.ToByte(checkBoxMTCannon.Checked),
                checkpointWarp = Convert.ToByte(checkBoxMTWarp.Checked),
                checkpointRed = Convert.ToByte(checkBoxMTRed.Checked),
                checkpointCoin = Convert.ToByte(checkBoxMTCoin.Checked),
                checkpointObject = Convert.ToByte(checkBoxMTObject.Checked),
                checkpointPlatform = Convert.ToByte(checkBoxMTPlatform.Checked)
            };
        }

        private void UpdateUIFromConfig(Config config)
        {
            using (MuteScope mute = new MuteScope(this))
            {
                checkBoxShowSpeed.Checked = 0 != config.speed;
                comboBoxStick.SelectedIndex = config.stickStyle;
                checkBoxButtons.Checked = 0 != config.showButtons;
                comboBoxL.SelectedIndex = config.lAction;
                comboBoxLR.SelectedIndex = config.lRAction;
                comboBoxFC.SelectedIndex = config.cButtonsAction;
                comboBoxDpadDown.SelectedIndex = config.dpadDownAction;
                comboBoxDpadUp.SelectedIndex = config.dpadUpAction;
                checkBoxWKFrame.Checked = 0 != config.wallkickFrame;
                checkBoxDistanceToRedCoin.Checked = 0 != config.distanceFromClosestRed;
                checkBoxDistanceToSecret.Checked = 0 != config.distanceFromClosestSecret;
                checkBoxShowTimer.Checked = 0 != config.timerShow;
                comboBoxTimerStyle.SelectedIndex = config.timerStyle;
                checkBoxStopTimer100s.Checked = 0 != config.timerStopOnCoinStar;
                comboBoxStateStyle.SelectedIndex = config.stateSaveStyle;
                checkBoxMuteMusic.Checked = 0 != config.muteMusic;
                comboBoxDeathAction.SelectedIndex = config.deathAction;
                checkBoxWarpWheel.Checked = 0 != config.warpWheel;

                checkBoxMTWallkick.Checked = 0 != config.checkpointWallkick;
                checkBoxMTDoor.Checked = 0 != config.checkpointDoor;
                checkBoxMTPole.Checked = 0 != config.checkpointPole;
                checkBoxMTLava.Checked = 0 != config.checkpointLava;
                checkBoxMTGroundpound.Checked = 0 != config.checkpointGroundpound;
                checkBoxMTBurning.Checked = 0 != config.checkpointBurning;
                checkBoxMTCannon.Checked = 0 != config.checkpointCannon;
                checkBoxMTWarp.Checked = 0 != config.checkpointWarp;
                checkBoxMTRed.Checked = 0 != config.checkpointRed;
                checkBoxMTCoin.Checked = 0 != config.checkpointCoin;
                checkBoxMTObject.Checked = 0 != config.checkpointObject;
                checkBoxMTPlatform.Checked = 0 != config.checkpointPlatform;
            }
        }

        private void UpdateConfig(Config config)
        {
            UpdateUIFromConfig(config);
            _wantToUpdateConfig = config;
            _config = config;
            _timer.Change(0 /*now*/, Timeout.Infinite);
        }

        private void buttonSaveConfig_Click(object sender, EventArgs e)
        {
            SaveFileDialog sfd = new SaveFileDialog
            {
                Filter = "XML files (*.xml)|*.xml|All files (*.*)|*.*",
                FilterIndex = 1,
                RestoreDirectory = true,
                FileName = DEFAULT_CONFIG_NAME
            };

            if (sfd.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    XmlSerializer ser = new XmlSerializer(typeof(Config));
                    using (var writer = new FileStream(sfd.FileName, FileMode.Create))
                    {
                        ser.Serialize(writer, MakeConfig());
                    }

                    MessageBox.Show("Config was saved successfully!", "hacktice", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                catch(Exception)
                {
                    MessageBox.Show("Failed to save config file!", "hacktice", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        private void buttonLoadConfig_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog
            {
                Filter = "XML files (*.xml)|*.xml|All files (*.*)|*.*",
                FilterIndex = 1,
                RestoreDirectory = true,
            };

            if (ofd.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    XmlSerializer ser = new XmlSerializer(typeof(Config));
                    using (var reader = ofd.OpenFile())
                    {
                        UpdateConfig((Config)ser.Deserialize(reader));
                    }

                    MessageBox.Show("Config was loaded successfully!", "hacktice", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                catch (Exception)
                {
                    MessageBox.Show("Failed to load config file!", "hacktice", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        private void Config_CheckedChanged(object sender, EventArgs e)
        {
            if (_muteConfigEvents)
                return;

            var config = MakeConfig();
            _wantToUpdateConfig = config;
            _config = config;
            _timer.Change(0 /*now*/, Timeout.Infinite);
        }

        private void buttonSetDefault_Click(object sender, EventArgs e)
        {
            try
            {
                var path = Path.Combine(Application.LocalUserAppDataPath, DEFAULT_CONFIG_NAME);
                var ser = new XmlSerializer(typeof(Config));
                using (var writer = new FileStream(path, FileMode.Create))
                {
                    ser.Serialize(writer, MakeConfig());
                }

                MessageBox.Show("Config was saved successfully!", "hacktice", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception)
            {
                MessageBox.Show("Failed to save config file!", "hacktice", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private Config GetDefaultConfig()
        {
            return new Config{ timerShow = 1 };
        }

        private void buttonReset_Click(object sender, EventArgs e)
        {
            UpdateConfig(GetDefaultConfig());
        }
    }
}
