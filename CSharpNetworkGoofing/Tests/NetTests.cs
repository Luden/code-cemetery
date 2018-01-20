using System;
using System.Threading;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Network.Transport;
using System.Linq;

namespace Tests
{
	[TestClass]
	public class NetTests
	{
		string address = "127.0.0.1";
		int port = 4242;

		[TestMethod]
		public void TestConnection()
		{
			var server = new NetServer();
			server.StartListen(address, port);

			var client = new NetClient(address, port);

			Assert.IsTrue(server.WaitForClient(1000));

			var serverClient = server.PollClient();
			Assert.IsNotNull(serverClient);

			client.Stop();
			serverClient.Stop();
			server.StopListen();
		}

		[TestMethod]
		public void TestConnectionFail()
		{
			var server = new NetServer();
			Assert.IsTrue(server.StartListen(address, port));

			var server2 = new NetServer();
			Assert.IsFalse(server2.StartListen(address, port));

			server.StopListen();
		}

		[TestMethod]
		public void ClientFaultyServer()
		{
			var client = new NetClient(address, port);
			Assert.IsTrue(client.IsClosed());
		}

		[TestMethod]
		public void TestClientCantSend()
		{
			var server = new NetServer();
			server.StartListen(address, port);

			var client = new NetClient(address, port);
			Assert.IsFalse(client.Send());

			client.Stop();
			server.StopListen();
		}

		[TestMethod]
		public void ServerNoClient()
		{
			var server = new NetServer();
			server.StartListen(address, port);

			Assert.IsFalse(server.WaitForClient(0));
			Assert.IsNull(server.PollClient());

			server.StopListen();
		}

		[TestMethod]
		public void ReceiverNothingToRead()
		{
			var server = new NetServer();
			server.StartListen(address, port);

			var client = new NetClient(address, port);
			server.WaitForClient(1000);
			var serverClient = server.PollClient();

			Assert.IsNull(serverClient.GetReader());

			client.Stop();
			serverClient.Stop();
			server.StopListen();
		}

		[TestMethod]
		public void TestCommunication()
		{
			var server = new NetServer();
			server.StartListen(address, port);

			var client = new NetClient(address, port);
			server.WaitForClient(1000);
			var serverClient = server.PollClient();

			var writer = client.GetWriter();

			var stringData = "some text for testing";
			var intData = 42;
			writer.Write(stringData);
			writer.Write(intData);
			client.Send();

			writer = serverClient.GetWriter();
			writer.Write(stringData);
			writer.Write(intData);
			serverClient.Send();

			bool received = serverClient.WaitForData(1000);
			Assert.IsTrue(received);

			var reader = serverClient.GetReader();
			Assert.IsTrue(reader.ReadString() == stringData);
			Assert.IsTrue(reader.ReadInt32() == intData);
			serverClient.FinishRead();

			received = client.WaitForData(1000);
			Assert.IsTrue(received);
			reader = client.GetReader();
			Assert.IsTrue(reader.ReadString() == stringData);
			Assert.IsTrue(reader.ReadInt32() == intData);
			client.FinishRead();

			client.Stop();
			serverClient.Stop();
			server.StopListen();
		}

		[TestMethod]
		public void TestBufferGrowth()
		{
			var server = new NetServer();
			server.StartListen(address, port);

			var client = new NetClient(address, port);
			server.WaitForClient(1000);
			var serverClient = server.PollClient();

			var writer = client.GetWriter();
			var size = 1024;
			var bigData = new byte[size];
			for (int i = 0; i < size; i++)
				bigData[i] = 1;

			// growth

			writer.Write(size);
			writer.Write(bigData);
			client.Send();

			bool received = serverClient.WaitForData(1000);
			Assert.IsTrue(received);

			var reader = serverClient.GetReader();
			var receivedSize = reader.ReadInt32();
			Assert.IsTrue(receivedSize == size);

			var receivedArray = reader.ReadBytes(receivedSize);
			Assert.IsTrue(receivedArray.Sum(x => x) == bigData.Sum(x => x));
			serverClient.FinishRead();

			// shift

			writer = client.GetWriter();
			writer.Write(bigData);
			client.Send();

			received = serverClient.WaitForData(1000);
			Assert.IsTrue(received);
			reader = serverClient.GetReader();
			receivedArray = reader.ReadBytes(receivedSize);
			Assert.IsTrue(receivedArray.Sum(x => x) == bigData.Sum(x => x));
			serverClient.FinishRead();

			client.Stop();
			serverClient.Stop();
			server.StopListen();
		}

		[TestMethod]
		public void TestClientLoad()
		{
			var server = new NetServer();
			server.StartListen(address, port);

			var client = new NetClient(address, port);
			server.WaitForClient(1000);
			var serverClient = server.PollClient();

			var size = 1024;
			var bigData = new byte[size];

			var sended = true;
			int totalSent = 0;
			while (sended)
			{
				var writer = client.GetWriter();
				writer.Write(bigData);
				sended = client.Send();
				if (sended)
					totalSent++;
			}

			Assert.IsFalse(sended);

			int totalReceived = 0;
			while (serverClient.WaitForData(100))
			{
				var reader = serverClient.GetReader();
				reader.ReadBytes(size);
				totalReceived++;
				serverClient.FinishRead();
			}

			Assert.IsTrue(totalSent == totalReceived, "Sended {0}, Received {1}", totalSent, totalReceived);
			Assert.IsTrue(client.Send());

			client.Stop();
			serverClient.Stop();
			server.StopListen();
		}
	}
}
