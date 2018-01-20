using System;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using Common;

namespace Network.Transport
{
	public class NetClient
	{
		private Socket _sock;
		private Receiver _receiver;
		private Sender _sender;

		public NetClient(string address, int port)
		{
			try
			{
				IPHostEntry ipHostInfo = Dns.GetHostEntry(address);
				IPAddress ipAddress = ipHostInfo.AddressList.First(x => !x.IsIPv6LinkLocal);
				IPEndPoint remoteEP = new IPEndPoint(ipAddress, port);

				_sock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
				_sock.Connect(remoteEP);
				Init();
			}
			catch (Exception e)
			{
				Log.Error(e.ToString());
				_sock = null;
			}
		}

		public NetClient(Socket socket)
		{
			_sock = socket;
			Init();
		}

		private void Init()
		{
			_receiver = new Receiver(_sock);
			_sender = new Sender(_sock);

			_receiver.BeginReceive();
		}

		public BinaryWriter GetWriter()
		{
			return _sender.GetWriter();
		}

		public BinaryReader GetReader()
		{
			return _receiver.GetReader();
		}

		public bool WaitForData(int millis)
		{
			return _receiver.WaitForData(millis);
		}

		public bool Send()
		{
			return _sender.Send();
		}

		public void FinishRead()
		{
			_receiver.Finish();
		}

		public void Stop()
		{
			_sock.Close();
			_sock = null;
		}

		public bool IsClosed()
		{
			return _sock == null;
		}
	}
}