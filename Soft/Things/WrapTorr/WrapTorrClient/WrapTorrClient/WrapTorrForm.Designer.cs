namespace WrapTorrClient
{
    partial class WrapTorrForm
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
            this.AddLocalButton = new System.Windows.Forms.Button();
            this.AddRemotelyButton = new System.Windows.Forms.Button();
            this.TorrentPathTextBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // AddLocalButton
            // 
            this.AddLocalButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.AddLocalButton.Location = new System.Drawing.Point(149, 250);
            this.AddLocalButton.Name = "AddLocalButton";
            this.AddLocalButton.Size = new System.Drawing.Size(139, 23);
            this.AddLocalButton.TabIndex = 0;
            this.AddLocalButton.Text = "Скачать локально";
            this.AddLocalButton.UseVisualStyleBackColor = true;
            this.AddLocalButton.Click += new System.EventHandler(this.AddLocalButton_Click);
            // 
            // AddRemotelyButton
            // 
            this.AddRemotelyButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.AddRemotelyButton.Location = new System.Drawing.Point(294, 250);
            this.AddRemotelyButton.Name = "AddRemotelyButton";
            this.AddRemotelyButton.Size = new System.Drawing.Size(139, 23);
            this.AddRemotelyButton.TabIndex = 1;
            this.AddRemotelyButton.Text = "Скачать сервером";
            this.AddRemotelyButton.UseVisualStyleBackColor = true;
            this.AddRemotelyButton.Click += new System.EventHandler(this.AddRemotelyButton_Click);
            // 
            // TorrentPathTextBox
            // 
            this.TorrentPathTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.TorrentPathTextBox.Location = new System.Drawing.Point(12, 29);
            this.TorrentPathTextBox.Multiline = true;
            this.TorrentPathTextBox.Name = "TorrentPathTextBox";
            this.TorrentPathTextBox.Size = new System.Drawing.Size(421, 215);
            this.TorrentPathTextBox.TabIndex = 3;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(79, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Торрент-файл";
            // 
            // WrapTorrForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(445, 285);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.TorrentPathTextBox);
            this.Controls.Add(this.AddRemotelyButton);
            this.Controls.Add(this.AddLocalButton);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.MaximizeBox = false;
            this.Name = "WrapTorrForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "WrapTorr";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button AddLocalButton;
        private System.Windows.Forms.Button AddRemotelyButton;
        public System.Windows.Forms.TextBox TorrentPathTextBox;
        private System.Windows.Forms.Label label1;
    }
}

