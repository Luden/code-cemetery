using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Network.Netvars
{
	public abstract class Netvar : INetvar
	{
		public bool IsChanged { get; set; }

		public abstract void Read(BinaryReader reader);
		public abstract void Write(BinaryWriter writer);
	}
}