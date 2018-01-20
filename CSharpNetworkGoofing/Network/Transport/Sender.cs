using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Sockets;

namespace Network.Transport
{
	public class Sender
	{
		private MemoryStream _stream;
		private BinaryWriter _writer;
		private Socket _sock;

		private ConcurrentQueue<byte[]> _pendingSend = new ConcurrentQueue<byte[]>();

		public Sender(Socket sock)
		{
			_sock = sock;
		}

		public BinaryWriter GetWriter()
		{
			_stream = new MemoryStream();
			_writer = new BinaryWriter(_stream);
			_writer.Write(0);
			return _writer;
		}

		public bool Send()
		{
			if (_stream == null)
				return false;

			_stream.Flush();

			if (_stream.Position > 0)
			{
				var pos = (int)_stream.Position;
				_writer.Seek(0, SeekOrigin.Begin);
				_writer.Write(pos);
				_writer.Seek(pos, SeekOrigin.Begin);
			}

			bool sended = false;
			while (_sock.Poll(0, SelectMode.SelectWrite) && (_stream.Position > 0 || _pendingSend.Count > 0))
			{
				byte[] data;
				if (_pendingSend.Count > 0 && _pendingSend.TryDequeue(out data))
				{
					_sock.Send(data);
				}
				else
				{
					_sock.Send(_stream.GetBuffer(), (int) _stream.Position, SocketFlags.None);
					_stream.SetLength(0);
					sended = true;
				}
			}

			if (_stream.Position > 0)
			{
				_pendingSend.Enqueue(_stream.ToArray());
				_stream.SetLength(0);
			}

			return sended || _pendingSend.Count == 0;
		}
	}
}