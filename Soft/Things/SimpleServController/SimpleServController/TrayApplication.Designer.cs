using System.Windows.Forms;

namespace SimpleServController
{
    partial class TrayApplicationContext
    {
        private System.ComponentModel.IContainer components = null;
        private System.Windows.Forms.NotifyIcon TrayIcon;
        private System.Windows.Forms.ContextMenuStrip MainMenu;
        private System.Windows.Forms.Timer PingTimer;
        private System.Windows.Forms.ToolStripMenuItem SwitchOnMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ExitToolStripMenuItem;

        private System.Windows.Forms.ToolStripTextBox MacTextBox;
        private System.Windows.Forms.ToolStripTextBox DnsNameTextBox;
        private System.Windows.Forms.ToolStripMenuItem MacTextBoxName;
        private System.Windows.Forms.ToolStripMenuItem DnsNameTextBoxName;

        System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager();

        protected override void Dispose(bool disposing)
        {
            if (disposing && components != null) { components.Dispose(); }
        }

        private void InitializeContext()
        {
            components = new System.ComponentModel.Container();
            TrayIcon = new NotifyIcon(components);
            MainMenu = new System.Windows.Forms.ContextMenuStrip(components);
            SwitchOnMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ExitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            MacTextBox = new ToolStripTextBox();
            DnsNameTextBox = new ToolStripTextBox();
            MacTextBoxName = new ToolStripMenuItem();
            DnsNameTextBoxName = new ToolStripMenuItem();
            PingTimer = new Timer();

            TrayIcon.ContextMenuStrip = this.MainMenu;
            TrayIcon.Icon = SimpleServController.Properties.Resources.ServCotrolDisabled;
            TrayIcon.Text = "SimpleServController";
            TrayIcon.Visible = true;
            // 
            // MainMenu
            // 
            MainMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            MacTextBoxName,
            MacTextBox,
            DnsNameTextBoxName,
            DnsNameTextBox,
            SwitchOnMenuItem,
            ExitToolStripMenuItem});
            MainMenu.Name = "MainMenu";
            MainMenu.Size = new System.Drawing.Size(140, 70);
            // 
            // SwitchOnMenuItem
            // 
            SwitchOnMenuItem.Name = "SwitchOnMenuItem";
            SwitchOnMenuItem.Size = new System.Drawing.Size(139, 22);
            SwitchOnMenuItem.Text = "Включить";
            SwitchOnMenuItem.Click += new System.EventHandler(SwitchOnMenuItem_Click);
            // 
            // ExitToolStripMenuItem
            // 
            ExitToolStripMenuItem.Name = "ExitToolStripMenuItem";
            ExitToolStripMenuItem.Size = new System.Drawing.Size(139, 22);
            ExitToolStripMenuItem.Text = "Выход";
            ExitToolStripMenuItem.Click += new System.EventHandler(ExitToolStripMenuItem_Click);
            //
            // PingTimer
            //
            PingTimer.Interval = 10000;
            PingTimer.Tick += new System.EventHandler(PingTimer_Tick);
            PingTimer.Enabled = true;
            // 
            // MacTextBox
            // 
            this.MacTextBox.Name = "MacTextBox";
            this.MacTextBox.Size = new System.Drawing.Size(100, 21);
            this.MacTextBox.Text = Properties.Settings.Default.MacAddress;
            // 
            // DnsNameTextBox
            // 
            this.DnsNameTextBox.Name = "DnsNameTextBox";
            this.DnsNameTextBox.Size = new System.Drawing.Size(100, 21);
            this.DnsNameTextBox.Text = Properties.Settings.Default.DnsName;
            // 
            // MacTextBoxName
            // 
            this.MacTextBoxName.Name = "MacTextBoxName";
            this.MacTextBoxName.Size = new System.Drawing.Size(140, 21);
            this.MacTextBoxName.Text = "MAC-адрес компьютера";
            this.MacTextBoxName.Enabled = false;
            // 
            // DnsNameTextBoxName
            // 
            this.DnsNameTextBoxName.Name = "DnsNameTextBoxName";
            this.DnsNameTextBoxName.Size = new System.Drawing.Size(140, 21);
            this.DnsNameTextBoxName.Text = "DNS-имя компьютера";
            this.DnsNameTextBoxName.Enabled = false;
        }
    }
}