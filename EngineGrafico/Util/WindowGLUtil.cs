using EngineGrafico.Models;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;

namespace EngineGrafico.Util
{

	public abstract class WindowGLUtil : IDisposable
	{
		private const string CLASS_NAME = "LUANA_ENGINE";

		private Stopwatch tm1;
		private double frameTimer = 1.0f;
		private int frameCount = 0;
		private IntPtr m_hWnd;

		private static bool hasInputFocus;
		private static bool hasMouseFocus;

		private static Vec2d windowSize;
		private static Vec2d windowPos;

		private List<Layer> layers;

		private static Dictionary<int, KeyUtil.Key> mapKeys = new Dictionary<int, KeyUtil.Key>();

		private MouseUtil mouse = new MouseUtil();
		private static Vec2d mousePosCache = new Vec2d(0, 0);
		private static int mouseWheelDataCache = 0;

		private KeyUtil.HWButton[] keyboardState = new KeyUtil.HWButton[256];
		private static bool[] keyOld = new bool[256];
		private static bool[] keyNew = new bool[256];

		private KeyUtil.HWButton[] mouseState = new KeyUtil.HWButton[4];
		private static bool[] mouseOld = new bool[256];
		private static bool[] mouseNew = new bool[256];
		private int quantidadeMouseButtons = 4;

		public string Title { get; set; }

		public int Width { get; set; }

		public int Height { get; set; }

		public int PixelWidth { get; set; }

		public int PixelHeight { get; set; }

		public bool FullScreen { get; set; }

		public bool Vsync { get; set; }

		public double ElapsedTime { get; set; }

		public bool IsDisposed { get; set; }

		private static bool ativo;

		public WindowGLUtil()
		{
			Title = "Indefinido";
		}

		public abstract bool OnCreate();

		public abstract bool OnUpdate(double dElapsedTime);

		public abstract bool OnDestroy();

		public bool Construct(int screenWidth, int screenHeight, int pixelWidth, int pixelHeight, bool fullScreen = false, bool vsync = false)
		{
			Width = screenWidth;
			Height = screenHeight;
			PixelWidth = pixelWidth;
			PixelHeight = pixelHeight;
			FullScreen = fullScreen;
			Vsync = vsync;

			return true;
		}

		public bool IsFocused()
		{
			return true;
		}

		public KeyUtil.HWButton GetKey(KeyUtil.Key k)
		{
			return keyboardState[(int)k];
		}

		public KeyUtil.HWButton GetMouse(int b)
		{
			return mouseState[b];
		}

		public int GetMouseX()
		{
			return (int)mouse.Pos.X;
		}

		public int GetMouseY()
		{
			return (int)mouse.Pos.Y;
		}

		public int GetMouseWheel()
		{
			return mouse.WheelDelta;
		}

		public bool Draw(int x, int y, Pixel p = null)
		{

			// TODO
			return true;
		}

		public bool Start()
		{
			if (!CreateWindowPane(30, 30, 30, 30, false)) return false;
			UpdateWindowSize(Width, Height);

			ativo = true;
			Thread t = new Thread(new ThreadStart(EngineThread));
			t.Start();

			t.Join();

			if (!ApplicationCleanUp()) return false;

			return true;
		}


		private void EngineThread()
		{
			PrepareEngine();

			if (!OnCreate()) return;

			while (ativo)
			{
				CoreUpdate();
			}
		}

		private void PrepareEngine()
		{
			if (!CreateGraphics()) return;
			CreateLayer();
			layers[0].Update = true;
			layers[0].Show = true;

			tm1 = Stopwatch.StartNew();
		}

		private void ClearBuffer()
		{
			// TODO
		}

		private static void UpdateViewPort()
		{
			// TODO
		}

		private void PrepareDrawing()
		{
			// TODO
		}

		private void DisplayFrame()
		{
			// TODO
		}

		private bool CreateGraphics()
		{
			// TODO
			return true;
		}
		private void CreateLayer()
		{
			if (layers == null) layers = new List<Layer>();
			layers.Add(new Layer());
		}

