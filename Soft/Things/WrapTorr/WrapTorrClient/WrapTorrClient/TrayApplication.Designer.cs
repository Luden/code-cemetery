using System.Windows.Forms;

namespace WrapTorrClient
{
    partial class TrayApplicationContext
    {
        private System.ComponentModel.IContainer components = null;
        private System.Windows.Forms.NotifyIcon TrayIcon;
        private System.Windows.Forms.ContextMenuStrip MainMenu;
        private System.Windows.Forms.ToolStripMenuItem AddToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem OptionsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ExitToolStripMenuItem;
        System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(WrapTorrForm));

        protected override void Dispose(bool disposing)
        {
            if (disposing && components != null) { components.Dispose(); }
        }

        private void InitializeContext()
        {
            components = new System.ComponentModel.Container();
            TrayIcon = new NotifyIcon(components);
            MainMenu = new System.Windows.Forms.ContextMenuStrip(components);
            AddToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            OptionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ExitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            //MainMenu.SuspendLayout();

            TrayIcon.ContextMenuStrip = this.MainMenu;
            TrayIcon.Icon = WrapTorrClient.Properties.Resources.torr;
            //TrayIcon.Icon = new System.Drawing.Icon("torr.ico");
            TrayIcon.Text = "WrapTorr";
            TrayIcon.Visible = true;
            TrayIcon.DoubleClick += new System.EventHandler(TrayIcon_DoubleClick);

            // 
            // MainMenu
            // 
            MainMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            AddToolStripMenuItem,
            OptionsToolStripMenuItem,
            ExitToolStripMenuItem});
            MainMenu.Name = "MainMenu";
            MainMenu.Size = new System.Drawing.Size(140, 70);
            // 
            // AddToolStripMenuItem
            // 
            AddToolStripMenuItem.Name = "AddToolStripMenuItem";
            AddToolStripMenuItem.Size = new System.Drawing.Size(139, 22);
            AddToolStripMenuItem.Text = "Добавить";
            AddToolStripMenuItem.Click += new System.EventHandler(TrayIcon_DoubleClick);
            // 
            // OptionsToolStripMenuItem
            // 
            OptionsToolStripMenuItem.Name = "OptionsToolStripMenuItem";
            OptionsToolStripMenuItem.Size = new System.Drawing.Size(139, 22);
            OptionsToolStripMenuItem.Text = "Настройки";
            OptionsToolStripMenuItem.Click += new System.EventHandler(OptionsToolStripMenuItem_Click);
            // 
            // ExitToolStripMenuItem
            // 
            ExitToolStripMenuItem.Name = "ExitToolStripMenuItem";
            ExitToolStripMenuItem.Size = new System.Drawing.Size(139, 22);
            ExitToolStripMenuItem.Text = "Выход";
            ExitToolStripMenuItem.Click += new System.EventHandler(ExitToolStripMenuItem_Click);

            
        }
    }
}