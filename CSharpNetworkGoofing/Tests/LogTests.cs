using System;
using Common;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Tests
{
	[TestClass]
	public class LogTests
	{
		[TestMethod]
		public void TestWipe()
		{
			Log.Wipe();
		}

		[TestMethod]
		public void TestError()
		{
			Log.Error("Test {0} {1}", 1, "error");
		}

		[TestMethod]
		public void TestWarning()
		{
			Log.Info("Test {0} {1}", 2, "warning");
		}
	}
}
