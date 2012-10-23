using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using WakeOnLan;
using System.Diagnostics;
using System.Net;
using System.IO;

namespace WrapTorrClient
{
    class TorrClient
    {
        private string ServerMAC;
        private string ServerName;
        private string uTorrentPath;
        private string DownloadsPath;

        public TorrClient(string mac, string name, string uTorrentPath, string downloadsPath)
        {
            ServerMAC = mac;
            ServerName = name;
            this.uTorrentPath = uTorrentPath;
            DownloadsPath = downloadsPath;
        }

        public void TryConnect(string mac, string name)
        {
            
        }

        public bool uTorrentIsWorking()
        {
            return (Process.GetProcessesByName("uTorrent").Count() != 0);
        }

        public void StartUTorrent()
        {
            Process.Start(uTorrentPath, "\\Minimized");
            
        }

        private string GetNormalFile(string fileName)
        {
            if(fileName.StartsWith("http"))
            {
                string newName = fileName.Substring(fileName.LastIndexOf('\\'));

                if(!newName.EndsWith(".torrent"))
                    newName = newName + ".torrent";

                WebClient myWebClient = new WebClient();
                myWebClient.DownloadFile(fileName, DownloadsPath + newName);

                fileName = newName;
            }
            else if (!fileName.EndsWith(".torrent"))
                fileName = fileName + ".torrent";

            if (!File.Exists(fileName)) throw new ApplicationException("Файл торрента не найден");

            return "\"" + fileName + "\"";
        }

        public void DownloadLocaly(string fileName)
        {
            if (!uTorrentIsWorking())
                StartUTorrent();

            fileName = GetNormalFile(fileName);
            
            Process.Start(uTorrentPath, fileName);
        }

        public void GiveWorkToUtorrent(string fileName)
        { }

        public void DownloadRemotely()
        { }

        public bool IsConnected()
        {
            return false;
        }
    }
}
