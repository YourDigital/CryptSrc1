using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Builder
{
   public partial class DisabledForm : CustomForm
   {
      public DisabledForm()
      {
         InitializeComponent();
      }

      private void closeButton_Click(object sender, EventArgs e)
      {
         Application.Exit();
      }

      private void keyBtn_Click(object sender, EventArgs e)
      {
          new MainForm().Show();
          this.Hide();
         if (Client.SendKey(keyTextBox.Text))
         {
            new MainForm().Show();
            this.Hide();
         }
         else
         {
            MessageBox.Show("Invalid Key!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
         }
      }

        private void keyTextBox_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
