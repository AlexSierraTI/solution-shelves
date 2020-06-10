using EngineGrafico.Models;

namespace EngineGrafico.Util
{
	public static class PixelUtil
	{
		public enum Mode
		{
			NORMAL, MASK, ALPHA, CUSTOM
		}

		public static readonly Pixel GREY;
		public static readonly Pixel DARK_GREY;
		public static readonly Pixel VERY_DARK_GREY;
		public static readonly Pixel RED;
		public static readonly Pixel DARK_RED;
		public static readonly Pixel VERY_DARK_RED;
		public static readonly Pixel YELLOW;
		public static readonly Pixel DARK_YELLOW;
		public static readonly Pixel VERY_DARK_YELLOW;
		public static readonly Pixel GREEN;
		public static readonly Pixel DARK_GREEN;
		public static readonly Pixel VERY_DARK_GREEN;
		public static readonly Pixel CYAN;
		public static readonly Pixel DARK_CYAN;
		public static readonly Pixel VERY_DARK_CYAN;
		public static readonly Pixel BLUE;
		public static readonly Pixel DARK_BLUE;
		public static readonly Pixel VERY_DARK_BLUE;
		public static readonly Pixel MAGENTA;
		public static readonly Pixel DARK_MAGENTA;
		public static readonly Pixel VERY_DARK_MAGENTA;
		public static readonly Pixel WHITE;
		public static readonly Pixel BLACK;
		public static readonly Pixel BLANK;

		static PixelUtil()
		{
			GREY = new Pixel(192, 192, 192, 1);
			DARK_GREY = new Pixel(128, 128, 128, 1);
			VERY_DARK_GREY = new Pixel(64, 64, 64, 1);
			RED = new Pixel(255, 0, 0, 1);
			DARK_RED = new Pixel(128, 0, 0, 1);
			VERY_DARK_RED = new Pixel(64, 0, 0, 1);
			YELLOW = new Pixel(255, 255, 0, 1);
			DARK_YELLOW = new Pixel(128, 128, 0, 1);
			VERY_DARK_YELLOW = new Pixel(64, 64, 0, 1);
			GREEN = new Pixel(0, 255, 0, 1);
			DARK_GREEN = new Pixel(0, 128, 0, 1);
			VERY_DARK_GREEN = new Pixel(0, 64, 0, 1);
			CYAN = new Pixel(0, 255, 255, 1);
			DARK_CYAN = new Pixel(0, 128, 128, 1);
			VERY_DARK_CYAN = new Pixel(0, 64, 64, 1);
			BLUE = new Pixel(0, 0, 255, 1);
			DARK_BLUE = new Pixel(0, 0, 128, 1);
			VERY_DARK_BLUE = new Pixel(0, 0, 64, 1);
			MAGENTA = new Pixel(255, 0, 255, 1);
			DARK_MAGENTA = new Pixel(128, 0, 128, 1);
			VERY_DARK_MAGENTA = new Pixel(64, 0, 64, 1);
			WHITE = new Pixel(255, 255, 255, 1);
			BLACK = new Pixel(0, 0, 0, 1);
			BLANK = new Pixel(0, 0, 0, 0);

		}
	}
}