		private void CoreUpdate()
		{
			CalculateFPS();

			ScanHardware(ref keyboardState, ref keyOld, ref keyNew, 256);
			ScanHardware(ref mouseState, ref mouseOld, ref mouseNew, quantidadeMouseButtons);

			mouse.Pos = mousePosCache;
			mouse.WheelDelta = mouseWheelDataCache;
			mouseWheelDataCache = 0;

			ClearBuffer();

			if (!OnUpdate(ElapsedTime))
				ativo = false;

			UpdateViewPort();
			ClearBuffer();

			layers[0].Update = true;
			layers[0].Show = true;

			PrepareDrawing();

			DisplayFrame();

		}

		private void ScanHardware(ref KeyUtil.HWButton[] keys, ref bool[] oldState, ref bool[] newState, int keyCount)
		{
			for (int i = 0; i < keyCount; i++)
			{
				keys[i].bPressed = false;
				keys[i].bReleased = false;
				if (newState[i] != oldState[i])
				{
					if (newState[i])
					{
						keys[i].bPressed = !keys[i].bHeld;
						keys[i].bHeld = true;
					}
					else
					{
						keys[i].bReleased = true;
						keys[i].bHeld = false;
					}
				}
				oldState[i] = newState[i];
			}
		}

		private bool CreateWindowPane(int x, int y, int w, int h, bool fs)
		{
			windowSize = new Vec2d(w, h);
			windowPos = new Vec2d(x, y);

			mWndProcDelegate = MyWndProc;
			Win32.WNDCLASSEX wcex = new Win32.WNDCLASSEX
			{
				style = (int)Win32.ClassStyles.CS_DBLCLKS,
				lpfnWndProc = Marshal.GetFunctionPointerForDelegate(mWndProcDelegate),
				lpszClassName = CLASS_NAME,
				cbSize = Marshal.SizeOf(typeof(Win32.WNDCLASSEX)),
				cbClsExtra = 0,
				cbWndExtra = 0,
				hIcon = Win32.LoadIcon(IntPtr.Zero, (IntPtr)Win32.SystemIcons.IDI_APPLICATION),
				hCursor = Win32.LoadCursor(IntPtr.Zero, (int)Win32.IDC_ARROW),
				hIconSm = IntPtr.Zero,
				hbrBackground = (IntPtr)(Win32.COLOR_WINDOW + 1),
				lpszMenuName = null
			};

			ushort regReturn = Win32.RegisterClassEx(ref wcex);

			if (regReturn == 0) return false;

			uint dwExStyle = (uint)(Win32.WindowStylesEx.WS_EX_APPWINDOW | Win32.WindowStylesEx.WS_EX_WINDOWEDGE);
			uint dwStyle = (uint)(Win32.WindowStyles.WS_CAPTION | Win32.WindowStyles.WS_SYSMENU | Win32.WindowStyles.WS_VISIBLE);

			if (fs)
			{
				dwExStyle = 0;
				dwStyle = (uint)(Win32.WindowStyles.WS_VISIBLE | Win32.WindowStyles.WS_POPUP);
				IntPtr hmon = Win32.MonitorFromWindow(m_hWnd, Win32.MONITOR_DEFAULTTONEAREST);
				Win32.MonitorInfoEx mon_info = new Win32.MonitorInfoEx();
				mon_info.Size = (int)Marshal.SizeOf(mon_info);
				if (!Win32.GetMonitorInfo(hmon, ref mon_info)) return false;
				windowSize = new Vec2d(mon_info.Monitor.Right, mon_info.Monitor.Bottom);
				windowPos.X = 0;
				windowPos.Y = 0;
			}

			Win32.RECT rWndRect = new Win32.RECT(0, 0, (int)windowSize.X, (int)windowSize.Y);
			Win32.AdjustWindowRectEx(ref rWndRect, dwStyle, false, dwExStyle);
			int width = rWndRect.Right - rWndRect.Left;
			int height = rWndRect.Bottom - rWndRect.Top;

			m_hWnd = Win32.CreateWindowEx(
				dwExStyle,
				regReturn,
				Title,
				dwStyle,
				(int)windowPos.X,
				(int)windowPos.Y,
				width,
				height,
				IntPtr.Zero,
				IntPtr.Zero,
				wcex.hInstance,
				IntPtr.Zero);

			mapKeys[0x00] = KeyUtil.Key.NONE;
			mapKeys[0x41] = KeyUtil.Key.A; mapKeys[0x42] = KeyUtil.Key.B; mapKeys[0x43] = KeyUtil.Key.C; mapKeys[0x44] = KeyUtil.Key.D; mapKeys[0x45] = KeyUtil.Key.E;
			mapKeys[0x46] = KeyUtil.Key.F; mapKeys[0x47] = KeyUtil.Key.G; mapKeys[0x48] = KeyUtil.Key.H; mapKeys[0x49] = KeyUtil.Key.I; mapKeys[0x4A] = KeyUtil.Key.J;
			mapKeys[0x4B] = KeyUtil.Key.K; mapKeys[0x4C] = KeyUtil.Key.L; mapKeys[0x4D] = KeyUtil.Key.M; mapKeys[0x4E] = KeyUtil.Key.N; mapKeys[0x4F] = KeyUtil.Key.O;
			mapKeys[0x50] = KeyUtil.Key.P; mapKeys[0x51] = KeyUtil.Key.Q; mapKeys[0x52] = KeyUtil.Key.R; mapKeys[0x53] = KeyUtil.Key.S; mapKeys[0x54] = KeyUtil.Key.T;
			mapKeys[0x55] = KeyUtil.Key.U; mapKeys[0x56] = KeyUtil.Key.V; mapKeys[0x57] = KeyUtil.Key.W; mapKeys[0x58] = KeyUtil.Key.X; mapKeys[0x59] = KeyUtil.Key.Y;
			mapKeys[0x5A] = KeyUtil.Key.Z;

			mapKeys[(int)Win32.VK.F1] = KeyUtil.Key.F1; mapKeys[(int)Win32.VK.F2] = KeyUtil.Key.F2; mapKeys[(int)Win32.VK.F3] = KeyUtil.Key.F3; mapKeys[(int)Win32.VK.F4] = KeyUtil.Key.F4;
			mapKeys[(int)Win32.VK.F5] = KeyUtil.Key.F5; mapKeys[(int)Win32.VK.F6] = KeyUtil.Key.F6; mapKeys[(int)Win32.VK.F7] = KeyUtil.Key.F7; mapKeys[(int)Win32.VK.F8] = KeyUtil.Key.F8;
			mapKeys[(int)Win32.VK.F9] = KeyUtil.Key.F9; mapKeys[(int)Win32.VK.F10] = KeyUtil.Key.F10; mapKeys[(int)Win32.VK.F11] = KeyUtil.Key.F11; mapKeys[(int)Win32.VK.F12] = KeyUtil.Key.F12;

			mapKeys[(int)Win32.VK.DOWN] = KeyUtil.Key.DOWN; mapKeys[(int)Win32.VK.LEFT] = KeyUtil.Key.LEFT; mapKeys[(int)Win32.VK.RIGHT] = KeyUtil.Key.RIGHT; mapKeys[(int)Win32.VK.UP] = KeyUtil.Key.UP;
			mapKeys[(int)Win32.VK.RETURN] = KeyUtil.Key.ENTER; //mapKeys[VK_RETURN] = KeyUtil.Key.RETURN;

			mapKeys[(int)Win32.VK.BACK] = KeyUtil.Key.BACK; mapKeys[(int)Win32.VK.ESCAPE] = KeyUtil.Key.ESCAPE; mapKeys[(int)Win32.VK.RETURN] = KeyUtil.Key.ENTER; mapKeys[(int)Win32.VK.PAUSE] = KeyUtil.Key.PAUSE;
			mapKeys[(int)Win32.VK.SCROLL] = KeyUtil.Key.SCROLL; mapKeys[(int)Win32.VK.TAB] = KeyUtil.Key.TAB; mapKeys[(int)Win32.VK.DELETE] = KeyUtil.Key.DEL; mapKeys[(int)Win32.VK.HOME] = KeyUtil.Key.HOME;
			mapKeys[(int)Win32.VK.END] = KeyUtil.Key.END; mapKeys[(int)Win32.VK.PRIOR] = KeyUtil.Key.PGUP; mapKeys[(int)Win32.VK.NEXT] = KeyUtil.Key.PGDN; mapKeys[(int)Win32.VK.INSERT] = KeyUtil.Key.INS;
			mapKeys[(int)Win32.VK.SHIFT] = KeyUtil.Key.SHIFT; mapKeys[(int)Win32.VK.CONTROL] = KeyUtil.Key.CTRL;
			mapKeys[(int)Win32.VK.SPACE] = KeyUtil.Key.SPACE;

			mapKeys[0x30] = KeyUtil.Key.K0; mapKeys[0x31] = KeyUtil.Key.K1; mapKeys[0x32] = KeyUtil.Key.K2; mapKeys[0x33] = KeyUtil.Key.K3; mapKeys[0x34] = KeyUtil.Key.K4;
			mapKeys[0x35] = KeyUtil.Key.K5; mapKeys[0x36] = KeyUtil.Key.K6; mapKeys[0x37] = KeyUtil.Key.K7; mapKeys[0x38] = KeyUtil.Key.K8; mapKeys[0x39] = KeyUtil.Key.K9;

			mapKeys[(int)Win32.VK.NUMPAD0] = KeyUtil.Key.NP0; mapKeys[(int)Win32.VK.NUMPAD1] = KeyUtil.Key.NP1; mapKeys[(int)Win32.VK.NUMPAD2] = KeyUtil.Key.NP2; mapKeys[(int)Win32.VK.NUMPAD3] = KeyUtil.Key.NP3; mapKeys[(int)Win32.VK.NUMPAD4] = KeyUtil.Key.NP4;
			mapKeys[(int)Win32.VK.NUMPAD5] = KeyUtil.Key.NP5; mapKeys[(int)Win32.VK.NUMPAD6] = KeyUtil.Key.NP6; mapKeys[(int)Win32.VK.NUMPAD7] = KeyUtil.Key.NP7; mapKeys[(int)Win32.VK.NUMPAD8] = KeyUtil.Key.NP8; mapKeys[(int)Win32.VK.NUMPAD9] = KeyUtil.Key.NP9;
			mapKeys[(int)Win32.VK.MULTIPLY] = KeyUtil.Key.NP_MUL; mapKeys[(int)Win32.VK.ADD] = KeyUtil.Key.NP_ADD; mapKeys[(int)Win32.VK.DIVIDE] = KeyUtil.Key.NP_DIV; mapKeys[(int)Win32.VK.SUBTRACT] = KeyUtil.Key.NP_SUB; mapKeys[(int)Win32.VK.DECIMAL] = KeyUtil.Key.NP_DECIMAL;

			return true;
		}

