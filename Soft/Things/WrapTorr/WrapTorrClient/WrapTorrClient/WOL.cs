using System;
using System.Net;
using System.Net.Sockets;

namespace WakeOnLan
{
    class ProgramWaker
    {
        /// <summary>
        /// Sends a Wake-On-Lan packet to the specified MAC address.
        /// </summary>
        /// <param name="mac">Physical MAC address to send WOL packet to.</param>

        public static void WakeUp(string mac)
        {
            byte [] packet = new byte[6];
            for (int i = 0; i < 6; i++)
            {
                string byteStr = "0x" + mac[i * 2] + mac[i * 2 + 1];
                byte bytic;
                if (!byte.TryParse(byteStr, out bytic))
                    throw new ApplicationException("Ты чо за мак там написал, а? Пиши нормально давай!");
                packet[i] = bytic;
            }

            WakeUp(packet);
        }
        
        public static void WakeUp(byte[] mac)
        {
            //
            // WOL packet is sent over UDP 255.255.255.0:40000.
            //
            UdpClient client = new UdpClient();
            client.Connect(IPAddress.Broadcast, 40000);

            //
            // WOL packet contains a 6-bytes trailer and 16 times a 6-bytes sequence containing the MAC address.
            //
            byte[] packet = new byte[17 * 6];

            //
            // Trailer of 6 times 0xFF.
            //
            for (int i = 0; i < 6; i++)
                packet[i] = 0xFF;

            //
            // Body of magic packet contains 16 times the MAC address.
            //
            for (int i = 1; i <= 16; i++)
                for (int j = 0; j < 6; j++)
                    packet[i * 6 + j] = mac[j];

            //
            // Submit WOL packet.
            //
            client.Send(packet, packet.Length);
        }
    }
}