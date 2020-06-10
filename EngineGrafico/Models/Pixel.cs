using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;

namespace EngineGrafico.Models
{
	public class Pixel : IEquatable<Pixel>
	{
		public ushort R { get; set; }
		public ushort G { get; set; }
		public ushort B { get; set; }
		public ushort A { get; set; }

		public Pixel(ushort r, ushort g, ushort b, ushort a)
		{
			R = r;
			G = g;
			B = b;
			A = a;
		}

		public override bool Equals(object obj)
		{
			return Equals(obj as Pixel);
		}

		public bool Equals([AllowNull] Pixel other)
		{
			return other != null &&
				   R == other.R &&
				   G == other.G &&
				   B == other.B &&
				   A == other.A;
		}

		public override int GetHashCode()
		{
			return HashCode.Combine(R, G, B, A);
		}

		public static bool operator ==(Pixel left, Pixel right)
		{
			return EqualityComparer<Pixel>.Default.Equals(left, right);
		}

		public static bool operator !=(Pixel left, Pixel right)
		{
			return !(left == right);
		}
	}
}
