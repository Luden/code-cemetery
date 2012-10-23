using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WrapTorrClient
{
    public partial class OptionsScreen : Form
    {
        public string MAC
        {
            get
            {
                return MACTextBox.Text;
            }
        }

        public string DNSName
        {
            get 
            {
                return DNSNameTextBox.Text;
            }
        }

        public string uTorrentPath
        {
            get
            {
                return uTorrentPathTextBox.Text;
            }
        }

        public string DownloadsPath
        {
            get
            {
                return DownloadsPathTextBox.Text;
            }
        }

        public OptionsScreen()
        {
            InitializeComponent();
        }

        private void OkButton_Click(object sender, EventArgs e)
        {
            Properties.Settings.Default.Save();
            DialogResult = DialogResult.OK;
        }

        private void CancelButton_Click(object sender, EventArgs e)
        {
            Properties.Settings.Default.Reload();
            DialogResult = DialogResult.Cancel;
        }
    }
}
