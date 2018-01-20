using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using Common;

namespace Network.Transport
{
	public class NetServer
	{
		private ConcurrentQueue<NetClient> _clients = new ConcurrentQueue<NetClient>();
		private ManualResetEvent _gotClient = new ManualResetEvent(false);
		private Socket _listener;

		public bool StartListen(string address, int port)
		{
			var ipHostInfo = Dns.GetHostEntry(address);
			var ipAddress = ipHostInfo.AddressList.First(x => !x.IsIPv6LinkLocal);
			var localEndPoint = new IPEndPoint(ipAddress, port);
			_listener = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

			try
			{
				_listener.Bind(localEndPoint);
				_listener.Listen(100);

				Log.Info("NetServer: Waiting for a connection...");
				_listener.BeginAccept(new AsyncCallback(AcceptCallback), _listener);
				return true;
			}
			catch (Exception e)
			{
				Log.Error(e.ToString());
				return false;
			}
		}

		private void AcceptCallback(IAsyncResult ar)
		{
			try
			{
				Socket listener = (Socket) ar.AsyncState;
				Socket handler = listener.EndAccept(ar);

				var client = new NetClient(handler);
				_clients.Enqueue(client);

				_gotClient.Set();

				Log.Info("NetServer: Client connected: {0}", handler.RemoteEndPoint);
				Log.Info("NetServer: Waiting for another connection...");

				listener.BeginAccept(new AsyncCallback(AcceptCallback), listener);
			}
			catch (Exception e)
			{
				Log.Error(e.ToString());
			}
		}

		public bool WaitForClient(int millis)
		{
			return _gotClient.WaitOne(millis);
		}

		public NetClient PollClient()
		{
			NetClient result;
			if (_clients.Count > 0 && _clients.TryDequeue(out result))
			{
				if (_clients.Count == 0)
					_gotClient.Reset();
				return result;
			}

			return null;
		}

		public void StopListen()
		{
			if (_listener != null)
			{
				_listener.Close();
				_listener = null;
			}
		}
	}
}