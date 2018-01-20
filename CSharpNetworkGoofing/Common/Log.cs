using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Common
{
	public class Log : IDisposable
	{
		private string _fileName;
		private FileStream _log;
		private StreamWriter _writer;

		private string _prefix = "{0} [{1:HH:mm:ss.fff}]: ";

		private static Log _instance = new Log();
		public static Log Instance { get { return _instance; } }

		private Log()
		{
			Open();
		}

		private void Open()
		{
			if (!Directory.Exists(Config.logDir))
				Directory.CreateDirectory(Config.logDir);

			var filesCount = Directory.GetFiles(Config.logDir).Count();
			_fileName = $"log_{filesCount:00000}_{DateTime.Now:dd.MM.yyyy}.txt";

			_log = File.OpenWrite(Path.Combine(Config.logDir, _fileName));
			_writer = new StreamWriter(_log);
		}

		private void LogText(string format, string logType, params object[] args)
		{
			var prefix = string.Format(_prefix, logType, DateTime.Now);
			_writer.WriteLineAsync(string.Format(prefix + format, args));
		}

		public static void Error(string format, params object[] args)
		{
			Instance.LogText(format, "Error", args);
		}

		public static void Info(string format, params object[] args)
		{
			Instance.LogText(format, "Info ", args);
		}

		public static void Wipe()
		{
			_instance.Dispose();

			if (Directory.Exists(Config.logDir))
				Directory.Delete(Config.logDir, true);

			_instance.Open();
		}

		~Log()
		{
			Dispose();
		}

		public void Dispose()
		{
			if (_writer.BaseStream.CanWrite)
				_writer.Close();
		}
	}
}