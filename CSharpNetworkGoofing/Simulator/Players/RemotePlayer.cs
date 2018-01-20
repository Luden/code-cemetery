using System;
using System.Collections.Generic;
using System.Linq;
using Network.Transport;

namespace Simulator.Players
{
	public class RemotePlayer : Player
	{
		NetClient _client;

		public RemotePlayer(NetClient client)
		{
		}
	}
}