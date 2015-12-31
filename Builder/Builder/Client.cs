using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.IO;
using System.Management;
using System.Net;
using System.Reflection;
using System.Text;
using System.Windows.Forms;

namespace Builder
{
   class Client
   {
      static string uhid = GetMachineGuid();
      const string page = "http://87.120.37.88/license/client.php";
      const string successStr = "OK";
      const string errorStr = "FUCKOFF";
      const bool customStub = true;
      const string version = "v1.4";
      static string GetMachineGuid()
      {
         string location = @"SOFTWARE\Microsoft\Cryptography";
         string name = "MachineGuid";

         using (RegistryKey localMachineX64View =
             RegistryKey.OpenBaseKey(RegistryHive.LocalMachine, RegistryView.Registry64))
         {
            using (RegistryKey rk = localMachineX64View.OpenSubKey(location))
            {
               if (rk == null)
                  throw new KeyNotFoundException(
                      string.Format("Key Not Found: {0}", location));

               object machineGuid = rk.GetValue(name);
               if (machineGuid == null)
                  throw new IndexOutOfRangeException(
                      string.Format("Index Not Found: {0}", name));

               return machineGuid.ToString();
            }
         }
      }
      public static bool NeedsUpdate()
      {
         if (customStub)
            return false;
         using (CustomWebClient client = new CustomWebClient())
         {
            client.Proxy = null;
            try
            {
               string content = client.DownloadString(page + "?ver=" + version);
               if (content == successStr)
                  return false;
            }
            catch
            {
               ServerOffline();
               return false;
            }
         }
         return true;
      }
      public static bool SendKey(string key)
      {
         using (CustomWebClient client = new CustomWebClient())
         {
            try
            {
               string content = client.DownloadString(page + "?uhid=" + uhid + "&key=" + key);
               if (content == successStr)
                  return true;
            }
            catch
            {
               ServerOffline();
               return true;
            }
         }
         return true;
      }

      static void ServerOffline()
      {
         MessageBox.Show("Server is offline!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
         System.Environment.Exit(1);
      }

      public static bool DownloadStub()
      {
         if (customStub)
            return true;
         using (CustomWebClient client = new CustomWebClient())
         {
            try
            {
               byte[] stubBytes = client.DownloadData(page + "?uhid=" + uhid + "&action=STUB");
               if (System.Text.Encoding.ASCII.GetString(stubBytes) != errorStr)
               {
                  File.WriteAllBytes("stub.exe", stubBytes);
                  return true;
               }
            }
            catch
            {
               ServerOffline();
               return true;
            }
         }
         return false;
      }
      public static bool HasLicense()
      {
         using (CustomWebClient client = new CustomWebClient())
         {
            try
            {
               string content = client.DownloadString(page + "?uhid=" + uhid);
               if (content == successStr)
                  return true;
            }
            catch
            {
               ServerOffline();
               return true;
            }
         }
         return false;
      }
   }
}

public class CustomWebClient : WebClient
{
   public CustomWebClient()
   {
      this.Proxy = null;
   }
}