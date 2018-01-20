using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NAudio.Wave;

namespace Mp3Split
{
	class Program
	{
		static void Main(string[] args)
		{
			if (args.Length == 0)
				args = new string[3] {Environment.CurrentDirectory, "Output", "120"};

			if (args.Length < 3)
			{
				Console.WriteLine("Usage: Mp3Split.exe folderWithSource folderWithOutput fileLength");
				return;
			}

			var inputFolder = args[0];
			if (!Directory.Exists(inputFolder))
			{
				Console.WriteLine("Input directory does not exist");
				return;
			}

			var outputFolder = args[1];
			if (Directory.Exists(outputFolder))
				Directory.Delete(outputFolder, true);
			Directory.CreateDirectory(outputFolder);

			var length = 0;
			if (!Int32.TryParse(args[2], out length))
			{
				Console.WriteLine("Incorrect file length");
				return;
			}

			var program = new Program();
			program.Execute(inputFolder, outputFolder, length);
		}

		private string CreateOutFileName(string outputFolder, string inputFile, int index)
		{
			return Path.Combine(Path.GetFullPath(outputFolder), string.Concat(Path.GetFileNameWithoutExtension(inputFile), "_", index.ToString("D3"), ".mp3"));
		}

		public void Execute(string inputFolder, string outputFolder, int length)
		{
			Directory.GetFiles(inputFolder, "*.mp3").AsParallel().ForAll(x =>
				ProcessFile(outputFolder, length, x));
		}

		private void ProcessFile(string outputFolder, int length, string fileName)
		{
			Console.WriteLine("File processing: {0}", Path.GetFileName(fileName));

			using (var reader = new Mp3FileReader(fileName))
			{
				int index = 1;

				var writer = File.Create(CreateOutFileName(outputFolder, fileName, index));
				Mp3Frame frame;
				while ((frame = reader.ReadNextFrame()) != null)
				{
					if (reader.CurrentTime.TotalSeconds >= length*index)
					{
						writer.Close();
						index++;
						writer = File.Create(CreateOutFileName(outputFolder, fileName, index));
					}

					writer.Write(frame.RawData, 0, frame.RawData.Length);
				}
			}
		}
	}
}
