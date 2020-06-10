using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Text;

namespace EngineGrafico.Models
{
	public class PixelF : IEquatable<PixelF>
	{
		public float R { get; set; }
		public float G { get; set; }
		public float B { get; set; }
		public float A { get; set; }

		public override bool Equals(object obj)
		{
			return Equals(obj as PixelF);
		}

		public bool Equals([AllowNull] PixelF other)
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

		public static bool operator ==(PixelF left, PixelF right)
		{
			return EqualityComparer<PixelF>.Default.Equals(left, right);
		}

		public static bool operator !=(PixelF left, PixelF right)
		{
			return !(left == right);
		}
	}
}
