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
            this.buttonGSCode = new System.Windows.Forms.Button();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.SuspendLayout();
            // 
            // buttonPatch
            // 
            this.buttonPatch.Location = new System.Drawing.Point(12, 212);
            this.buttonPatch.Name = "buttonPatch";
            this.buttonPatch.Size = new System.Drawing.Size(75, 23);
            this.buttonPatch.TabIndex = 0;
            this.buttonPatch.Text = "Patch";
            this.buttonPatch.UseVisualStyleBackColor = true;
            this.buttonPatch.Click += new System.EventHandler(this.buttonPatch_Click);
            // 
            // buttonGSCode
            // 
            this.buttonGSCode.Location = new System.Drawing.Point(130, 212);
            this.buttonGSCode.Name = "buttonGSCode";
            this.buttonGSCode.Size = new System.Drawing.Size(75, 23);
            this.buttonGSCode.TabIndex = 1;
            this.buttonGSCode.Text = "GS Code";
            this.buttonGSCode.UseVisualStyleBackColor = true;
            this.buttonGSCode.Click += new System.EventHandler(this.buttonGSCode_Click);
            // 
            // richTextBox1
            // 
            this.richTextBox1.Location = new System.Drawing.Point(12, 12);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(193, 194);
            this.richTextBox1.TabIndex = 2;
            this.richTextBox1.Text = "";
            // 
            // Tool
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(217, 247);
            this.Controls.Add(this.richTextBox1);
            this.Controls.Add(this.buttonGSCode);
            this.Controls.Add(this.buttonPatch);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Tool";
            this.Text = "hacktice";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonPatch;
        private System.Windows.Forms.Button buttonGSCode;
        private System.Windows.Forms.RichTextBox richTextBox1;
    }
}