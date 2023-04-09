namespace Hacktice
{
    partial class Tool
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Tool));
            this.buttonPatch = new System.Windows.Forms.Button();
            this.labelEmulatorState = new System.Windows.Forms.Label();
            this.pictureBoxState = new System.Windows.Forms.PictureBox();
            this.buttonInjectInEmulator = new System.Windows.Forms.Button();
            this.checkBoxShowSpeed = new System.Windows.Forms.CheckBox();
            this.groupBoxInject = new System.Windows.Forms.GroupBox();
            this.labelDescInject = new System.Windows.Forms.Label();
            this.groupBoxConfig = new System.Windows.Forms.GroupBox();
            this.textBoxCustomText = new System.Windows.Forms.TextBox();
            this.checkBoxShowCustomText = new System.Windows.Forms.CheckBox();
            this.checkBoxSoftReset = new System.Windows.Forms.CheckBox();
            this.checkBoxWarpWheel = new System.Windows.Forms.CheckBox();
            this.comboBoxDpadUp = new System.Windows.Forms.ComboBox();
            this.labelDPadUpAction = new System.Windows.Forms.Label();
            this.buttonReset = new System.Windows.Forms.Button();
            this.buttonSetDefault = new System.Windows.Forms.Button();
            this.labelExpl = new System.Windows.Forms.Label();
            this.labelTimerStopOn = new System.Windows.Forms.Label();
            this.buttonLoadConfig = new System.Windows.Forms.Button();
            this.buttonSaveConfig = new System.Windows.Forms.Button();
            this.groupBoxMiscTimer = new System.Windows.Forms.GroupBox();
            this.checkBoxMTPlatform = new System.Windows.Forms.CheckBox();
            this.checkBoxMTObject = new System.Windows.Forms.CheckBox();
            this.checkBoxMTCoin = new System.Windows.Forms.CheckBox();
            this.checkBoxMTRed = new System.Windows.Forms.CheckBox();
            this.checkBoxMTWarp = new System.Windows.Forms.CheckBox();
            this.checkBoxMTCannon = new System.Windows.Forms.CheckBox();
            this.checkBoxMTBurning = new System.Windows.Forms.CheckBox();
            this.checkBoxMTGroundpound = new System.Windows.Forms.CheckBox();
            this.checkBoxMTLava = new System.Windows.Forms.CheckBox();
            this.checkBoxMTPole = new System.Windows.Forms.CheckBox();
            this.checkBoxMTDoor = new System.Windows.Forms.CheckBox();
            this.checkBoxMTWallkick = new System.Windows.Forms.CheckBox();
            this.labelDeathAction = new System.Windows.Forms.Label();
            this.comboBoxDeathAction = new System.Windows.Forms.ComboBox();
            this.checkBoxMuteMusic = new System.Windows.Forms.CheckBox();
            this.labelStateCond = new System.Windows.Forms.Label();
            this.comboBoxStateStyle = new System.Windows.Forms.ComboBox();
            this.checkBoxStopTimer100s = new System.Windows.Forms.CheckBox();
            this.comboBoxTimerStyle = new System.Windows.Forms.ComboBox();
            this.checkBoxShowTimer = new System.Windows.Forms.CheckBox();
            this.checkBoxDistanceToSecret = new System.Windows.Forms.CheckBox();
            this.checkBoxDistanceToRedCoin = new System.Windows.Forms.CheckBox();
            this.checkBoxWKFrame = new System.Windows.Forms.CheckBox();
            this.comboBoxDpadDown = new System.Windows.Forms.ComboBox();
            this.labelDPadDown = new System.Windows.Forms.Label();
            this.comboBoxFC = new System.Windows.Forms.ComboBox();
            this.label4C = new System.Windows.Forms.Label();
            this.comboBoxLR = new System.Windows.Forms.ComboBox();
            this.labelLR = new System.Windows.Forms.Label();
            this.comboBoxL = new System.Windows.Forms.ComboBox();
            this.labelLButtonAction = new System.Windows.Forms.Label();
            this.checkBoxButtons = new System.Windows.Forms.CheckBox();
            this.comboBoxStick = new System.Windows.Forms.ComboBox();
            this.groupBoxROM = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.labelROM = new System.Windows.Forms.Label();
            this.labelInfo = new System.Windows.Forms.Label();
            this.toolTip = new System.Windows.Forms.ToolTip(this.components);
            this.checkBoxShowCollision = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxState)).BeginInit();
            this.groupBoxInject.SuspendLayout();
            this.groupBoxConfig.SuspendLayout();
            this.groupBoxMiscTimer.SuspendLayout();
            this.groupBoxROM.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonPatch
            // 
            this.buttonPatch.Location = new System.Drawing.Point(14, 58);
            this.buttonPatch.Name = "buttonPatch";
            this.buttonPatch.Size = new System.Drawing.Size(110, 23);
            this.buttonPatch.TabIndex = 0;
            this.buttonPatch.Text = "Patch ROM";
            this.buttonPatch.UseVisualStyleBackColor = true;
            this.buttonPatch.Click += new System.EventHandler(this.buttonPatch_Click);
            // 
            // labelEmulatorState
            // 
            this.labelEmulatorState.AutoSize = true;
            this.labelEmulatorState.Location = new System.Drawing.Point(22, 48);
            this.labelEmulatorState.Name = "labelEmulatorState";
            this.labelEmulatorState.Size = new System.Drawing.Size(165, 13);
            this.labelEmulatorState.TabIndex = 3;
            this.labelEmulatorState.Text = "No supported emulator is running.";
            // 
            // pictureBoxState
            // 
            this.pictureBoxState.BackColor = System.Drawing.SystemColors.ControlDark;
            this.pictureBoxState.Location = new System.Drawing.Point(9, 48);
            this.pictureBoxState.Name = "pictureBoxState";
            this.pictureBoxState.Size = new System.Drawing.Size(10, 13);
            this.pictureBoxState.TabIndex = 4;
            this.pictureBoxState.TabStop = false;
            // 
            // buttonInjectInEmulator
            // 
            this.buttonInjectInEmulator.Enabled = false;
            this.buttonInjectInEmulator.Location = new System.Drawing.Point(6, 19);
            this.buttonInjectInEmulator.Name = "buttonInjectInEmulator";
            this.buttonInjectInEmulator.Size = new System.Drawing.Size(123, 23);
            this.buttonInjectInEmulator.TabIndex = 5;
            this.buttonInjectInEmulator.Text = "Inject in Emulator";
            this.buttonInjectInEmulator.UseVisualStyleBackColor = true;
            this.buttonInjectInEmulator.Click += new System.EventHandler(this.buttonInjectInEmulator_Click);
            // 
            // checkBoxShowSpeed
            // 
            this.checkBoxShowSpeed.AutoSize = true;
            this.checkBoxShowSpeed.Location = new System.Drawing.Point(6, 19);
            this.checkBoxShowSpeed.Name = "checkBoxShowSpeed";
            this.checkBoxShowSpeed.Size = new System.Drawing.Size(85, 17);
            this.checkBoxShowSpeed.TabIndex = 6;
            this.checkBoxShowSpeed.Text = "Show speed";
            this.toolTip.SetToolTip(this.checkBoxShowSpeed, "Displays Mario speed. SPEED option in game.");
            this.checkBoxShowSpeed.UseVisualStyleBackColor = true;
            this.checkBoxShowSpeed.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // groupBoxInject
            // 
            this.groupBoxInject.Controls.Add(this.labelDescInject);
            this.groupBoxInject.Controls.Add(this.buttonInjectInEmulator);
            this.groupBoxInject.Controls.Add(this.labelEmulatorState);
            this.groupBoxInject.Controls.Add(this.pictureBoxState);
            this.groupBoxInject.Location = new System.Drawing.Point(13, 42);
            this.groupBoxInject.Name = "groupBoxInject";
            this.groupBoxInject.Size = new System.Drawing.Size(338, 90);
            this.groupBoxInject.TabIndex = 7;
            this.groupBoxInject.TabStop = false;
            this.groupBoxInject.Text = "Emulator";
            // 
            // labelDescInject
            // 
            this.labelDescInject.AutoSize = true;
            this.labelDescInject.Location = new System.Drawing.Point(135, 24);
            this.labelDescInject.Name = "labelDescInject";
            this.labelDescInject.Size = new System.Drawing.Size(185, 13);
            this.labelDescInject.TabIndex = 6;
            this.labelDescInject.Text = "Run clean ROM for Emulator injection";
            // 
            // groupBoxConfig
            // 
            this.groupBoxConfig.Controls.Add(this.checkBoxShowCollision);
            this.groupBoxConfig.Controls.Add(this.textBoxCustomText);
            this.groupBoxConfig.Controls.Add(this.checkBoxShowCustomText);
            this.groupBoxConfig.Controls.Add(this.checkBoxSoftReset);
            this.groupBoxConfig.Controls.Add(this.checkBoxWarpWheel);
            this.groupBoxConfig.Controls.Add(this.comboBoxDpadUp);
            this.groupBoxConfig.Controls.Add(this.labelDPadUpAction);
            this.groupBoxConfig.Controls.Add(this.buttonReset);
            this.groupBoxConfig.Controls.Add(this.buttonSetDefault);
            this.groupBoxConfig.Controls.Add(this.labelExpl);
            this.groupBoxConfig.Controls.Add(this.labelTimerStopOn);
            this.groupBoxConfig.Controls.Add(this.buttonLoadConfig);
            this.groupBoxConfig.Controls.Add(this.buttonSaveConfig);
            this.groupBoxConfig.Controls.Add(this.groupBoxMiscTimer);
            this.groupBoxConfig.Controls.Add(this.labelDeathAction);
            this.groupBoxConfig.Controls.Add(this.comboBoxDeathAction);
            this.groupBoxConfig.Controls.Add(this.checkBoxMuteMusic);
            this.groupBoxConfig.Controls.Add(this.labelStateCond);
            this.groupBoxConfig.Controls.Add(this.comboBoxStateStyle);
            this.groupBoxConfig.Controls.Add(this.checkBoxStopTimer100s);
            this.groupBoxConfig.Controls.Add(this.comboBoxTimerStyle);
            this.groupBoxConfig.Controls.Add(this.checkBoxShowTimer);
            this.groupBoxConfig.Controls.Add(this.checkBoxDistanceToSecret);
            this.groupBoxConfig.Controls.Add(this.checkBoxDistanceToRedCoin);
            this.groupBoxConfig.Controls.Add(this.checkBoxWKFrame);
            this.groupBoxConfig.Controls.Add(this.comboBoxDpadDown);
            this.groupBoxConfig.Controls.Add(this.labelDPadDown);
            this.groupBoxConfig.Controls.Add(this.comboBoxFC);
            this.groupBoxConfig.Controls.Add(this.label4C);
            this.groupBoxConfig.Controls.Add(this.comboBoxLR);
            this.groupBoxConfig.Controls.Add(this.labelLR);
            this.groupBoxConfig.Controls.Add(this.comboBoxL);
            this.groupBoxConfig.Controls.Add(this.labelLButtonAction);
            this.groupBoxConfig.Controls.Add(this.checkBoxButtons);
            this.groupBoxConfig.Controls.Add(this.comboBoxStick);
            this.groupBoxConfig.Controls.Add(this.checkBoxShowSpeed);
            this.groupBoxConfig.Location = new System.Drawing.Point(13, 138);
            this.groupBoxConfig.Name = "groupBoxConfig";
            this.groupBoxConfig.Size = new System.Drawing.Size(483, 444);
            this.groupBoxConfig.TabIndex = 8;
            this.groupBoxConfig.TabStop = false;
            this.groupBoxConfig.Text = "Config";
            // 
            // textBoxCustomText
            // 
            this.textBoxCustomText.Location = new System.Drawing.Point(122, 336);
            this.textBoxCustomText.Name = "textBoxCustomText";
            this.textBoxCustomText.Size = new System.Drawing.Size(198, 20);
            this.textBoxCustomText.TabIndex = 38;
            this.textBoxCustomText.Text = "PRACTICE";
            this.textBoxCustomText.TextChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxShowCustomText
            // 
            this.checkBoxShowCustomText.AutoSize = true;
            this.checkBoxShowCustomText.Location = new System.Drawing.Point(6, 338);
            this.checkBoxShowCustomText.Name = "checkBoxShowCustomText";
            this.checkBoxShowCustomText.Size = new System.Drawing.Size(110, 17);
            this.checkBoxShowCustomText.TabIndex = 37;
            this.checkBoxShowCustomText.Text = "Show custom text";
            this.toolTip.SetToolTip(this.checkBoxShowCustomText, "Displays distance to reds. D TO RED in game.");
            this.checkBoxShowCustomText.UseVisualStyleBackColor = true;
            this.checkBoxShowCustomText.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxSoftReset
            // 
            this.checkBoxSoftReset.AutoSize = true;
            this.checkBoxSoftReset.Location = new System.Drawing.Point(6, 234);
            this.checkBoxSoftReset.Name = "checkBoxSoftReset";
            this.checkBoxSoftReset.Size = new System.Drawing.Size(113, 17);
            this.checkBoxSoftReset.TabIndex = 36;
            this.checkBoxSoftReset.Text = "Z+L for Soft Reset";
            this.toolTip.SetToolTip(this.checkBoxSoftReset, "Enables warp wheel to select the warp target using control stick rotation. WARP W" +
        "HEEL in game.");
            this.checkBoxSoftReset.UseVisualStyleBackColor = true;
            this.checkBoxSoftReset.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxWarpWheel
            // 
            this.checkBoxWarpWheel.AutoSize = true;
            this.checkBoxWarpWheel.Location = new System.Drawing.Point(6, 211);
            this.checkBoxWarpWheel.Name = "checkBoxWarpWheel";
            this.checkBoxWarpWheel.Size = new System.Drawing.Size(136, 17);
            this.checkBoxWarpWheel.TabIndex = 35;
            this.checkBoxWarpWheel.Text = "Warp wheel using stick";
            this.toolTip.SetToolTip(this.checkBoxWarpWheel, "Enables warp wheel to select the warp target using control stick rotation. WARP W" +
        "HEEL in game.");
            this.checkBoxWarpWheel.UseVisualStyleBackColor = true;
            this.checkBoxWarpWheel.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // comboBoxDpadUp
            // 
            this.comboBoxDpadUp.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxDpadUp.FormattingEnabled = true;
            this.comboBoxDpadUp.Items.AddRange(new object[] {
            "Off",
            "Act Select",
            "Level Reset",
            "Start Reset",
            "Levitate",
            "Load State"});
            this.comboBoxDpadUp.Location = new System.Drawing.Point(199, 210);
            this.comboBoxDpadUp.Name = "comboBoxDpadUp";
            this.comboBoxDpadUp.Size = new System.Drawing.Size(121, 21);
            this.comboBoxDpadUp.TabIndex = 34;
            this.toolTip.SetToolTip(this.comboBoxDpadUp, "Changes action on pressing DPad Up button. D UP ACTION in game.");
            this.comboBoxDpadUp.SelectionChangeCommitted += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // labelDPadUpAction
            // 
            this.labelDPadUpAction.AutoSize = true;
            this.labelDPadUpAction.Location = new System.Drawing.Point(196, 194);
            this.labelDPadUpAction.Name = "labelDPadUpAction";
            this.labelDPadUpAction.Size = new System.Drawing.Size(116, 13);
            this.labelDPadUpAction.TabIndex = 33;
            this.labelDPadUpAction.Text = "DPad Up button action";
            // 
            // buttonReset
            // 
            this.buttonReset.Location = new System.Drawing.Point(264, 408);
            this.buttonReset.Name = "buttonReset";
            this.buttonReset.Size = new System.Drawing.Size(80, 23);
            this.buttonReset.TabIndex = 32;
            this.buttonReset.Text = "Reset config";
            this.buttonReset.UseVisualStyleBackColor = true;
            this.buttonReset.Click += new System.EventHandler(this.buttonReset_Click);
            // 
            // buttonSetDefault
            // 
            this.buttonSetDefault.Location = new System.Drawing.Point(178, 408);
            this.buttonSetDefault.Name = "buttonSetDefault";
            this.buttonSetDefault.Size = new System.Drawing.Size(80, 23);
            this.buttonSetDefault.TabIndex = 31;
            this.buttonSetDefault.Text = "Set default";
            this.buttonSetDefault.UseVisualStyleBackColor = true;
            this.buttonSetDefault.Click += new System.EventHandler(this.buttonSetDefault_Click);
            // 
            // labelExpl
            // 
            this.labelExpl.AutoSize = true;
            this.labelExpl.Location = new System.Drawing.Point(307, 23);
            this.labelExpl.Name = "labelExpl";
            this.labelExpl.Size = new System.Drawing.Size(13, 13);
            this.labelExpl.TabIndex = 30;
            this.labelExpl.Text = "?";
            this.toolTip.SetToolTip(this.labelExpl, resources.GetString("labelExpl.ToolTip"));
            // 
            // labelTimerStopOn
            // 
            this.labelTimerStopOn.AutoSize = true;
            this.labelTimerStopOn.Location = new System.Drawing.Point(6, 141);
            this.labelTimerStopOn.Name = "labelTimerStopOn";
            this.labelTimerStopOn.Size = new System.Drawing.Size(71, 13);
            this.labelTimerStopOn.TabIndex = 7;
            this.labelTimerStopOn.Text = "Timer stop on";
            // 
            // buttonLoadConfig
            // 
            this.buttonLoadConfig.Location = new System.Drawing.Point(92, 408);
            this.buttonLoadConfig.Name = "buttonLoadConfig";
            this.buttonLoadConfig.Size = new System.Drawing.Size(80, 23);
            this.buttonLoadConfig.TabIndex = 29;
            this.buttonLoadConfig.Text = "Load config";
            this.buttonLoadConfig.UseVisualStyleBackColor = true;
            this.buttonLoadConfig.Click += new System.EventHandler(this.buttonLoadConfig_Click);
            // 
            // buttonSaveConfig
            // 
            this.buttonSaveConfig.Location = new System.Drawing.Point(6, 408);
            this.buttonSaveConfig.Name = "buttonSaveConfig";
            this.buttonSaveConfig.Size = new System.Drawing.Size(80, 23);
            this.buttonSaveConfig.TabIndex = 6;
            this.buttonSaveConfig.Text = "Save config";
            this.buttonSaveConfig.UseVisualStyleBackColor = true;
            this.buttonSaveConfig.Click += new System.EventHandler(this.buttonSaveConfig_Click);
            // 
            // groupBoxMiscTimer
            // 
            this.groupBoxMiscTimer.Controls.Add(this.checkBoxMTPlatform);
            this.groupBoxMiscTimer.Controls.Add(this.checkBoxMTObject);
            this.groupBoxMiscTimer.Controls.Add(this.checkBoxMTCoin);
            this.groupBoxMiscTimer.Controls.Add(this.checkBoxMTRed);
            this.groupBoxMiscTimer.Controls.Add(this.checkBoxMTWarp);
            this.groupBoxMiscTimer.Controls.Add(this.checkBoxMTCannon);
            this.groupBoxMiscTimer.Controls.Add(this.checkBoxMTBurning);
            this.groupBoxMiscTimer.Controls.Add(this.checkBoxMTGroundpound);
            this.groupBoxMiscTimer.Controls.Add(this.checkBoxMTLava);
            this.groupBoxMiscTimer.Controls.Add(this.checkBoxMTPole);
            this.groupBoxMiscTimer.Controls.Add(this.checkBoxMTDoor);
            this.groupBoxMiscTimer.Controls.Add(this.checkBoxMTWallkick);
            this.groupBoxMiscTimer.Location = new System.Drawing.Point(339, 19);
            this.groupBoxMiscTimer.Name = "groupBoxMiscTimer";
            this.groupBoxMiscTimer.Size = new System.Drawing.Size(138, 295);
            this.groupBoxMiscTimer.TabIndex = 28;
            this.groupBoxMiscTimer.TabStop = false;
            this.groupBoxMiscTimer.Text = "Miscellaneous Timer";
            this.toolTip.SetToolTip(this.groupBoxMiscTimer, "Timers that trigger on a particular event happening in game.");
            // 
            // checkBoxMTPlatform
            // 
            this.checkBoxMTPlatform.AutoSize = true;
            this.checkBoxMTPlatform.Location = new System.Drawing.Point(5, 272);
            this.checkBoxMTPlatform.Name = "checkBoxMTPlatform";
            this.checkBoxMTPlatform.Size = new System.Drawing.Size(64, 17);
            this.checkBoxMTPlatform.TabIndex = 40;
            this.checkBoxMTPlatform.Text = "Platform";
            this.checkBoxMTPlatform.UseVisualStyleBackColor = true;
            this.checkBoxMTPlatform.Enter += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxMTObject
            // 
            this.checkBoxMTObject.AutoSize = true;
            this.checkBoxMTObject.Location = new System.Drawing.Point(6, 249);
            this.checkBoxMTObject.Name = "checkBoxMTObject";
            this.checkBoxMTObject.Size = new System.Drawing.Size(76, 17);
            this.checkBoxMTObject.TabIndex = 39;
            this.checkBoxMTObject.Text = "Any object";
            this.checkBoxMTObject.UseVisualStyleBackColor = true;
            this.checkBoxMTObject.Enter += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxMTCoin
            // 
            this.checkBoxMTCoin.AutoSize = true;
            this.checkBoxMTCoin.Location = new System.Drawing.Point(6, 226);
            this.checkBoxMTCoin.Name = "checkBoxMTCoin";
            this.checkBoxMTCoin.Size = new System.Drawing.Size(47, 17);
            this.checkBoxMTCoin.TabIndex = 38;
            this.checkBoxMTCoin.Text = "Coin";
            this.checkBoxMTCoin.UseVisualStyleBackColor = true;
            this.checkBoxMTCoin.Enter += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxMTRed
            // 
            this.checkBoxMTRed.AutoSize = true;
            this.checkBoxMTRed.Location = new System.Drawing.Point(6, 203);
            this.checkBoxMTRed.Name = "checkBoxMTRed";
            this.checkBoxMTRed.Size = new System.Drawing.Size(46, 17);
            this.checkBoxMTRed.TabIndex = 37;
            this.checkBoxMTRed.Text = "Red";
            this.checkBoxMTRed.UseVisualStyleBackColor = true;
            this.checkBoxMTRed.Enter += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxMTWarp
            // 
            this.checkBoxMTWarp.AutoSize = true;
            this.checkBoxMTWarp.Location = new System.Drawing.Point(6, 180);
            this.checkBoxMTWarp.Name = "checkBoxMTWarp";
            this.checkBoxMTWarp.Size = new System.Drawing.Size(52, 17);
            this.checkBoxMTWarp.TabIndex = 36;
            this.checkBoxMTWarp.Text = "Warp";
            this.checkBoxMTWarp.UseVisualStyleBackColor = true;
            this.checkBoxMTWarp.Enter += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxMTCannon
            // 
            this.checkBoxMTCannon.AutoSize = true;
            this.checkBoxMTCannon.Location = new System.Drawing.Point(6, 157);
            this.checkBoxMTCannon.Name = "checkBoxMTCannon";
            this.checkBoxMTCannon.Size = new System.Drawing.Size(63, 17);
            this.checkBoxMTCannon.TabIndex = 35;
            this.checkBoxMTCannon.Text = "Cannon";
            this.checkBoxMTCannon.UseVisualStyleBackColor = true;
            this.checkBoxMTCannon.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxMTBurning
            // 
            this.checkBoxMTBurning.AutoSize = true;
            this.checkBoxMTBurning.Location = new System.Drawing.Point(6, 134);
            this.checkBoxMTBurning.Name = "checkBoxMTBurning";
            this.checkBoxMTBurning.Size = new System.Drawing.Size(62, 17);
            this.checkBoxMTBurning.TabIndex = 34;
            this.checkBoxMTBurning.Text = "Burning";
            this.checkBoxMTBurning.UseVisualStyleBackColor = true;
            this.checkBoxMTBurning.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxMTGroundpound
            // 
            this.checkBoxMTGroundpound.AutoSize = true;
            this.checkBoxMTGroundpound.Location = new System.Drawing.Point(6, 111);
            this.checkBoxMTGroundpound.Name = "checkBoxMTGroundpound";
            this.checkBoxMTGroundpound.Size = new System.Drawing.Size(91, 17);
            this.checkBoxMTGroundpound.TabIndex = 33;
            this.checkBoxMTGroundpound.Text = "Groundpound";
            this.checkBoxMTGroundpound.UseVisualStyleBackColor = true;
            this.checkBoxMTGroundpound.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxMTLava
            // 
            this.checkBoxMTLava.AutoSize = true;
            this.checkBoxMTLava.Location = new System.Drawing.Point(6, 88);
            this.checkBoxMTLava.Name = "checkBoxMTLava";
            this.checkBoxMTLava.Size = new System.Drawing.Size(50, 17);
            this.checkBoxMTLava.TabIndex = 32;
            this.checkBoxMTLava.Text = "Lava";
            this.checkBoxMTLava.UseVisualStyleBackColor = true;
            this.checkBoxMTLava.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxMTPole
            // 
            this.checkBoxMTPole.AutoSize = true;
            this.checkBoxMTPole.Location = new System.Drawing.Point(6, 65);
            this.checkBoxMTPole.Name = "checkBoxMTPole";
            this.checkBoxMTPole.Size = new System.Drawing.Size(47, 17);
            this.checkBoxMTPole.TabIndex = 31;
            this.checkBoxMTPole.Text = "Pole";
            this.checkBoxMTPole.UseVisualStyleBackColor = true;
            this.checkBoxMTPole.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxMTDoor
            // 
            this.checkBoxMTDoor.AutoSize = true;
            this.checkBoxMTDoor.Location = new System.Drawing.Point(6, 42);
            this.checkBoxMTDoor.Name = "checkBoxMTDoor";
            this.checkBoxMTDoor.Size = new System.Drawing.Size(49, 17);
            this.checkBoxMTDoor.TabIndex = 30;
            this.checkBoxMTDoor.Text = "Door";
            this.checkBoxMTDoor.UseVisualStyleBackColor = true;
            this.checkBoxMTDoor.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxMTWallkick
            // 
            this.checkBoxMTWallkick.AutoSize = true;
            this.checkBoxMTWallkick.Location = new System.Drawing.Point(6, 19);
            this.checkBoxMTWallkick.Name = "checkBoxMTWallkick";
            this.checkBoxMTWallkick.Size = new System.Drawing.Size(67, 17);
            this.checkBoxMTWallkick.TabIndex = 29;
            this.checkBoxMTWallkick.Text = "Wallkick";
            this.checkBoxMTWallkick.UseVisualStyleBackColor = true;
            this.checkBoxMTWallkick.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // labelDeathAction
            // 
            this.labelDeathAction.AutoSize = true;
            this.labelDeathAction.Location = new System.Drawing.Point(6, 312);
            this.labelDeathAction.Name = "labelDeathAction";
            this.labelDeathAction.Size = new System.Drawing.Size(87, 13);
            this.labelDeathAction.TabIndex = 27;
            this.labelDeathAction.Text = "When Mario dies";
            // 
            // comboBoxDeathAction
            // 
            this.comboBoxDeathAction.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxDeathAction.FormattingEnabled = true;
            this.comboBoxDeathAction.Items.AddRange(new object[] {
            "do nothing",
            "go to Act Select",
            "go to Level Reset",
            "load savestate"});
            this.comboBoxDeathAction.Location = new System.Drawing.Point(100, 309);
            this.comboBoxDeathAction.Name = "comboBoxDeathAction";
            this.comboBoxDeathAction.Size = new System.Drawing.Size(220, 21);
            this.comboBoxDeathAction.TabIndex = 26;
            this.toolTip.SetToolTip(this.comboBoxDeathAction, "Triggers a special action when mario dies. DEATH ACTION in game.");
            this.comboBoxDeathAction.SelectionChangeCommitted += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxMuteMusic
            // 
            this.checkBoxMuteMusic.AutoSize = true;
            this.checkBoxMuteMusic.Location = new System.Drawing.Point(6, 188);
            this.checkBoxMuteMusic.Name = "checkBoxMuteMusic";
            this.checkBoxMuteMusic.Size = new System.Drawing.Size(80, 17);
            this.checkBoxMuteMusic.TabIndex = 25;
            this.checkBoxMuteMusic.Text = "Mute music";
            this.toolTip.SetToolTip(this.checkBoxMuteMusic, "Mutes the music. MUTE MUSIC in game.");
            this.checkBoxMuteMusic.UseVisualStyleBackColor = true;
            this.checkBoxMuteMusic.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // labelStateCond
            // 
            this.labelStateCond.AutoSize = true;
            this.labelStateCond.Location = new System.Drawing.Point(6, 285);
            this.labelStateCond.Name = "labelStateCond";
            this.labelStateCond.Size = new System.Drawing.Size(88, 13);
            this.labelStateCond.TabIndex = 24;
            this.labelStateCond.Text = "State is set when";
            // 
            // comboBoxStateStyle
            // 
            this.comboBoxStateStyle.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxStateStyle.FormattingEnabled = true;
            this.comboBoxStateStyle.Items.AddRange(new object[] {
            "button is pressed on pause",
            "any pause happens"});
            this.comboBoxStateStyle.Location = new System.Drawing.Point(100, 282);
            this.comboBoxStateStyle.Name = "comboBoxStateStyle";
            this.comboBoxStateStyle.Size = new System.Drawing.Size(220, 21);
            this.comboBoxStateStyle.TabIndex = 23;
            this.toolTip.SetToolTip(this.comboBoxStateStyle, "Changes condition to set in game state. SSAVE STYLE in game.");
            this.comboBoxStateStyle.SelectionChangeCommitted += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxStopTimer100s
            // 
            this.checkBoxStopTimer100s.AutoSize = true;
            this.checkBoxStopTimer100s.Location = new System.Drawing.Point(6, 165);
            this.checkBoxStopTimer100s.Name = "checkBoxStopTimer100s";
            this.checkBoxStopTimer100s.Size = new System.Drawing.Size(152, 17);
            this.checkBoxStopTimer100s.TabIndex = 22;
            this.checkBoxStopTimer100s.Text = "Stop timer on 100 coin star";
            this.toolTip.SetToolTip(this.checkBoxStopTimer100s, "Considers 100 coin stars interaction as a condition to stop the timer.\r\nTIMER 100" +
        " in game.");
            this.checkBoxStopTimer100s.UseVisualStyleBackColor = true;
            this.checkBoxStopTimer100s.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // comboBoxTimerStyle
            // 
            this.comboBoxTimerStyle.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxTimerStyle.FormattingEnabled = true;
            this.comboBoxTimerStyle.Items.AddRange(new object[] {
            "Star Grab",
            "XCam"});
            this.comboBoxTimerStyle.Location = new System.Drawing.Point(81, 138);
            this.comboBoxTimerStyle.Name = "comboBoxTimerStyle";
            this.comboBoxTimerStyle.Size = new System.Drawing.Size(93, 21);
            this.comboBoxTimerStyle.TabIndex = 21;
            this.toolTip.SetToolTip(this.comboBoxTimerStyle, "Star grab stops the timer when star is touched, XCam stops the timer when\r\nMario " +
        "reaches the floor - when camera icon is X. TIMER STYLE option in game.");
            this.comboBoxTimerStyle.SelectionChangeCommitted += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxShowTimer
            // 
            this.checkBoxShowTimer.AutoSize = true;
            this.checkBoxShowTimer.Checked = true;
            this.checkBoxShowTimer.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxShowTimer.Location = new System.Drawing.Point(6, 115);
            this.checkBoxShowTimer.Name = "checkBoxShowTimer";
            this.checkBoxShowTimer.Size = new System.Drawing.Size(78, 17);
            this.checkBoxShowTimer.TabIndex = 20;
            this.checkBoxShowTimer.Text = "Show timer";
            this.toolTip.SetToolTip(this.checkBoxShowTimer, "Displays the general timer. Makes the slide timer work. TIMER option in game.");
            this.checkBoxShowTimer.UseVisualStyleBackColor = true;
            this.checkBoxShowTimer.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxDistanceToSecret
            // 
            this.checkBoxDistanceToSecret.AutoSize = true;
            this.checkBoxDistanceToSecret.Location = new System.Drawing.Point(6, 385);
            this.checkBoxDistanceToSecret.Name = "checkBoxDistanceToSecret";
            this.checkBoxDistanceToSecret.Size = new System.Drawing.Size(194, 17);
            this.checkBoxDistanceToSecret.TabIndex = 19;
            this.checkBoxDistanceToSecret.Text = "Show distance to the closest secret";
            this.toolTip.SetToolTip(this.checkBoxDistanceToSecret, "Displays distance to secrets. D TO SECRET in game.");
            this.checkBoxDistanceToSecret.UseVisualStyleBackColor = true;
            this.checkBoxDistanceToSecret.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxDistanceToRedCoin
            // 
            this.checkBoxDistanceToRedCoin.AutoSize = true;
            this.checkBoxDistanceToRedCoin.Location = new System.Drawing.Point(6, 362);
            this.checkBoxDistanceToRedCoin.Name = "checkBoxDistanceToRedCoin";
            this.checkBoxDistanceToRedCoin.Size = new System.Drawing.Size(203, 17);
            this.checkBoxDistanceToRedCoin.TabIndex = 18;
            this.checkBoxDistanceToRedCoin.Text = "Show distance to the closest red coin";
            this.toolTip.SetToolTip(this.checkBoxDistanceToRedCoin, "Displays distance to reds. D TO RED in game.");
            this.checkBoxDistanceToRedCoin.UseVisualStyleBackColor = true;
            this.checkBoxDistanceToRedCoin.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxWKFrame
            // 
            this.checkBoxWKFrame.AutoSize = true;
            this.checkBoxWKFrame.Location = new System.Drawing.Point(6, 92);
            this.checkBoxWKFrame.Name = "checkBoxWKFrame";
            this.checkBoxWKFrame.Size = new System.Drawing.Size(123, 17);
            this.checkBoxWKFrame.TabIndex = 17;
            this.checkBoxWKFrame.Text = "Show wallkick frame";
            this.toolTip.SetToolTip(this.checkBoxWKFrame, "Displays the wallkick frame on the wallkick. WALLKICK FRAME option in game.");
            this.checkBoxWKFrame.UseVisualStyleBackColor = true;
            this.checkBoxWKFrame.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // comboBoxDpadDown
            // 
            this.comboBoxDpadDown.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxDpadDown.FormattingEnabled = true;
            this.comboBoxDpadDown.Items.AddRange(new object[] {
            "Off",
            "Act Select",
            "Level Reset",
            "Start Reset",
            "Levitate",
            "Load State"});
            this.comboBoxDpadDown.Location = new System.Drawing.Point(199, 170);
            this.comboBoxDpadDown.Name = "comboBoxDpadDown";
            this.comboBoxDpadDown.Size = new System.Drawing.Size(121, 21);
            this.comboBoxDpadDown.TabIndex = 16;
            this.toolTip.SetToolTip(this.comboBoxDpadDown, "Changes action on pressing DPad Down button. D DOWN ACTION in game.");
            this.comboBoxDpadDown.SelectionChangeCommitted += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // labelDPadDown
            // 
            this.labelDPadDown.AutoSize = true;
            this.labelDPadDown.Location = new System.Drawing.Point(196, 154);
            this.labelDPadDown.Name = "labelDPadDown";
            this.labelDPadDown.Size = new System.Drawing.Size(130, 13);
            this.labelDPadDown.TabIndex = 15;
            this.labelDPadDown.Text = "DPad Down button action";
            // 
            // comboBoxFC
            // 
            this.comboBoxFC.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxFC.FormattingEnabled = true;
            this.comboBoxFC.Items.AddRange(new object[] {
            "Off",
            "Act Select",
            "Level Reset",
            "Start Reset",
            "Levitate",
            "Load State"});
            this.comboBoxFC.Location = new System.Drawing.Point(199, 130);
            this.comboBoxFC.Name = "comboBoxFC";
            this.comboBoxFC.Size = new System.Drawing.Size(121, 21);
            this.comboBoxFC.TabIndex = 14;
            this.toolTip.SetToolTip(this.comboBoxFC, "Changes action on pressing all 4 C Buttons. 4C ACTION in game.");
            this.comboBoxFC.SelectionChangeCommitted += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // label4C
            // 
            this.label4C.AutoSize = true;
            this.label4C.Location = new System.Drawing.Point(196, 114);
            this.label4C.Name = "label4C";
            this.label4C.Size = new System.Drawing.Size(94, 13);
            this.label4C.TabIndex = 13;
            this.label4C.Text = "4 C Buttons action";
            // 
            // comboBoxLR
            // 
            this.comboBoxLR.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxLR.FormattingEnabled = true;
            this.comboBoxLR.Items.AddRange(new object[] {
            "Off",
            "Act Select",
            "Level Reset",
            "Start Reset",
            "Levitate",
            "Load State"});
            this.comboBoxLR.Location = new System.Drawing.Point(199, 90);
            this.comboBoxLR.Name = "comboBoxLR";
            this.comboBoxLR.Size = new System.Drawing.Size(121, 21);
            this.comboBoxLR.TabIndex = 12;
            this.toolTip.SetToolTip(this.comboBoxLR, "Changes action on pressing L and R buttons. L+R ACTION in game.");
            this.comboBoxLR.SelectionChangeCommitted += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // labelLR
            // 
            this.labelLR.AutoSize = true;
            this.labelLR.Location = new System.Drawing.Point(196, 74);
            this.labelLR.Name = "labelLR";
            this.labelLR.Size = new System.Drawing.Size(97, 13);
            this.labelLR.TabIndex = 11;
            this.labelLR.Text = "L+R buttons action";
            // 
            // comboBoxL
            // 
            this.comboBoxL.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxL.FormattingEnabled = true;
            this.comboBoxL.Items.AddRange(new object[] {
            "Off",
            "Act Select",
            "Level Reset",
            "Start Reset",
            "Levitate",
            "Load State"});
            this.comboBoxL.Location = new System.Drawing.Point(199, 50);
            this.comboBoxL.Name = "comboBoxL";
            this.comboBoxL.Size = new System.Drawing.Size(121, 21);
            this.comboBoxL.TabIndex = 10;
            this.toolTip.SetToolTip(this.comboBoxL, "Changes action on pressing L button. L ACTION in game.");
            this.comboBoxL.SelectionChangeCommitted += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // labelLButtonAction
            // 
            this.labelLButtonAction.AutoSize = true;
            this.labelLButtonAction.Location = new System.Drawing.Point(196, 34);
            this.labelLButtonAction.Name = "labelLButtonAction";
            this.labelLButtonAction.Size = new System.Drawing.Size(78, 13);
            this.labelLButtonAction.TabIndex = 9;
            this.labelLButtonAction.Text = "L button action";
            // 
            // checkBoxButtons
            // 
            this.checkBoxButtons.AutoSize = true;
            this.checkBoxButtons.Location = new System.Drawing.Point(6, 42);
            this.checkBoxButtons.Name = "checkBoxButtons";
            this.checkBoxButtons.Size = new System.Drawing.Size(91, 17);
            this.checkBoxButtons.TabIndex = 8;
            this.checkBoxButtons.Text = "Show buttons";
            this.toolTip.SetToolTip(this.checkBoxButtons, "Displays buttons that are being pressed. BUTTONS option in game.");
            this.checkBoxButtons.UseVisualStyleBackColor = true;
            this.checkBoxButtons.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // comboBoxStick
            // 
            this.comboBoxStick.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxStick.FormattingEnabled = true;
            this.comboBoxStick.Items.AddRange(new object[] {
            "No Stick",
            "Text Stick",
            "Graphics Stick"});
            this.comboBoxStick.Location = new System.Drawing.Point(6, 65);
            this.comboBoxStick.Name = "comboBoxStick";
            this.comboBoxStick.Size = new System.Drawing.Size(121, 21);
            this.comboBoxStick.TabIndex = 7;
            this.toolTip.SetToolTip(this.comboBoxStick, "Displays the stick direction being held. Graphics option draws 2 circles marking " +
        "the center and stick position,\r\ntext option shows raw values. STICK option in ga" +
        "me.");
            this.comboBoxStick.SelectionChangeCommitted += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // groupBoxROM
            // 
            this.groupBoxROM.Controls.Add(this.label1);
            this.groupBoxROM.Controls.Add(this.labelROM);
            this.groupBoxROM.Controls.Add(this.buttonPatch);
            this.groupBoxROM.Location = new System.Drawing.Point(357, 42);
            this.groupBoxROM.Name = "groupBoxROM";
            this.groupBoxROM.Size = new System.Drawing.Size(139, 90);
            this.groupBoxROM.TabIndex = 9;
            this.groupBoxROM.TabStop = false;
            this.groupBoxROM.Text = "ROM";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 35);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(106, 13);
            this.label1.TabIndex = 8;
            this.label1.Text = "with selected configs";
            // 
            // labelROM
            // 
            this.labelROM.AutoSize = true;
            this.labelROM.Location = new System.Drawing.Point(11, 20);
            this.labelROM.Name = "labelROM";
            this.labelROM.Size = new System.Drawing.Size(121, 13);
            this.labelROM.TabIndex = 7;
            this.labelROM.Text = "Or create patched ROM";
            // 
            // labelInfo
            // 
            this.labelInfo.Location = new System.Drawing.Point(13, 9);
            this.labelInfo.Name = "labelInfo";
            this.labelInfo.Size = new System.Drawing.Size(483, 26);
            this.labelInfo.TabIndex = 8;
            this.labelInfo.Text = "Welcome to hacktice control! In order to use the tool, either a payload\r\nneeds to" +
    " be injected in the emulator or patched ROM needs to be created.";
            this.labelInfo.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // checkBoxShowCollision
            // 
            this.checkBoxShowCollision.AutoSize = true;
            this.checkBoxShowCollision.Location = new System.Drawing.Point(6, 257);
            this.checkBoxShowCollision.Name = "checkBoxShowCollision";
            this.checkBoxShowCollision.Size = new System.Drawing.Size(112, 17);
            this.checkBoxShowCollision.TabIndex = 39;
            this.checkBoxShowCollision.Text = "Show cell collision";
            this.toolTip.SetToolTip(this.checkBoxShowCollision, "Enables warp wheel to select the warp target using control stick rotation. WARP W" +
        "HEEL in game.");
            this.checkBoxShowCollision.UseVisualStyleBackColor = true;
            this.checkBoxShowCollision.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // Tool
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(508, 590);
            this.Controls.Add(this.labelInfo);
            this.Controls.Add(this.groupBoxROM);
            this.Controls.Add(this.groupBoxConfig);
            this.Controls.Add(this.groupBoxInject);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Tool";
            this.ShowIcon = false;
            this.Text = "hacktice";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxState)).EndInit();
            this.groupBoxInject.ResumeLayout(false);
            this.groupBoxInject.PerformLayout();
            this.groupBoxConfig.ResumeLayout(false);
            this.groupBoxConfig.PerformLayout();
            this.groupBoxMiscTimer.ResumeLayout(false);
            this.groupBoxMiscTimer.PerformLayout();
            this.groupBoxROM.ResumeLayout(false);
            this.groupBoxROM.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonPatch;
        private System.Windows.Forms.Label labelEmulatorState;
        private System.Windows.Forms.PictureBox pictureBoxState;
        private System.Windows.Forms.Button buttonInjectInEmulator;
        private System.Windows.Forms.CheckBox checkBoxShowSpeed;
        private System.Windows.Forms.GroupBox groupBoxInject;
        private System.Windows.Forms.GroupBox groupBoxConfig;
        private System.Windows.Forms.ComboBox comboBoxStick;
        private System.Windows.Forms.CheckBox checkBoxButtons;
        private System.Windows.Forms.ComboBox comboBoxL;
        private System.Windows.Forms.Label labelLButtonAction;
        private System.Windows.Forms.ComboBox comboBoxLR;
        private System.Windows.Forms.Label labelLR;
        private System.Windows.Forms.ComboBox comboBoxFC;
        private System.Windows.Forms.Label label4C;
        private System.Windows.Forms.ComboBox comboBoxDpadDown;
        private System.Windows.Forms.Label labelDPadDown;
        private System.Windows.Forms.CheckBox checkBoxWKFrame;
        private System.Windows.Forms.CheckBox checkBoxDistanceToSecret;
        private System.Windows.Forms.CheckBox checkBoxDistanceToRedCoin;
        private System.Windows.Forms.CheckBox checkBoxShowTimer;
        private System.Windows.Forms.ComboBox comboBoxTimerStyle;
        private System.Windows.Forms.CheckBox checkBoxStopTimer100s;
        private System.Windows.Forms.Label labelStateCond;
        private System.Windows.Forms.ComboBox comboBoxStateStyle;
        private System.Windows.Forms.CheckBox checkBoxMuteMusic;
        private System.Windows.Forms.Label labelDeathAction;
        private System.Windows.Forms.ComboBox comboBoxDeathAction;
        private System.Windows.Forms.GroupBox groupBoxROM;
        private System.Windows.Forms.GroupBox groupBoxMiscTimer;
        private System.Windows.Forms.CheckBox checkBoxMTWallkick;
        private System.Windows.Forms.CheckBox checkBoxMTPole;
        private System.Windows.Forms.CheckBox checkBoxMTDoor;
        private System.Windows.Forms.CheckBox checkBoxMTLava;
        private System.Windows.Forms.CheckBox checkBoxMTGroundpound;
        private System.Windows.Forms.CheckBox checkBoxMTPlatform;
        private System.Windows.Forms.CheckBox checkBoxMTObject;
        private System.Windows.Forms.CheckBox checkBoxMTCoin;
        private System.Windows.Forms.CheckBox checkBoxMTRed;
        private System.Windows.Forms.CheckBox checkBoxMTWarp;
        private System.Windows.Forms.CheckBox checkBoxMTCannon;
        private System.Windows.Forms.CheckBox checkBoxMTBurning;
        private System.Windows.Forms.Button buttonSaveConfig;
        private System.Windows.Forms.Button buttonLoadConfig;
        private System.Windows.Forms.Label labelDescInject;
        private System.Windows.Forms.Label labelROM;
        private System.Windows.Forms.Label labelInfo;
        private System.Windows.Forms.ToolTip toolTip;
        private System.Windows.Forms.Label labelTimerStopOn;
        private System.Windows.Forms.Label labelExpl;
        private System.Windows.Forms.Button buttonSetDefault;
        private System.Windows.Forms.Button buttonReset;
        private System.Windows.Forms.ComboBox comboBoxDpadUp;
        private System.Windows.Forms.Label labelDPadUpAction;
        private System.Windows.Forms.CheckBox checkBoxWarpWheel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox checkBoxSoftReset;
        private System.Windows.Forms.CheckBox checkBoxShowCustomText;
        private System.Windows.Forms.TextBox textBoxCustomText;
        private System.Windows.Forms.CheckBox checkBoxShowCollision;
    }
}