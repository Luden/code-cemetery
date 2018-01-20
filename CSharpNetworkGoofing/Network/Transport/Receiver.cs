using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Threading;
using Common;

namespace Network.Transport
{
	public class Receiver
	{
		private Socket _sock;

		private ManualResetEvent _gotData = new ManualResetEvent(false);
		private object _bufferLock = new object();

		private const int START_SIZE = 1024;
		private int _curBufLen = START_SIZE;
		private byte[] _buffer = new byte[START_SIZE];

		private int _writeOffset = 0;
		private int _readOffset = 0;
		private int _readLen = 0;

		private int _currentBlockOffset = 0;
		private int _currentBlockLen = 0;
		private int _totalDataLength = 0;
		private int _estimatedBlockLen = 0;

		public Receiver(Socket sock)
		{
			_sock = sock;
		}

		public void BeginReceive()
		{
			try
			{
				_sock.BeginReceive(_buffer, _writeOffset, _curBufLen - _writeOffset, SocketFlags.None, ReceiveCallback, null);
			}
			catch (Exception ex)
			{
				Log.Error("Receiver abort: {0}", ex.Message);
			}
		}

		private void ReceiveCallback(IAsyncResult ar)
		{
			Monitor.Enter(_bufferLock);

			try
			{
				var received = _sock.EndReceive(ar);
				_totalDataLength += received;
				_currentBlockLen += received;
				_writeOffset += received;
			}
			catch (ObjectDisposedException ex) { Log.Info("Connection aborted: " + ex.Message); Monitor.Exit(_bufferLock); return; }
			catch (SocketException ex) { Log.Info("Connection aborted: " + ex.Message); Monitor.Exit(_bufferLock); return; }

			if (_estimatedBlockLen == 0 && _currentBlockLen >= 4)
				FindEstimates();

			while (_currentBlockLen >= _estimatedBlockLen && _estimatedBlockLen > 0)
				SkipBlock();

			if (_readOffset + GetMinimumBufferLength() >= _curBufLen)
				ManageBuffer();

			BeginReceive();

			Monitor.Exit(_bufferLock);
		}

		private void FindEstimates()
		{
			_estimatedBlockLen = BitConverter.ToInt32(_buffer, _currentBlockOffset);
		}

		private void SkipBlock()
		{
			_currentBlockOffset += _estimatedBlockLen;
			_currentBlockLen -= _estimatedBlockLen;
			_readLen += _estimatedBlockLen;
			_estimatedBlockLen = 0;

			_gotData.Set();

			if (_currentBlockLen >= 4)
				FindEstimates();
		}

		private void ShiftContents()
		{
			Buffer.BlockCopy(_buffer, _currentBlockOffset, _buffer, 0, _currentBlockLen);
		}

		private void ExtendBuffer()
		{
			while (_curBufLen < GetMinimumBufferLength())
				_curBufLen *= 2;

			var newBuf = new byte[_curBufLen];

			Buffer.BlockCopy(_buffer, _readOffset, newBuf, 0, _totalDataLength);
			_buffer = newBuf;
		}

		private int GetMinimumBufferLength()
		{
			return _totalDataLength + Math.Max(_estimatedBlockLen - _currentBlockLen, 0) + 4;
		}

		private void ManageBuffer()
		{
			if (_curBufLen > GetMinimumBufferLength())
				ShiftContents();
			else
				ExtendBuffer();

			_currentBlockOffset -= _readOffset;
			_readOffset = 0;
			_writeOffset = _totalDataLength;
		}

		public bool WaitForData(int millis)
		{
			return _gotData.WaitOne(millis);
		}

		public BinaryReader GetReader()
		{
			Monitor.Enter(_bufferLock);

			if (_readLen <= 4)
				return null;

			int size = BitConverter.ToInt32(_buffer, _readOffset);
			var stream = new MemoryStream(_buffer, _readOffset + 4, size - 4);
			var reader = new BinaryReader(stream);

			_totalDataLength -= size;
			_readOffset += size;
			_readLen -= size;

			if(_readLen == 0)
				_gotData.Reset();

			return reader;
		}

		public void Finish()
		{
			Monitor.Exit(_bufferLock);
		}
	}
}