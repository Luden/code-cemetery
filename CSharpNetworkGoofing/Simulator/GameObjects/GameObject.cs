using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Network.Netvars;
using Simulator.Components;

namespace Simulator.GameObjects
{
	public class GameObject : INetvar
	{
		private List<IComponent> _components = new List<IComponent>();

		public virtual void Update(float dt)
		{
			foreach (var component in _components)
				component.Update(dt);
		}

		public bool IsChanged { get; set; }
		public void Read(BinaryReader reader)
		{
			throw new NotImplementedException();
		}

		public void Write(BinaryWriter writer)
		{
			throw new NotImplementedException();
		}
	}
}