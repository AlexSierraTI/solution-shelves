using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;

namespace EngineGrafico.Models
{
	public class Vec2d : IEquatable<Vec2d>
	{
		public float X { get; set; }
		public float Y { get; set; }

		public Vec2d(float x, float y)
		{
			X = x;
			Y = y;
		}

		public override bool Equals(object obj)
		{
			return Equals(obj as Vec2d);
		}

		public bool Equals([AllowNull] Vec2d other)
		{
			return other != null &&
				   X == other.X &&
				   Y == other.Y;
		}

		public override int GetHashCode()
		{
			return HashCode.Combine(X, Y);
		}

		public static bool operator ==(Vec2d left, Vec2d right)
		{
			return EqualityComparer<Vec2d>.Default.Equals(left, right);
		}

		public static bool operator !=(Vec2d left, Vec2d right)
		{
			return !(left == right);
		}
	}
}
