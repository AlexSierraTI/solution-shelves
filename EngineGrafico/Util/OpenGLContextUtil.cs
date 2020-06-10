using System;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace EngineGrafico.Util
{
	public class OpenGLContextUtil
	{
		private const string APP_TO_OVERLAY = "Counter-Strike: Global Offensive";

		public struct Pixel
		{
			public float R;
			public float G;
			public float B;
			public float A;

			public float X;
			public float Y;
		}


		private static Stopwatch tm1;
		private static double frameTimer = 1.0f;
		private static int frameCount = 0;

		public static string Title { get; set; }

		public static int Width { get; set; }

		public static int Height { get; set; }

		public static bool WindowOpen { get; set; } = false;

		public static object Evento { get; set; }

		public static IntPtr Window { get; set; }

		public static IntPtr WindowGDI { get; set; }

		public static double ElapsedTime { get; set; }

		public static int LastFPS { get; set; }

		public static void CreateWindow(string title, int width, int height)
		{
			if (GLFW.glfwInit())
			{
				ConfiguraJanela();

				Window = GLFW.glfwCreateWindow(width, height, title, IntPtr.Zero, IntPtr.Zero);
				if (Window != IntPtr.Zero)
				{
					Title = title;
					Width = width;
					Height = height;

					tm1 = Stopwatch.StartNew();
					WindowOpen = true;
				}
			}
		}

		public static void CreateOpenGLContext()
		{
			GLFW.glfwMakeContextCurrent(Window);
		}

		public static void HandleEvent()
		{

		}
			
		public static void DrawGraphics()
		{

		}

		public static void PresentGraphics()
		{
			if (GLFW.glfwWindowShouldClose(Window) != 0)
			{
				WindowOpen = false;
				GLFW.glfwTerminate();
				return;
			}

			GLFW.glfwSwapBuffers(Window);
			GLFW.glfwPollEvents();

			CalculateFPS();
		}

		private static void CalculateFPS()
		{
			tm1.Stop();
			ElapsedTime = tm1.Elapsed.TotalSeconds;
			frameTimer += ElapsedTime;
			frameCount++;
			if (frameTimer >= 1.0f)
			{
				LastFPS = frameCount;
				frameTimer -= 1.0f;
				string novoTituloJanela = string.Format("{0} - FPS: {1}", Title, frameCount);
				GLFW.glfwSetWindowTitle(Window, novoTituloJanela);
				frameCount = 0;
			}
			tm1.Reset();
			tm1.Start();
		}

		private static void ConfiguraJanela()
		{
			// Transparencia
			// GLFW.glfwWindowHint(GLFW.GLFW_TRANSPARENT_FRAMEBUFFER, 1);
			// OpenGL.glClearColor(1.0f, 0.0f, 0.0f, 0.2f);

			// Top Most Overlay
			// GLFW.glfwWindowHint(GLFW.GLFW_FLOATING, 1);

			// Unresizable
			// GLFW.glfwWindowHint(GLFW.GLFW_RESIZABLE, 0);

			// SemBorda
			// GLFW.glfwWindowHint(GLFW.GLFW_DECORATED, 1);
		}

		private static void MakeWindowOverlay()
		{
			
			IntPtr hdl = Win32.FindWindowByCaption(IntPtr.Zero, Title);
			WindowGDI = hdl;
			IntPtr iniatialStyle = Win32.GetWindowLongPtr(hdl, -20);
			Win32.SetWindowLongPtr(hdl, -20, (IntPtr)((int)iniatialStyle | 0x80000 | 0x20));

			SincronizaOverlay();
		}

		private static void SincronizaOverlay()
		{
			// Mesmo tamanho da janela alvo e sincronizaPosicao
			IntPtr hdlAppToOverlay = Win32.FindWindowByCaption(IntPtr.Zero, APP_TO_OVERLAY);
			Win32.GetWindowRect(hdlAppToOverlay, out Win32.RECT rectApp);
			GLFW.glfwSetWindowSize(Window, rectApp.Right - rectApp.Left, rectApp.Bottom - rectApp.Top);
			GLFW.glfwSetWindowPos(Window, rectApp.Left, rectApp.Top);
		}

	}
}

