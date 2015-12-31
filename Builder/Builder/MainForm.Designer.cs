namespace Builder
{
   partial class MainForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.openExeDialog = new System.Windows.Forms.OpenFileDialog();
            this.openIconDialog = new System.Windows.Forms.OpenFileDialog();
            this.label6 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.delayTextBox = new CustomTextBox();
            this.exeBtn = new CustomButton();
            this.netCheckBox = new CustomCheckBox();
            this.meltCheckBox = new CustomCheckBox();
            this.antiVmCheckBox = new CustomCheckBox();
            this.installCheckBox = new CustomCheckBox();
            this.exeTextBox = new CustomTextBox();
            this.keyTextBox = new CustomTextBox();
            this.fileTextBox = new CustomTextBox();
            this.cryptBtn = new CustomButton();
            this.closeButton = new TopCustomButton();
            this.persistCheckbox = new CustomCheckBox();
            this.SuspendLayout();
            // 
            // openExeDialog
            // 
            this.openExeDialog.Filter = "EXE|*.exe";
            // 
            // openIconDialog
            // 
            this.openIconDialog.FileName = "icon.ico";
            this.openIconDialog.Filter = "Icon|*.ico";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(8, 112);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(34, 13);
            this.label6.TabIndex = 35;
            this.label6.Text = "Delay";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(11, 86);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(25, 13);
            this.label1.TabIndex = 22;
            this.label1.Text = "Key";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(13, 57);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(23, 13);
            this.label5.TabIndex = 12;
            this.label5.Text = "File";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(13, 36);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(29, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Stub";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // delayTextBox
            // 
            this.delayTextBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(37)))), ((int)(((byte)(38)))));
            this.delayTextBox.ForeColor = System.Drawing.Color.Transparent;
            this.delayTextBox.Location = new System.Drawing.Point(51, 109);
            this.delayTextBox.Name = "delayTextBox";
            this.delayTextBox.Size = new System.Drawing.Size(231, 20);
            this.delayTextBox.TabIndex = 36;
            this.delayTextBox.Text = "0";
            // 
            // exeBtn
            // 
            this.exeBtn.BackColor = System.Drawing.Color.White;
            this.exeBtn.ForeColor = System.Drawing.Color.White;
            this.exeBtn.Location = new System.Drawing.Point(254, 29);
            this.exeBtn.Name = "exeBtn";
            this.exeBtn.Size = new System.Drawing.Size(28, 23);
            this.exeBtn.TabIndex = 27;
            this.exeBtn.Text = "...";
            this.exeBtn.UseVisualStyleBackColor = false;
            this.exeBtn.Click += new System.EventHandler(this.exeBtn_Click);
            // 
            // netCheckBox
            // 
            this.netCheckBox.AutoSize = true;
            this.netCheckBox.ForeColor = System.Drawing.Color.White;
            this.netCheckBox.Location = new System.Drawing.Point(289, 61);
            this.netCheckBox.Name = "netCheckBox";
            this.netCheckBox.Size = new System.Drawing.Size(69, 17);
            this.netCheckBox.TabIndex = 26;
            this.netCheckBox.Text = ".NET 2.0";
            this.netCheckBox.UseVisualStyleBackColor = false;
            this.netCheckBox.CheckedChanged += new System.EventHandler(this.netCheckBox_CheckedChanged);
            // 
            // meltCheckBox
            // 
            this.meltCheckBox.AutoSize = true;
            this.meltCheckBox.Checked = true;
            this.meltCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.meltCheckBox.Location = new System.Drawing.Point(289, 92);
            this.meltCheckBox.Name = "meltCheckBox";
            this.meltCheckBox.Size = new System.Drawing.Size(46, 17);
            this.meltCheckBox.TabIndex = 25;
            this.meltCheckBox.Text = "Melt";
            this.meltCheckBox.UseVisualStyleBackColor = true;
            // 
            // antiVmCheckBox
            // 
            this.antiVmCheckBox.AutoSize = true;
            this.antiVmCheckBox.Location = new System.Drawing.Point(364, 92);
            this.antiVmCheckBox.Name = "antiVmCheckBox";
            this.antiVmCheckBox.Size = new System.Drawing.Size(63, 17);
            this.antiVmCheckBox.TabIndex = 24;
            this.antiVmCheckBox.Text = "Anti VM";
            this.antiVmCheckBox.UseVisualStyleBackColor = true;
            // 
            // installCheckBox
            // 
            this.installCheckBox.AutoSize = true;
            this.installCheckBox.Checked = true;
            this.installCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.installCheckBox.Location = new System.Drawing.Point(364, 61);
            this.installCheckBox.Name = "installCheckBox";
            this.installCheckBox.Size = new System.Drawing.Size(98, 17);
            this.installCheckBox.TabIndex = 21;
            this.installCheckBox.Text = "Startup / Install";
            this.installCheckBox.UseVisualStyleBackColor = true;
            this.installCheckBox.CheckedChanged += new System.EventHandler(this.installCheckBox_CheckedChanged);
            // 
            // exeTextBox
            // 
            this.exeTextBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(37)))), ((int)(((byte)(38)))));
            this.exeTextBox.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(37)))), ((int)(((byte)(38)))));
            this.exeTextBox.Location = new System.Drawing.Point(51, 31);
            this.exeTextBox.Name = "exeTextBox";
            this.exeTextBox.ReadOnly = true;
            this.exeTextBox.Size = new System.Drawing.Size(197, 20);
            this.exeTextBox.TabIndex = 20;
            // 
            // keyTextBox
            // 
            this.keyTextBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(37)))), ((int)(((byte)(38)))));
            this.keyTextBox.ForeColor = System.Drawing.Color.Transparent;
            this.keyTextBox.Location = new System.Drawing.Point(51, 83);
            this.keyTextBox.Name = "keyTextBox";
            this.keyTextBox.Size = new System.Drawing.Size(231, 20);
            this.keyTextBox.TabIndex = 19;
            this.keyTextBox.Text = "bin";
            // 
            // fileTextBox
            // 
            this.fileTextBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(37)))), ((int)(((byte)(38)))));
            this.fileTextBox.ForeColor = System.Drawing.Color.Transparent;
            this.fileTextBox.Location = new System.Drawing.Point(51, 57);
            this.fileTextBox.Name = "fileTextBox";
            this.fileTextBox.Size = new System.Drawing.Size(231, 20);
            this.fileTextBox.TabIndex = 18;
            this.fileTextBox.Text = "bin.exe";
            // 
            // cryptBtn
            // 
            this.cryptBtn.BackColor = System.Drawing.SystemColors.InactiveBorder;
            this.cryptBtn.ForeColor = System.Drawing.Color.IndianRed;
            this.cryptBtn.Location = new System.Drawing.Point(289, 115);
            this.cryptBtn.Name = "cryptBtn";
            this.cryptBtn.Size = new System.Drawing.Size(173, 44);
            this.cryptBtn.TabIndex = 15;
            this.cryptBtn.Text = "Crypt";
            this.cryptBtn.UseVisualStyleBackColor = false;
            this.cryptBtn.Click += new System.EventHandler(this.cryptBtn_Click);
            // 
            // closeButton
            // 
            this.closeButton.Location = new System.Drawing.Point(441, 6);
            this.closeButton.Name = "closeButton";
            this.closeButton.Size = new System.Drawing.Size(25, 25);
            this.closeButton.TabIndex = 0;
            this.closeButton.Text = "X";
            this.closeButton.UseVisualStyleBackColor = true;
            this.closeButton.Click += new System.EventHandler(this.closeButton_Click);
            // 
            // persistCheckbox
            // 
            this.persistCheckbox.AutoSize = true;
            this.persistCheckbox.CheckAlign = System.Drawing.ContentAlignment.TopLeft;
            this.persistCheckbox.ForeColor = System.Drawing.Color.White;
            this.persistCheckbox.Location = new System.Drawing.Point(289, 29);
            this.persistCheckbox.Name = "persistCheckbox";
            this.persistCheckbox.Size = new System.Drawing.Size(87, 17);
            this.persistCheckbox.TabIndex = 37;
            this.persistCheckbox.Text = "Persistance  ";
            this.persistCheckbox.UseVisualStyleBackColor = false;
            this.persistCheckbox.CheckedChanged += new System.EventHandler(this.customCheckBox1_CheckedChanged);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(37)))), ((int)(((byte)(38)))));
            this.ClientSize = new System.Drawing.Size(472, 169);
            this.Controls.Add(this.persistCheckbox);
            this.Controls.Add(this.delayTextBox);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.exeBtn);
            this.Controls.Add(this.netCheckBox);
            this.Controls.Add(this.meltCheckBox);
            this.Controls.Add(this.antiVmCheckBox);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.installCheckBox);
            this.Controls.Add(this.exeTextBox);
            this.Controls.Add(this.keyTextBox);
            this.Controls.Add(this.fileTextBox);
            this.Controls.Add(this.cryptBtn);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.closeButton);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Cyber Protector";
            this.TopMost = true;
            this.TransparencyKey = System.Drawing.Color.Black;
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

      }

      #endregion

      private TopCustomButton closeButton;
      private System.Windows.Forms.Label label2;
      private System.Windows.Forms.Label label5;
      private CustomButton cryptBtn;
      private CustomTextBox fileTextBox;
      private CustomTextBox keyTextBox;
      private CustomTextBox exeTextBox;
      private CustomCheckBox installCheckBox;
      private System.Windows.Forms.Label label1;
      private CustomCheckBox antiVmCheckBox;
      private CustomCheckBox meltCheckBox;
      private CustomCheckBox netCheckBox;
      private CustomButton exeBtn;
      private System.Windows.Forms.OpenFileDialog openExeDialog;
      private System.Windows.Forms.Label label6;
      private CustomTextBox delayTextBox;
      private System.Windows.Forms.OpenFileDialog openIconDialog;
      private CustomCheckBox persistCheckbox;

   }
}

