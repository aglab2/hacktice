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
            this.buttonPatch = new System.Windows.Forms.Button();
            this.labelEmulatorState = new System.Windows.Forms.Label();
            this.pictureBoxState = new System.Windows.Forms.PictureBox();
            this.buttonInjectInEmulator = new System.Windows.Forms.Button();
            this.checkBoxShowSpeed = new System.Windows.Forms.CheckBox();
            this.groupBoxInject = new System.Windows.Forms.GroupBox();
            this.labelDescInject = new System.Windows.Forms.Label();
            this.groupBoxConfig = new System.Windows.Forms.GroupBox();
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
            this.labelROM = new System.Windows.Forms.Label();
            this.labelInfo = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxState)).BeginInit();
            this.groupBoxInject.SuspendLayout();
            this.groupBoxConfig.SuspendLayout();
            this.groupBoxMiscTimer.SuspendLayout();
            this.groupBoxROM.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonPatch
            // 
            this.buttonPatch.Location = new System.Drawing.Point(16, 51);
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
            this.labelEmulatorState.Size = new System.Drawing.Size(157, 13);
            this.labelEmulatorState.TabIndex = 3;
            this.labelEmulatorState.Text = "No supported emulator is found.";
            // 
            // pictureBoxState
            // 
            this.pictureBoxState.BackColor = System.Drawing.SystemColors.ControlDark;
            this.pictureBoxState.Location = new System.Drawing.Point(6, 48);
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
            this.buttonInjectInEmulator.Size = new System.Drawing.Size(110, 23);
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
            this.labelDescInject.Location = new System.Drawing.Point(118, 24);
            this.labelDescInject.Name = "labelDescInject";
            this.labelDescInject.Size = new System.Drawing.Size(185, 13);
            this.labelDescInject.TabIndex = 6;
            this.labelDescInject.Text = "Run clean ROM for Emulator injection";
            // 
            // groupBoxConfig
            // 
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
            this.groupBoxConfig.Enabled = false;
            this.groupBoxConfig.Location = new System.Drawing.Point(13, 138);
            this.groupBoxConfig.Name = "groupBoxConfig";
            this.groupBoxConfig.Size = new System.Drawing.Size(483, 354);
            this.groupBoxConfig.TabIndex = 8;
            this.groupBoxConfig.TabStop = false;
            this.groupBoxConfig.Text = "Config";
            // 
            // buttonLoadConfig
            // 
            this.buttonLoadConfig.Location = new System.Drawing.Point(92, 325);
            this.buttonLoadConfig.Name = "buttonLoadConfig";
            this.buttonLoadConfig.Size = new System.Drawing.Size(80, 23);
            this.buttonLoadConfig.TabIndex = 29;
            this.buttonLoadConfig.Text = "Load config";
            this.buttonLoadConfig.UseVisualStyleBackColor = true;
            this.buttonLoadConfig.Click += new System.EventHandler(this.buttonLoadConfig_Click);
            // 
            // buttonSaveConfig
            // 
            this.buttonSaveConfig.Location = new System.Drawing.Point(6, 325);
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
            this.labelDeathAction.Location = new System.Drawing.Point(6, 240);
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
            this.comboBoxDeathAction.Location = new System.Drawing.Point(100, 237);
            this.comboBoxDeathAction.Name = "comboBoxDeathAction";
            this.comboBoxDeathAction.Size = new System.Drawing.Size(220, 21);
            this.comboBoxDeathAction.TabIndex = 26;
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
            this.checkBoxMuteMusic.UseVisualStyleBackColor = true;
            this.checkBoxMuteMusic.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // labelStateCond
            // 
            this.labelStateCond.AutoSize = true;
            this.labelStateCond.Location = new System.Drawing.Point(6, 213);
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
            this.comboBoxStateStyle.Location = new System.Drawing.Point(100, 210);
            this.comboBoxStateStyle.Name = "comboBoxStateStyle";
            this.comboBoxStateStyle.Size = new System.Drawing.Size(220, 21);
            this.comboBoxStateStyle.TabIndex = 23;
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
            this.checkBoxStopTimer100s.UseVisualStyleBackColor = true;
            this.checkBoxStopTimer100s.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // comboBoxTimerStyle
            // 
            this.comboBoxTimerStyle.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxTimerStyle.FormattingEnabled = true;
            this.comboBoxTimerStyle.Items.AddRange(new object[] {
            "Star Grab Timer",
            "XCam Timer"});
            this.comboBoxTimerStyle.Location = new System.Drawing.Point(6, 138);
            this.comboBoxTimerStyle.Name = "comboBoxTimerStyle";
            this.comboBoxTimerStyle.Size = new System.Drawing.Size(121, 21);
            this.comboBoxTimerStyle.TabIndex = 21;
            this.comboBoxTimerStyle.SelectionChangeCommitted += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxShowTimer
            // 
            this.checkBoxShowTimer.AutoSize = true;
            this.checkBoxShowTimer.Location = new System.Drawing.Point(6, 115);
            this.checkBoxShowTimer.Name = "checkBoxShowTimer";
            this.checkBoxShowTimer.Size = new System.Drawing.Size(78, 17);
            this.checkBoxShowTimer.TabIndex = 20;
            this.checkBoxShowTimer.Text = "Show timer";
            this.checkBoxShowTimer.UseVisualStyleBackColor = true;
            this.checkBoxShowTimer.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxDistanceToSecret
            // 
            this.checkBoxDistanceToSecret.AutoSize = true;
            this.checkBoxDistanceToSecret.Location = new System.Drawing.Point(6, 287);
            this.checkBoxDistanceToSecret.Name = "checkBoxDistanceToSecret";
            this.checkBoxDistanceToSecret.Size = new System.Drawing.Size(194, 17);
            this.checkBoxDistanceToSecret.TabIndex = 19;
            this.checkBoxDistanceToSecret.Text = "Show distance to the closest secret";
            this.checkBoxDistanceToSecret.UseVisualStyleBackColor = true;
            this.checkBoxDistanceToSecret.CheckedChanged += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // checkBoxDistanceToRedCoin
            // 
            this.checkBoxDistanceToRedCoin.AutoSize = true;
            this.checkBoxDistanceToRedCoin.Location = new System.Drawing.Point(6, 264);
            this.checkBoxDistanceToRedCoin.Name = "checkBoxDistanceToRedCoin";
            this.checkBoxDistanceToRedCoin.Size = new System.Drawing.Size(203, 17);
            this.checkBoxDistanceToRedCoin.TabIndex = 18;
            this.checkBoxDistanceToRedCoin.Text = "Show distance to the closest red coin";
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
            this.comboBoxDpadDown.Location = new System.Drawing.Point(199, 155);
            this.comboBoxDpadDown.Name = "comboBoxDpadDown";
            this.comboBoxDpadDown.Size = new System.Drawing.Size(121, 21);
            this.comboBoxDpadDown.TabIndex = 16;
            this.comboBoxDpadDown.SelectionChangeCommitted += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // labelDPadDown
            // 
            this.labelDPadDown.AutoSize = true;
            this.labelDPadDown.Location = new System.Drawing.Point(196, 139);
            this.labelDPadDown.Name = "labelDPadDown";
            this.labelDPadDown.Size = new System.Drawing.Size(137, 13);
            this.labelDPadDown.TabIndex = 15;
            this.labelDPadDown.Text = "DPad Down Buttons Action";
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
            this.comboBoxFC.Location = new System.Drawing.Point(199, 115);
            this.comboBoxFC.Name = "comboBoxFC";
            this.comboBoxFC.Size = new System.Drawing.Size(121, 21);
            this.comboBoxFC.TabIndex = 14;
            this.comboBoxFC.SelectionChangeCommitted += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // label4C
            // 
            this.label4C.AutoSize = true;
            this.label4C.Location = new System.Drawing.Point(196, 99);
            this.label4C.Name = "label4C";
            this.label4C.Size = new System.Drawing.Size(95, 13);
            this.label4C.TabIndex = 13;
            this.label4C.Text = "4 C Buttons Action";
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
            this.comboBoxLR.Location = new System.Drawing.Point(199, 75);
            this.comboBoxLR.Name = "comboBoxLR";
            this.comboBoxLR.Size = new System.Drawing.Size(121, 21);
            this.comboBoxLR.TabIndex = 12;
            this.comboBoxLR.SelectionChangeCommitted += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // labelLR
            // 
            this.labelLR.AutoSize = true;
            this.labelLR.Location = new System.Drawing.Point(196, 59);
            this.labelLR.Name = "labelLR";
            this.labelLR.Size = new System.Drawing.Size(99, 13);
            this.labelLR.TabIndex = 11;
            this.labelLR.Text = "L+R Buttons Action";
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
            this.comboBoxL.Location = new System.Drawing.Point(199, 35);
            this.comboBoxL.Name = "comboBoxL";
            this.comboBoxL.Size = new System.Drawing.Size(121, 21);
            this.comboBoxL.TabIndex = 10;
            this.comboBoxL.SelectionChangeCommitted += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // labelLButtonAction
            // 
            this.labelLButtonAction.AutoSize = true;
            this.labelLButtonAction.Location = new System.Drawing.Point(196, 19);
            this.labelLButtonAction.Name = "labelLButtonAction";
            this.labelLButtonAction.Size = new System.Drawing.Size(80, 13);
            this.labelLButtonAction.TabIndex = 9;
            this.labelLButtonAction.Text = "L Button Action";
            // 
            // checkBoxButtons
            // 
            this.checkBoxButtons.AutoSize = true;
            this.checkBoxButtons.Location = new System.Drawing.Point(6, 42);
            this.checkBoxButtons.Name = "checkBoxButtons";
            this.checkBoxButtons.Size = new System.Drawing.Size(91, 17);
            this.checkBoxButtons.TabIndex = 8;
            this.checkBoxButtons.Text = "Show buttons";
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
            this.comboBoxStick.SelectionChangeCommitted += new System.EventHandler(this.Config_CheckedChanged);
            // 
            // groupBoxROM
            // 
            this.groupBoxROM.Controls.Add(this.labelROM);
            this.groupBoxROM.Controls.Add(this.buttonPatch);
            this.groupBoxROM.Location = new System.Drawing.Point(357, 42);
            this.groupBoxROM.Name = "groupBoxROM";
            this.groupBoxROM.Size = new System.Drawing.Size(139, 90);
            this.groupBoxROM.TabIndex = 9;
            this.groupBoxROM.TabStop = false;
            this.groupBoxROM.Text = "ROM";
            // 
            // labelROM
            // 
            this.labelROM.AutoSize = true;
            this.labelROM.Location = new System.Drawing.Point(11, 24);
            this.labelROM.Name = "labelROM";
            this.labelROM.Size = new System.Drawing.Size(121, 13);
            this.labelROM.TabIndex = 7;
            this.labelROM.Text = "Or create patched ROM";
            // 
            // labelInfo
            // 
            this.labelInfo.AutoSize = true;
            this.labelInfo.Location = new System.Drawing.Point(75, 9);
            this.labelInfo.Name = "labelInfo";
            this.labelInfo.Size = new System.Drawing.Size(358, 26);
            this.labelInfo.TabIndex = 8;
            this.labelInfo.Text = "Welcome to hacktice control! In order to use the tool, either a payload\r\nneeds to" +
    " be injected in the emulator or patched ROM needs to be created.";
            this.labelInfo.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Tool
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(508, 503);
            this.Controls.Add(this.labelInfo);
            this.Controls.Add(this.groupBoxROM);
            this.Controls.Add(this.groupBoxConfig);
            this.Controls.Add(this.groupBoxInject);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Tool";
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
            this.PerformLayout();

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
    }
}