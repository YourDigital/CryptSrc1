namespace Builder
{
   partial class DisabledForm
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
            this.keyTextBox = new CustomTextBox();
            this.keyBtn = new CustomButton();
            this.closeButton = new TopCustomButton();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // keyTextBox
            // 
            this.keyTextBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(37)))), ((int)(((byte)(38)))));
            this.keyTextBox.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(241)))), ((int)(((byte)(241)))), ((int)(((byte)(241)))));
            this.keyTextBox.Location = new System.Drawing.Point(15, 76);
            this.keyTextBox.Name = "keyTextBox";
            this.keyTextBox.Size = new System.Drawing.Size(221, 20);
            this.keyTextBox.TabIndex = 3;
            this.keyTextBox.TextChanged += new System.EventHandler(this.keyTextBox_TextChanged);
            // 
            // keyBtn
            // 
            this.keyBtn.Location = new System.Drawing.Point(242, 74);
            this.keyBtn.Name = "keyBtn";
            this.keyBtn.Size = new System.Drawing.Size(77, 23);
            this.keyBtn.TabIndex = 2;
            this.keyBtn.Text = "Submit";
            this.keyBtn.UseVisualStyleBackColor = true;
            this.keyBtn.Click += new System.EventHandler(this.keyBtn_Click);
            // 
            // closeButton
            // 
            this.closeButton.Location = new System.Drawing.Point(301, 4);
            this.closeButton.Name = "closeButton";
            this.closeButton.Size = new System.Drawing.Size(25, 25);
            this.closeButton.TabIndex = 1;
            this.closeButton.Text = "X";
            this.closeButton.UseVisualStyleBackColor = true;
            this.closeButton.Click += new System.EventHandler(this.closeButton_Click);
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(12, 32);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(307, 39);
            this.label1.TabIndex = 0;
            this.label1.Text = "No license found with your hardware ID.\r\nIf you have purchased a key enter it bel" +
    "ow.";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // DisabledForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(331, 108);
            this.Controls.Add(this.keyTextBox);
            this.Controls.Add(this.keyBtn);
            this.Controls.Add(this.closeButton);
            this.Controls.Add(this.label1);
            this.Name = "DisabledForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Cyber Protector";
            this.ResumeLayout(false);
            this.PerformLayout();

      }

      #endregion

      private System.Windows.Forms.Label label1;
      private TopCustomButton closeButton;
      private CustomButton keyBtn;
      private CustomTextBox keyTextBox;
   }
}