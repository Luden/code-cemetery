using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using SingletonApp;
using System.Runtime.InteropServices;
using System.Drawing;

namespace WrapTorrClient
{
    public partial class TrayApplicationContext : ApplicationContext
    {
        WrapTorrForm AddTorrentForm;
        OptionsScreen OptionsForm;
        TorrClient TorrClient;

        public TrayApplicationContext() 
        {
            InitializeContext();

            AddTorrentForm = new WrapTorrForm();
            OptionsForm = new OptionsScreen();
            TorrClient = new TorrClient(OptionsForm.MAC, OptionsForm.DNSName, 
                OptionsForm.uTorrentPath, OptionsForm.DownloadsPath);
        }

        private void ProcessGetForm(string path)
        {
            AddTorrentForm.TorrentPathTextBox.Text = path;
            var result = AddTorrentForm.ShowDialog();
            
            if (result == DialogResult.OK)
            {
                if (Uri.IsWellFormedUriString(AddTorrentForm.TorrentPathTextBox.Text, UriKind.Absolute))
                {
                    TorrClient.DownloadLocaly(AddTorrentForm.TorrentPathTextBox.Text);
                }
            }
            else if (result == DialogResult.Yes)
            {
                if (Uri.IsWellFormedUriString(AddTorrentForm.TorrentPathTextBox.Text, UriKind.Absolute))
                {
                    MessageBox.Show("Bam!");
                }
            }
        }

        public void ReceiveMessage(string[] args)
        {
            ProcessGetForm(args[0]);
        }

        private void TrayIcon_DoubleClick(object sender, EventArgs e)
        {
            ProcessGetForm(string.Empty);
        }

        private void OptionsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OptionsForm.ShowDialog();
        }

        private void ExitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ExitThread();
        }
    }
}
