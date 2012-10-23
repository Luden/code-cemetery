using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using SingletonApp;
using System.Runtime.InteropServices;
using System.Drawing;

namespace WrapTorrClient
{
    static class TrayApplication
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            TrayApplicationContext applicationContext = new TrayApplicationContext();

            if (SingletonController.IamFirst(new
                SingletonController.ReceiveDelegate(applicationContext.ReceiveMessage)))
            {
                Application.Run(applicationContext);
            }
            else
            {
                SingletonController.Send(args);
            }

            SingletonController.Cleanup();
        }
    }
}