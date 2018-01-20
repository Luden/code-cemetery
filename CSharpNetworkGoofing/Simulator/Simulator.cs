using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading;

namespace Simulator
{
	public class Simulator
	{
		private const float DT = 0.05f;

		private World _world;

		public void Simulate()
		{
			_world = new World();

			var sw = new Stopwatch();
			var stepSpan = TimeSpan.FromSeconds(DT);

			while (!_world.IsEnded())
			{
				sw.Start();
				_world.Update(DT);
				sw.Stop();

				if (sw.Elapsed < stepSpan)
					Thread.Sleep(stepSpan - sw.Elapsed);
			}
		}
	}
}