using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Network.Netvars
{
	public class NetvarBool : Netvar
	{
		public bool Value;

		public override void Read(BinaryReader reader)
		{
			Value = reader.ReadBoolean();
		}

		public override void Write(BinaryWriter writer)
		{
			writer.Write(Value);
		}
	}
}