		delegate IntPtr WndProc(IntPtr hWnd, Win32.WindowsMessages message, IntPtr wParam, IntPtr lParam);

		private static WndProc mWndProcDelegate;

		private static IntPtr MyWndProc(IntPtr hWnd, Win32.WindowsMessages message, IntPtr wParam, IntPtr lParam)

		{
			switch (message)
			{
				case Win32.WindowsMessages.MOUSEMOVE:
					UInt16 x = (UInt16)((int)lParam & 0xFFFF);
					UInt16 y = (UInt16)(((int)lParam >> 16) & 0xFFFF);
					unsafe
					{
						Int16 ix = *(Int16*)&x; Int16 iy = *(Int16*)&y;
						UpdateMouse(ix, iy);
					}
					return IntPtr.Zero;
				case Win32.WindowsMessages.SIZE:
					UpdateWindowSize((int)lParam & 0xFFFF, (int)(((int)lParam >> 16) & 0xFFFF));
					return IntPtr.Zero;
				case Win32.WindowsMessages.MOUSEWHEEL:
					UpdateMouseWheel(((short)((int)wParam >> 16)));
					return IntPtr.Zero;
				case Win32.WindowsMessages.MOUSELEAVE:
					UpdateMouseFocus(false);
					return IntPtr.Zero;
				case Win32.WindowsMessages.SETFOCUS:
					UpdateKeyFocus(true);
					return IntPtr.Zero;
				case Win32.WindowsMessages.KILLFOCUS:
					UpdateKeyFocus(false);
					return IntPtr.Zero;
				case Win32.WindowsMessages.KEYDOWN:
					UpdateKeyState((int)mapKeys[(int)wParam], true);
					return IntPtr.Zero;
				case Win32.WindowsMessages.KEYUP:
					UpdateKeyState((int)mapKeys[(int)wParam], false);
					return IntPtr.Zero;
				case Win32.WindowsMessages.LBUTTONDOWN:
					UpdateMouseState(0, true);
					return IntPtr.Zero;
				case Win32.WindowsMessages.LBUTTONUP:
					UpdateMouseState(0, false);
					return IntPtr.Zero;
				case Win32.WindowsMessages.RBUTTONDOWN:
					UpdateMouseState(1, true);
					return IntPtr.Zero;
				case Win32.WindowsMessages.RBUTTONUP:
					UpdateMouseState(1, false);
					return IntPtr.Zero;
				case Win32.WindowsMessages.MBUTTONDOWN:
					UpdateMouseState(2, true);
					return IntPtr.Zero;
				case Win32.WindowsMessages.MBUTTONUP:
					UpdateMouseState(2, false);
					return IntPtr.Zero;
				case Win32.WindowsMessages.CLOSE:
					Terminate();
					return IntPtr.Zero;
				case Win32.WindowsMessages.PAINT:
					{
						IntPtr hDC;
						hDC = Win32.BeginPaint(hWnd, out Win32.PAINTSTRUCT ps);

						Win32.EndPaint(hWnd, ref ps);
						return IntPtr.Zero;
					}
				case Win32.WindowsMessages.DESTROY:
					Win32.PostQuitMessage(0);
					return IntPtr.Zero;
				default:
					return (Win32.DefWindowProc(hWnd, message, wParam, lParam));
			}
		}

