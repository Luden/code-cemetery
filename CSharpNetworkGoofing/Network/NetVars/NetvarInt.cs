using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Network.Netvars
{
	public class NetvarInt : Netvar
	{
		public float Value;

		public override void Read(BinaryReader reader)
		{
			Value = reader.ReadSingle();
		}

		public override void Write(BinaryWriter writer)
		{
			writer.Write(Value);
		}
	}
}