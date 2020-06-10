using System;
using System.Runtime.InteropServices;
using EngineGrafico.Util;

namespace EngineGrafico
{
	class Program 
	{
		static void Main()
		{
			OpenGLContextUtil.CreateWindow("Teste", 500, 500);
			OpenGLContextUtil.CreateOpenGLContext();

			while (OpenGLContextUtil.WindowOpen)
			{
				OpenGLContextUtil.HandleEvent();

				OpenGLContextUtil.DrawGraphics();

				OpenGLContextUtil.PresentGraphics();
			}

		}



	}
}
