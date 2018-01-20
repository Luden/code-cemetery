using System;
using System.Collections.Generic;
using System.Linq;
using Common;
using Network.Transport;
using Simulator.GameObjects;
using Simulator.Players;

namespace Simulator
{
    public class World
    {
		private float _time;

		private readonly List<GameObject> _objects = new List<GameObject>();
		private readonly List<Player> _players = new List<Player>();

		private readonly NetServer _server = new NetServer();
	    //private readonly PlayerFactory _playerFactory = new PlayerFactory();

	    public void Load()
	    {
		    _server.StartListen(Config.address, Config.port);
	    }

	    public void Update(float dt)
	    {
			_time += dt;

		    var newClient = _server.PollClient();
		    if (newClient != null)
			    _players.Add(new RemotePlayer(newClient));

		    for (var i = 0; i < _objects.Count; i++)
			    _objects[i].Update(dt);

		    foreach (var player in _players)
			    player.Update(dt);

		    MakeSnapshot();
	    }

	    private void MakeSnapshot()
	    {
		    foreach (var player in _players)
		    {

		    }
	    }

	    public bool IsEnded()
	    {
			return false;
	    }
    }
}
