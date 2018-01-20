using System.IO;

namespace Network
{
	public interface IDataWriter
	{
		void Write(Stream stream);
	}
}