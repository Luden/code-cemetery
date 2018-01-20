using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Network.Netvars;

namespace Network
{
	public class NetWatcher : INetvar
	{
		private readonly List<INetvar> _netvars = new List<INetvar>();

		public bool IsChanged
		{
			get { return _netvars.Any(x => x.IsChanged); }
			set { }
		}

		public NetvarBool GetBool()
		{
			var netvar = new NetvarBool();
			_netvars.Add(netvar);
			return netvar;
		}

		public NetvarFloat GetFloat()
		{
			var netvar = new NetvarFloat();
			_netvars.Add(netvar);
			return netvar;
		}

		public NetvarInt GetInt()
		{
			var netvar = new NetvarInt();
			_netvars.Add(netvar);
			return netvar;
		}

		public void RegisterClass(INetvar netvar)
		{
			_netvars.Add(netvar);
		}

		public void Write(BinaryWriter writer)
		{
			var changeds = (byte)_netvars.Count(x => x.IsChanged);
			writer.Write(changeds);

			for (var i = 0; i < _netvars.Count; i++)
			{
				if (!_netvars[i].IsChanged)
					continue;

				writer.Write((byte)i);
				_netvars[i].Write(writer);
				_netvars[i].IsChanged = false;
			}
		}

		public void Read(BinaryReader reader)
		{
			var changeds = reader.ReadByte();
			for (var i = 0; i < changeds; i++)
			{
				var id = reader.ReadByte();
				if (id >= _netvars.Count)
					throw new ApplicationException("Protocol corruption");

				_netvars[id].Read(reader);
			}
		}
	}
}