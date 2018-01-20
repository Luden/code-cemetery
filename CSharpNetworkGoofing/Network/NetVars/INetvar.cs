using System.IO;

namespace Network.Netvars
{
	public interface INetvar
	{
		bool IsChanged { get; set; }

		void Read(BinaryReader reader);
		void Write(BinaryWriter writer);
	}
}