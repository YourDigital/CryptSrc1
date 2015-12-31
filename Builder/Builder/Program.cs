using System;
using System.Collections.Generic;
using System.Management;
using System.Windows.Forms;

namespace Builder
{
   static class Program
   {
      [STAThread]
      static void Main()
      {
         Application.EnableVisualStyles();
         Application.SetCompatibleTextRenderingDefault(false);
      //   bool hasLicense = Client.HasLicense();
  //       if (hasLicense)
            new MainForm().Show();
    //     else
      //      new DisabledForm().Show();
         Application.Run();
      }
   }
}