		private static void UpdateWindowSize(int x, int y)
		{
			windowSize = new Vec2d(x, y);
			UpdateViewPort();
		}

		private static void UpdateMouseWheel(int delta)
		{
			mouseWheelDataCache += delta;
		}

		private static void UpdateMouse(int x, int y)
		{
			mousePosCache.X = x;
			mousePosCache.Y = y;
		}

		private static void UpdateMouseState(int button, bool state)
		{
			mouseNew[button] = state;
		}

		private static void UpdateKeyState(int key, bool state)
		{
			keyNew[key] = state;
		}

		private static void UpdateMouseFocus(bool state)
		{
			hasMouseFocus = state;
		}

		private static void UpdateKeyFocus(bool state)
		{
			hasInputFocus = state;
		}

		private static void Terminate()
		{
			ativo = false;
		}

		private bool ApplicationCleanUp()
		{
			Win32.PostMessage(m_hWnd, Win32.WindowsMessages.DESTROY, IntPtr.Zero, IntPtr.Zero);
			return true;
		}

		private void CalculateFPS()
		{
			if (tm1 == null) tm1 = Stopwatch.StartNew();
			tm1.Stop();
			ElapsedTime = tm1.Elapsed.TotalSeconds;
			frameTimer += ElapsedTime;
			frameCount++;
			if (frameTimer >= 1.0f)
			{
				frameTimer -= 1.0f;
				string novoTituloJanela = string.Format("{0} - FPS: {1}", Title, frameCount);
				SetWindowTitle(novoTituloJanela);
				frameCount = 0;
			}
			tm1.Reset();
			tm1.Start();
		}

		private void SetWindowTitle(string titulo)
		{
			Win32.SetWindowText(m_hWnd, titulo);
		}

		public void Dispose()
		{
			Dispose(true);
			GC.SuppressFinalize(this);
		}

		private void Dispose(bool disposing)
		{
			if (!IsDisposed)
			{
				if (disposing)
				{
					// Dispose managed resources
				}

				// Dispose unmanaged resources
				if (m_hWnd != IntPtr.Zero)
				{
					Win32.DestroyWindow(m_hWnd);
					m_hWnd = IntPtr.Zero;
				}

			}
		}


	}
}
