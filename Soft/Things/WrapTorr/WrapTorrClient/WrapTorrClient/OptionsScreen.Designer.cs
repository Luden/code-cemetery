namespace WrapTorrClient
{
    partial class OptionsScreen
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.OkButton = new System.Windows.Forms.Button();
            this.CancelButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.DownloadsPathTextBox = new System.Windows.Forms.TextBox();
            this.uTorrentPathTextBox = new System.Windows.Forms.TextBox();
            this.DNSNameTextBox = new System.Windows.Forms.TextBox();
            this.MACTextBox = new System.Windows.Forms.MaskedTextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // OkButton
            // 
            this.OkButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.OkButton.Location = new System.Drawing.Point(152, 210);
            this.OkButton.Name = "OkButton";
            this.OkButton.Size = new System.Drawing.Size(75, 23);
            this.OkButton.TabIndex = 0;
            this.OkButton.Text = "OK";
            this.OkButton.UseVisualStyleBackColor = true;
            this.OkButton.Click += new System.EventHandler(this.OkButton_Click);
            // 
            // CancelButton
            // 
            this.CancelButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.CancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.CancelButton.Location = new System.Drawing.Point(233, 210);
            this.CancelButton.Name = "CancelButton";
            this.CancelButton.Size = new System.Drawing.Size(75, 23);
            this.CancelButton.TabIndex = 0;
            this.CancelButton.Text = "Отмена";
            this.CancelButton.UseVisualStyleBackColor = true;
            this.CancelButton.Click += new System.EventHandler(this.CancelButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 16);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "MAC";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 43);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(56, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "DNS name";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 16);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(74, 13);
            this.label4.TabIndex = 2;
            this.label4.Text = "uTorrent path";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(5, 64);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(84, 13);
            this.label5.TabIndex = 2;
            this.label5.Text = "Downloads path";
            // 
            // DownloadsPathTextBox
            // 
            this.DownloadsPathTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.DownloadsPathTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", global::WrapTorrClient.Properties.Settings.Default, "DownloadsPath", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.DownloadsPathTextBox.Location = new System.Drawing.Point(8, 80);
            this.DownloadsPathTextBox.Name = "DownloadsPathTextBox";
            this.DownloadsPathTextBox.Size = new System.Drawing.Size(282, 20);
            this.DownloadsPathTextBox.TabIndex = 4;
            this.DownloadsPathTextBox.Text = global::WrapTorrClient.Properties.Settings.Default.DownloadsPath;
            // 
            // uTorrentPathTextBox
            // 
            this.uTorrentPathTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.uTorrentPathTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", global::WrapTorrClient.Properties.Settings.Default, "uTorrentLocation", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.uTorrentPathTextBox.Location = new System.Drawing.Point(8, 32);
            this.uTorrentPathTextBox.Name = "uTorrentPathTextBox";
            this.uTorrentPathTextBox.Size = new System.Drawing.Size(282, 20);
            this.uTorrentPathTextBox.TabIndex = 4;
            this.uTorrentPathTextBox.Text = global::WrapTorrClient.Properties.Settings.Default.uTorrentLocation;
            // 
            // DNSNameTextBox
            // 
            this.DNSNameTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", global::WrapTorrClient.Properties.Settings.Default, "ServerDNSName", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.DNSNameTextBox.Location = new System.Drawing.Point(64, 39);
            this.DNSNameTextBox.Name = "DNSNameTextBox";
            this.DNSNameTextBox.Size = new System.Drawing.Size(103, 20);
            this.DNSNameTextBox.TabIndex = 3;
            this.DNSNameTextBox.Text = global::WrapTorrClient.Properties.Settings.Default.ServerDNSName;
            // 
            // MACTextBox
            // 
            this.MACTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", global::WrapTorrClient.Properties.Settings.Default, "ServerMAC", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.MACTextBox.Location = new System.Drawing.Point(64, 13);
            this.MACTextBox.Mask = ">AA-AA-AA-AA-AA-AA|";
            this.MACTextBox.Name = "MACTextBox";
            this.MACTextBox.Size = new System.Drawing.Size(103, 20);
            this.MACTextBox.TabIndex = 1;
            this.MACTextBox.Text = global::WrapTorrClient.Properties.Settings.Default.ServerMAC;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.MACTextBox);
            this.groupBox1.Controls.Add(this.DNSNameTextBox);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(296, 67);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Сервер";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.DownloadsPathTextBox);
            this.groupBox2.Controls.Add(this.uTorrentPathTextBox);
            this.groupBox2.Location = new System.Drawing.Point(12, 85);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(296, 117);
            this.groupBox2.TabIndex = 5;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Клиент";
            // 
            // OptionsScreen
            // 
            this.AcceptButton = this.OkButton;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.CancelButton;
            this.ClientSize = new System.Drawing.Size(320, 245);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.CancelButton);
            this.Controls.Add(this.OkButton);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "OptionsScreen";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Настройки";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button OkButton;
        private System.Windows.Forms.Button CancelButton;
        private System.Windows.Forms.MaskedTextBox MACTextBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox DNSNameTextBox;
        private System.Windows.Forms.TextBox uTorrentPathTextBox;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox DownloadsPathTextBox;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
    }
}