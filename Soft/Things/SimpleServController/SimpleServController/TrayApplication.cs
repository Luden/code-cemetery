using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Drawing;
using System.Net.NetworkInformation;

namespace SimpleServController
{
    public partial class TrayApplicationContext : ApplicationContext
    {
        bool IsWorking = false;
        Ping ping;
        PingReply reply;

        public TrayApplicationContext() 
        {
            InitializeContext();
            ping = new Ping();
        }

        private void ExitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Properties.Settings.Default.MacAddress = MacTextBox.Text;
            Properties.Settings.Default.DnsName = DnsNameTextBox.Text;
            Properties.Settings.Default.Save();
            ExitThread();
        }

        void SwitchOnMenuItem_Click(object sender, System.EventArgs e)
        {
            if (MacTextBox.Text == string.Empty) return;
            if (DnsNameTextBox.Text == string.Empty) return;

            if (IsWorking)
            {
                System.Diagnostics.Process proc = new System.Diagnostics.Process();
                proc.EnableRaisingEvents = false;
                proc.StartInfo.FileName = "shutdown";
                proc.StartInfo.Arguments = "-m \\\\"+DnsNameTextBox.Text+" -s -t 0";
                proc.StartInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
                proc.Start();
            }
            else
            {
                WakeOnLan.ProgramWaker.WakeUp(MacTextBox.Text);
            }
        }

        void PingTimer_Tick(object sender, System.EventArgs e)
        {
            if (DnsNameTextBox.Text != string.Empty)
            {
                try
                {
                    reply = ping.Send("HIGHVOLTAGE", 100);
                    if (reply.Status == IPStatus.Success)
                    {
                        IsWorking = true;
                        TrayIcon.Icon = SimpleServController.Properties.Resources.ServCotrolEnabled;
                        SwitchOnMenuItem.Text = "Выключить";
                    }
                    else
                    {
                        IsWorking = false;
                        TrayIcon.Icon = SimpleServController.Properties.Resources.ServCotrolDisabled;
                        SwitchOnMenuItem.Text = "Включить";
                    }
                }
                catch (System.Net.NetworkInformation.PingException ex)
                {
                    IsWorking = false;
                    TrayIcon.Icon = SimpleServController.Properties.Resources.ServCotrolDisabled;
                    SwitchOnMenuItem.Text = "Включить";
                }
            }
        }
    }
}
