using System.IO;

namespace Network
{
	public interface IDataReader
	{
		void Read(Stream s);
	}
}