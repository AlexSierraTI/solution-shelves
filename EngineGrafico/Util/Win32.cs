﻿using System;
using System.Runtime.InteropServices;

namespace EngineGrafico.Util
{
	public class Win32
	{
		// CONST
		public const int MONITOR_DEFAULTTONULL = 0;
		public const int MONITOR_DEFAULTTOPRIMARY = 1;
		public const int MONITOR_DEFAULTTONEAREST = 2;

		private const int CCHDEVICENAME = 32;

		public const uint WM_ACTIVATE = 0x0006,
			WM_ACTIVATEAPP = 0x001C,
			WM_AFXFIRST = 0x0360,
			WM_AFXLAST = 0x037F,
			WM_APP = 0x8000,
			WM_ASKCBFORMATNAME = 0x030C,
			WM_CANCELJOURNAL = 0x004B,
			WM_CANCELMODE = 0x001F,
			WM_CAPTURECHANGED = 0x0215,
			WM_CHANGECBCHAIN = 0x030D,
			WM_CHANGEUISTATE = 0x0127,
			WM_CHAR = 0x0102,
			WM_CHARTOITEM = 0x002F,
			WM_CHILDACTIVATE = 0x0022,
			WM_CLEAR = 0x0303,
			WM_CLOSE = 0x0010,
			WM_COMMAND = 0x0111,
			WM_COMPACTING = 0x0041,
			WM_COMPAREITEM = 0x0039,
			WM_CONTEXTMENU = 0x007B,
			WM_COPY = 0x0301,
			WM_COPYDATA = 0x004A,
			WM_CREATE = 0x0001,
			WM_CTLCOLORBTN = 0x0135,
			WM_CTLCOLORDLG = 0x0136,
			WM_CTLCOLOREDIT = 0x0133,
			WM_CTLCOLORLISTBOX = 0x0134,
			WM_CTLCOLORMSGBOX = 0x0132,
			WM_CTLCOLORSCROLLBAR = 0x0137,
			WM_CTLCOLORSTATIC = 0x0138,
			WM_CUT = 0x0300,
			WM_DEADCHAR = 0x0103,
			WM_DELETEITEM = 0x002D,
			WM_DESTROY = 0x0002,
			WM_DESTROYCLIPBOARD = 0x0307,
			WM_DEVICECHANGE = 0x0219,
			WM_DEVMODECHANGE = 0x001B,
			WM_DISPLAYCHANGE = 0x007E,
			WM_DRAWCLIPBOARD = 0x0308,
			WM_DRAWITEM = 0x002B,
			WM_DROPFILES = 0x0233,
			WM_ENABLE = 0x000A,
			WM_ENDSESSION = 0x0016,
			WM_ENTERIDLE = 0x0121,
			WM_ENTERMENULOOP = 0x0211,
			WM_ENTERSIZEMOVE = 0x0231,
			WM_ERASEBKGND = 0x0014,
			WM_EXITMENULOOP = 0x0212,
			WM_EXITSIZEMOVE = 0x0232,
			WM_FONTCHANGE = 0x001D,
			WM_GETDLGCODE = 0x0087,
			WM_GETFONT = 0x0031,
			WM_GETHOTKEY = 0x0033,
			WM_GETICON = 0x007F,
			WM_GETMINMAXINFO = 0x0024,
			WM_GETOBJECT = 0x003D,
			WM_GETTEXT = 0x000D,
			WM_GETTEXTLENGTH = 0x000E,
			WM_HANDHELDFIRST = 0x0358,
			WM_HANDHELDLAST = 0x035F,
			WM_HELP = 0x0053,
			WM_HOTKEY = 0x0312,
			WM_HSCROLL = 0x0114,
			WM_HSCROLLCLIPBOARD = 0x030E,
			WM_ICONERASEBKGND = 0x0027,
			WM_IME_CHAR = 0x0286,
			WM_IME_COMPOSITION = 0x010F,
			WM_IME_COMPOSITIONFULL = 0x0284,
			WM_IME_CONTROL = 0x0283,
			WM_IME_ENDCOMPOSITION = 0x010E,
			WM_IME_KEYDOWN = 0x0290,
			WM_IME_KEYLAST = 0x010F,
			WM_IME_KEYUP = 0x0291,
			WM_IME_NOTIFY = 0x0282,
			WM_IME_REQUEST = 0x0288,
			WM_IME_SELECT = 0x0285,
			WM_IME_SETCONTEXT = 0x0281,
			WM_IME_STARTCOMPOSITION = 0x010D,
			WM_INITDIALOG = 0x0110,
			WM_INITMENU = 0x0116,
			WM_INITMENUPOPUP = 0x0117,
			WM_INPUTLANGCHANGE = 0x0051,
			WM_INPUTLANGCHANGEREQUEST = 0x0050,
			WM_KEYDOWN = 0x0100,
			WM_KEYFIRST = 0x0100,
			WM_KEYLAST = 0x0108,
			WM_KEYUP = 0x0101,
			WM_KILLFOCUS = 0x0008,
			WM_LBUTTONDBLCLK = 0x0203,
			WM_LBUTTONDOWN = 0x0201,
			WM_LBUTTONUP = 0x0202,
			WM_MBUTTONDBLCLK = 0x0209,
			WM_MBUTTONDOWN = 0x0207,
			WM_MBUTTONUP = 0x0208,
			WM_MDIACTIVATE = 0x0222,
			WM_MDICASCADE = 0x0227,
			WM_MDICREATE = 0x0220,
			WM_MDIDESTROY = 0x0221,
			WM_MDIGETACTIVE = 0x0229,
			WM_MDIICONARRANGE = 0x0228,
			WM_MDIMAXIMIZE = 0x0225,
			WM_MDINEXT = 0x0224,
			WM_MDIREFRESHMENU = 0x0234,
			WM_MDIRESTORE = 0x0223,
			WM_MDISETMENU = 0x0230,
			WM_MDITILE = 0x0226,
			WM_MEASUREITEM = 0x002C,
			WM_MENUCHAR = 0x0120,
			WM_MENUCOMMAND = 0x0126,
			WM_MENUDRAG = 0x0123,
			WM_MENUGETOBJECT = 0x0124,
			WM_MENURBUTTONUP = 0x0122,
			WM_MENUSELECT = 0x011F,
			WM_MOUSEACTIVATE = 0x0021,
			WM_MOUSEFIRST = 0x0200,
			WM_MOUSEHOVER = 0x02A1,
			WM_MOUSELAST = 0x020D,
			WM_MOUSELEAVE = 0x02A3,
			WM_MOUSEMOVE = 0x0200,
			WM_MOUSEWHEEL = 0x020A,
			WM_MOUSEHWHEEL = 0x020E,
			WM_MOVE = 0x0003,
			WM_MOVING = 0x0216,
			WM_NCACTIVATE = 0x0086,
			WM_NCCALCSIZE = 0x0083,
			WM_NCCREATE = 0x0081,
			WM_NCDESTROY = 0x0082,
			WM_NCHITTEST = 0x0084,
			WM_NCLBUTTONDBLCLK = 0x00A3,
			WM_NCLBUTTONDOWN = 0x00A1,
			WM_NCLBUTTONUP = 0x00A2,
			WM_NCMBUTTONDBLCLK = 0x00A9,
			WM_NCMBUTTONDOWN = 0x00A7,
			WM_NCMBUTTONUP = 0x00A8,
			WM_NCMOUSEHOVER = 0x02A0,
			WM_NCMOUSELEAVE = 0x02A2,
			WM_NCMOUSEMOVE = 0x00A0,
			WM_NCPAINT = 0x0085,
			WM_NCRBUTTONDBLCLK = 0x00A6,
			WM_NCRBUTTONDOWN = 0x00A4,
			WM_NCRBUTTONUP = 0x00A5,
			WM_NCXBUTTONDBLCLK = 0x00AD,
			WM_NCXBUTTONDOWN = 0x00AB,
			WM_NCXBUTTONUP = 0x00AC,
			WM_NCUAHDRAWCAPTION = 0x00AE,
			WM_NCUAHDRAWFRAME = 0x00AF,
			WM_NEXTDLGCTL = 0x0028,
			WM_NEXTMENU = 0x0213,
			WM_NOTIFY = 0x004E,
			WM_NOTIFYFORMAT = 0x0055,
			WM_NULL = 0x0000,
			WM_PAINT = 0x000F,
			WM_PAINTCLIPBOARD = 0x0309,
			WM_PAINTICON = 0x0026,
			WM_PALETTECHANGED = 0x0311,
			WM_PALETTEISCHANGING = 0x0310,
			WM_PARENTNOTIFY = 0x0210,
			WM_PASTE = 0x0302,
			WM_PENWINFIRST = 0x0380,
			WM_PENWINLAST = 0x038F,
			WM_POWER = 0x0048,
			WM_POWERBROADCAST = 0x0218,
			WM_PRINT = 0x0317,
			WM_PRINTCLIENT = 0x0318,
			WM_QUERYDRAGICON = 0x0037,
			WM_QUERYENDSESSION = 0x0011,
			WM_QUERYNEWPALETTE = 0x030F,
			WM_QUERYOPEN = 0x0013,
			WM_QUEUESYNC = 0x0023,
			WM_QUIT = 0x0012,
			WM_RBUTTONDBLCLK = 0x0206,
			WM_RBUTTONDOWN = 0x0204,
			WM_RBUTTONUP = 0x0205,
			WM_RENDERALLFORMATS = 0x0306,
			WM_RENDERFORMAT = 0x0305,
			WM_SETCURSOR = 0x0020,
			WM_SETFOCUS = 0x0007,
			WM_SETFONT = 0x0030,
			WM_SETHOTKEY = 0x0032,
			WM_SETICON = 0x0080,
			WM_SETREDRAW = 0x000B,
			WM_SETTEXT = 0x000C,
			WM_SETTINGCHANGE = 0x001A,
			WM_SHOWWINDOW = 0x0018,
			WM_SIZE = 0x0005,
			WM_SIZECLIPBOARD = 0x030B,
			WM_SIZING = 0x0214,
			WM_SPOOLERSTATUS = 0x002A,
			WM_STYLECHANGED = 0x007D,
			WM_STYLECHANGING = 0x007C,
			WM_SYNCPAINT = 0x0088,
			WM_SYSCHAR = 0x0106,
			WM_SYSCOLORCHANGE = 0x0015,
			WM_SYSCOMMAND = 0x0112,
			WM_SYSDEADCHAR = 0x0107,
			WM_SYSKEYDOWN = 0x0104,
			WM_SYSKEYUP = 0x0105,
			WM_TCARD = 0x0052,
			WM_TIMECHANGE = 0x001E,
			WM_TIMER = 0x0113,
			WM_UNDO = 0x0304,
			WM_UNINITMENUPOPUP = 0x0125,
			WM_USER = 0x0400,
			WM_USERCHANGED = 0x0054,
			WM_VKEYTOITEM = 0x002E,
			WM_VSCROLL = 0x0115,
			WM_VSCROLLCLIPBOARD = 0x030A,
			WM_WINDOWPOSCHANGED = 0x0047,
			WM_WINDOWPOSCHANGING = 0x0046,
			WM_WININICHANGE = 0x001A,
			WM_XBUTTONDBLCLK = 0x020D,
			WM_XBUTTONDOWN = 0x020B,
			WM_XBUTTONUP = 0x020C;

		public const int
			IDC_ARROW = 32512,
			IDC_IBEAM = 32513,
			IDC_WAIT = 32514,
			IDC_CROSS = 32515,
			IDC_UPARROW = 32516,
			IDC_SIZE = 32640,
			IDC_ICON = 32641,
			IDC_SIZENWSE = 32642,
			IDC_SIZENESW = 32643,
			IDC_SIZEWE = 32644,
			IDC_SIZENS = 32645,
			IDC_SIZEALL = 32646,
			IDC_NO = 32648,
			IDC_HAND = 32649,
			IDC_APPSTARTING = 32650,
			IDC_HELP = 32651;

		public const int
			COLOR_SCROLLBAR = 0,
			COLOR_BACKGROUND = 1,
			COLOR_DESKTOP = 1,
			COLOR_ACTIVECAPTION = 2,
			COLOR_INACTIVECAPTION = 3,
			COLOR_MENU = 4,
			COLOR_WINDOW = 5,
			COLOR_WINDOWFRAME = 6,
			COLOR_MENUTEXT = 7,
			COLOR_WINDOWTEXT = 8,
			COLOR_CAPTIONTEXT = 9,
			COLOR_ACTIVEBORDER = 10,
			COLOR_INACTIVEBORDER = 11,
			COLOR_APPWORKSPACE = 12,
			COLOR_HIGHLIGHT = 13,
			COLOR_HIGHLIGHTTEXT = 14,
			COLOR_BTNFACE = 15,
			COLOR_3DFACE = 15,
			COLOR_BTNSHADOW = 16,
			COLOR_3DSHADOW = 16,
			COLOR_GRAYTEXT = 17,
			COLOR_BTNTEXT = 18,
			COLOR_INACTIVECAPTIONTEXT = 19,
			COLOR_BTNHIGHLIGHT = 20,
			COLOR_3DHIGHLIGHT = 20,
			COLOR_3DHILIGHT = 20,
			COLOR_BTNHILIGHT = 20,
			COLOR_3DDKSHADOW = 21,
			COLOR_3DLIGHT = 22,
			COLOR_INFOTEXT = 23,
			COLOR_INFOBK = 24;

		// ENUMS 
		public enum ClassStyles
		{
			CS_BYTEALIGNCLIENT = 0x1000,
			CS_BYTEALIGNWINDOW = 0x2000,
			CS_CLASSDC = 0x0040,
			CS_DBLCLKS = 0x0008,
			CS_DROPSHADOW = 0x00020000,
			CS_GLOBALCLASS = 0x4000,
			CS_HREDRAW = 0x0002,
			CS_NOCLOSE = 0x0200,
			CS_OWNDC = 0x0020,
			CS_PARENTDC = 0x0080,
			CS_SAVEBITS = 0x0800,
			CS_VREDRAW = 0x0001
		}

		public enum SystemIcons
		{
			IDI_APPLICATION = 32512,
			IDI_HAND = 32513,
			IDI_QUESTION = 32514,
			IDI_EXCLAMATION = 32515,
			IDI_ASTERISK = 32516,
			IDI_WINLOGO = 32517,
			IDI_WARNING = IDI_EXCLAMATION,
			IDI_ERROR = IDI_HAND,
			IDI_INFORMATION = IDI_ASTERISK,
		}

		[Flags]
		public enum MessageBoxOptions : uint
		{
			OkOnly = 0x000000,
			OkCancel = 0x000001,
			AbortRetryIgnore = 0x000002,
			YesNoCancel = 0x000003,
			YesNo = 0x000004,
			RetryCancel = 0x000005,
			CancelTryContinue = 0x000006,
			IconHand = 0x000010,
			IconQuestion = 0x000020,
			IconExclamation = 0x000030,
			IconAsterisk = 0x000040,
			UserIcon = 0x000080,
			IconWarning = IconExclamation,
			IconError = IconHand,
			IconInformation = IconAsterisk,
			IconStop = IconHand,
			DefButton1 = 0x000000,
			DefButton2 = 0x000100,
			DefButton3 = 0x000200,
			DefButton4 = 0x000300,
			ApplicationModal = 0x000000,
			SystemModal = 0x001000,
			TaskModal = 0x002000,
			Help = 0x004000,
			NoFocus = 0x008000,
			SetForeground = 0x010000,
			DefaultDesktopOnly = 0x020000,
			Topmost = 0x040000,
			Right = 0x080000,
			RTLReading = 0x100000
		}

		[Flags]
		public enum WindowStylesEx : uint
		{
			WS_EX_ACCEPTFILES = 0x00000010,
			WS_EX_APPWINDOW = 0x00040000,
			WS_EX_CLIENTEDGE = 0x00000200,
			WS_EX_COMPOSITED = 0x02000000,
			WS_EX_CONTEXTHELP = 0x00000400,
			WS_EX_CONTROLPARENT = 0x00010000,
			WS_EX_DLGMODALFRAME = 0x00000001,
			WS_EX_LAYERED = 0x00080000,
			WS_EX_LAYOUTRTL = 0x00400000,
			WS_EX_LEFT = 0x00000000,
			WS_EX_LEFTSCROLLBAR = 0x00004000,
			WS_EX_LTRREADING = 0x00000000,
			WS_EX_MDICHILD = 0x00000040,
			WS_EX_NOACTIVATE = 0x08000000,
			WS_EX_NOINHERITLAYOUT = 0x00100000,
			WS_EX_NOPARENTNOTIFY = 0x00000004,
			WS_EX_NOREDIRECTIONBITMAP = 0x00200000,
			WS_EX_OVERLAPPEDWINDOW = WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE,
			WS_EX_PALETTEWINDOW = WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST,
			WS_EX_RIGHT = 0x00001000,
			WS_EX_RIGHTSCROLLBAR = 0x00000000,
			WS_EX_RTLREADING = 0x00002000,
			WS_EX_STATICEDGE = 0x00020000,
			WS_EX_TOOLWINDOW = 0x00000080,
			WS_EX_TOPMOST = 0x00000008,
			WS_EX_TRANSPARENT = 0x00000020,
			WS_EX_WINDOWEDGE = 0x00000100
		}

		[Flags]
		public enum WindowStyles : uint
		{
			WS_BORDER = 0x800000,
			WS_CAPTION = 0xc00000,
			WS_CHILD = 0x40000000,
			WS_CLIPCHILDREN = 0x2000000,
			WS_CLIPSIBLINGS = 0x4000000,
			WS_DISABLED = 0x8000000,
			WS_DLGFRAME = 0x400000,
			WS_GROUP = 0x20000,
			WS_HSCROLL = 0x100000,
			WS_MAXIMIZE = 0x1000000,
			WS_MAXIMIZEBOX = 0x10000,
			WS_MINIMIZE = 0x20000000,
			WS_MINIMIZEBOX = 0x20000,
			WS_OVERLAPPED = 0x0,
			WS_OVERLAPPEDWINDOW = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_SIZEFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
			WS_POPUP = 0x80000000u,
			WS_POPUPWINDOW = WS_POPUP | WS_BORDER | WS_SYSMENU,
			WS_SIZEFRAME = 0x40000,
			WS_SYSMENU = 0x80000,
			WS_TABSTOP = 0x10000,
			WS_VISIBLE = 0x10000000,
			WS_VSCROLL = 0x200000
		}

		/// <summary>
		/// Windows Messages
		/// Defined in winuser.h from Windows SDK v6.1
		/// Documentation pulled from MSDN.
		/// </summary>
		public enum WindowsMessages : uint
		{
			/// <summary>
			/// The WM_NULL message performs no operation. An application sends the WM_NULL message if it wants to post a message that the recipient window will ignore.
			/// </summary>
			NULL = 0x0000,
			/// <summary>
			/// The WM_CREATE message is sent when an application requests that a window be created by calling the CreateWindowEx or CreateWindow function. (The message is sent before the function returns.) The window procedure of the new window receives this message after the window is created, but before the window becomes visible.
			/// </summary>
			CREATE = 0x0001,
			/// <summary>
			/// The WM_DESTROY message is sent when a window is being destroyed. It is sent to the window procedure of the window being destroyed after the window is removed from the screen.
			/// This message is sent first to the window being destroyed and then to the child windows (if any) as they are destroyed. During the processing of the message, it can be assumed that all child windows still exist.
			/// /// </summary>
			DESTROY = 0x0002,
			/// <summary>
			/// The WM_MOVE message is sent after a window has been moved.
			/// </summary>
			MOVE = 0x0003,
			/// <summary>
			/// The WM_SIZE message is sent to a window after its size has changed.
			/// </summary>
			SIZE = 0x0005,
			/// <summary>
			/// The WM_ACTIVATE message is sent to both the window being activated and the window being deactivated. If the windows use the same input queue, the message is sent synchronously, first to the window procedure of the top-level window being deactivated, then to the window procedure of the top-level window being activated. If the windows use different input queues, the message is sent asynchronously, so the window is activated immediately.
			/// </summary>
			ACTIVATE = 0x0006,
			/// <summary>
			/// The WM_SETFOCUS message is sent to a window after it has gained the keyboard focus.
			/// </summary>
			SETFOCUS = 0x0007,
			/// <summary>
			/// The WM_KILLFOCUS message is sent to a window immediately before it loses the keyboard focus.
			/// </summary>
			KILLFOCUS = 0x0008,
			/// <summary>
			/// The WM_ENABLE message is sent when an application changes the enabled state of a window. It is sent to the window whose enabled state is changing. This message is sent before the EnableWindow function returns, but after the enabled state (WS_DISABLED style bit) of the window has changed.
			/// </summary>
			ENABLE = 0x000A,
			/// <summary>
			/// An application sends the WM_SETREDRAW message to a window to allow changes in that window to be redrawn or to prevent changes in that window from being redrawn.
			/// </summary>
			SETREDRAW = 0x000B,
			/// <summary>
			/// An application sends a WM_SETTEXT message to set the text of a window.
			/// </summary>
			SETTEXT = 0x000C,
			/// <summary>
			/// An application sends a WM_GETTEXT message to copy the text that corresponds to a window into a buffer provided by the caller.
			/// </summary>
			GETTEXT = 0x000D,
			/// <summary>
			/// An application sends a WM_GETTEXTLENGTH message to determine the length, in characters, of the text associated with a window.
			/// </summary>
			GETTEXTLENGTH = 0x000E,
			/// <summary>
			/// The WM_PAINT message is sent when the system or another application makes a request to paint a portion of an application's window. The message is sent when the UpdateWindow or RedrawWindow function is called, or by the DispatchMessage function when the application obtains a WM_PAINT message by using the GetMessage or PeekMessage function.
			/// </summary>
			PAINT = 0x000F,
			/// <summary>
			/// The WM_CLOSE message is sent as a signal that a window or an application should terminate.
			/// </summary>
			CLOSE = 0x0010,
			/// <summary>
			/// The WM_QUERYENDSESSION message is sent when the user chooses to end the session or when an application calls one of the system shutdown functions. If any application returns zero, the session is not ended. The system stops sending WM_QUERYENDSESSION messages as soon as one application returns zero.
			/// After processing this message, the system sends the WM_ENDSESSION message with the wParam parameter set to the results of the WM_QUERYENDSESSION message.
			/// </summary>
			QUERYENDSESSION = 0x0011,
			/// <summary>
			/// The WM_QUERYOPEN message is sent to an icon when the user requests that the window be restored to its previous size and position.
			/// </summary>
			QUERYOPEN = 0x0013,
			/// <summary>
			/// The WM_ENDSESSION message is sent to an application after the system processes the results of the WM_QUERYENDSESSION message. The WM_ENDSESSION message informs the application whether the session is ending.
			/// </summary>
			ENDSESSION = 0x0016,
			/// <summary>
			/// The WM_QUIT message indicates a request to terminate an application and is generated when the application calls the PostQuitMessage function. It causes the GetMessage function to return zero.
			/// </summary>
			QUIT = 0x0012,
			/// <summary>
			/// The WM_ERASEBKGND message is sent when the window background must be erased (for example, when a window is resized). The message is sent to prepare an invalidated portion of a window for painting.
			/// </summary>
			ERASEBKGND = 0x0014,
			/// <summary>
			/// This message is sent to all top-level windows when a change is made to a system color setting.
			/// </summary>
			SYSCOLORCHANGE = 0x0015,
			/// <summary>
			/// The WM_SHOWWINDOW message is sent to a window when the window is about to be hidden or shown.
			/// </summary>
			SHOWWINDOW = 0x0018,
			/// <summary>
			/// An application sends the WM_WININICHANGE message to all top-level windows after making a change to the WIN.INI file. The SystemParametersInfo function sends this message after an application uses the function to change a setting in WIN.INI.
			/// Note  The WM_WININICHANGE message is provided only for compatibility with earlier versions of the system. Applications should use the WM_SETTINGCHANGE message.
			/// </summary>
			WININICHANGE = 0x001A,
			/// <summary>
			/// An application sends the WM_WININICHANGE message to all top-level windows after making a change to the WIN.INI file. The SystemParametersInfo function sends this message after an application uses the function to change a setting in WIN.INI.
			/// Note  The WM_WININICHANGE message is provided only for compatibility with earlier versions of the system. Applications should use the WM_SETTINGCHANGE message.
			/// </summary>
			SETTINGCHANGE = WININICHANGE,
			/// <summary>
			/// The WM_DEVMODECHANGE message is sent to all top-level windows whenever the user changes device-mode settings.
			/// </summary>
			DEVMODECHANGE = 0x001B,
			/// <summary>
			/// The WM_ACTIVATEAPP message is sent when a window belonging to a different application than the active window is about to be activated. The message is sent to the application whose window is being activated and to the application whose window is being deactivated.
			/// </summary>
			ACTIVATEAPP = 0x001C,
			/// <summary>
			/// An application sends the WM_FONTCHANGE message to all top-level windows in the system after changing the pool of font resources.
			/// </summary>
			FONTCHANGE = 0x001D,
			/// <summary>
			/// A message that is sent whenever there is a change in the system time.
			/// </summary>
			TIMECHANGE = 0x001E,
			/// <summary>
			/// The WM_CANCELMODE message is sent to cancel certain modes, such as mouse capture. For example, the system sends this message to the active window when a dialog box or message box is displayed. Certain functions also send this message explicitly to the specified window regardless of whether it is the active window. For example, the EnableWindow function sends this message when disabling the specified window.
			/// </summary>
			CANCELMODE = 0x001F,
			/// <summary>
			/// The WM_SETCURSOR message is sent to a window if the mouse causes the cursor to move within a window and mouse input is not captured.
			/// </summary>
			SETCURSOR = 0x0020,
			/// <summary>
			/// The WM_MOUSEACTIVATE message is sent when the cursor is in an inactive window and the user presses a mouse button. The parent window receives this message only if the child window passes it to the DefWindowProc function.
			/// </summary>
			MOUSEACTIVATE = 0x0021,
			/// <summary>
			/// The WM_CHILDACTIVATE message is sent to a child window when the user clicks the window's title bar or when the window is activated, moved, or sized.
			/// </summary>
			CHILDACTIVATE = 0x0022,
			/// <summary>
			/// The WM_QUEUESYNC message is sent by a computer-based training (CBT) application to separate user-input messages from other messages sent through the WH_JOURNALPLAYBACK Hook procedure.
			/// </summary>
			QUEUESYNC = 0x0023,
			/// <summary>
			/// The WM_GETMINMAXINFO message is sent to a window when the size or position of the window is about to change. An application can use this message to override the window's default maximized size and position, or its default minimum or maximum tracking size.
			/// </summary>
			GETMINMAXINFO = 0x0024,
			/// <summary>
			/// Windows NT 3.51 and earlier: The WM_PAINTICON message is sent to a minimized window when the icon is to be painted. This message is not sent by newer versions of Microsoft Windows, except in unusual circumstances explained in the Remarks.
			/// </summary>
			PAINTICON = 0x0026,
			/// <summary>
			/// Windows NT 3.51 and earlier: The WM_ICONERASEBKGND message is sent to a minimized window when the background of the icon must be filled before painting the icon. A window receives this message only if a class icon is defined for the window; otherwise, WM_ERASEBKGND is sent. This message is not sent by newer versions of Windows.
			/// </summary>
			ICONERASEBKGND = 0x0027,
			/// <summary>
			/// The WM_NEXTDLGCTL message is sent to a dialog box procedure to set the keyboard focus to a different control in the dialog box.
			/// </summary>
			NEXTDLGCTL = 0x0028,
			/// <summary>
			/// The WM_SPOOLERSTATUS message is sent from Print Manager whenever a job is added to or removed from the Print Manager queue.
			/// </summary>
			SPOOLERSTATUS = 0x002A,
			/// <summary>
			/// The WM_DRAWITEM message is sent to the parent window of an owner-drawn button, combo box, list box, or menu when a visual aspect of the button, combo box, list box, or menu has changed.
			/// </summary>
			DRAWITEM = 0x002B,
			/// <summary>
			/// The WM_MEASUREITEM message is sent to the owner window of a combo box, list box, list view control, or menu item when the control or menu is created.
			/// </summary>
			MEASUREITEM = 0x002C,
			/// <summary>
			/// Sent to the owner of a list box or combo box when the list box or combo box is destroyed or when items are removed by the LB_DELETESTRING, LB_RESETCONTENT, CB_DELETESTRING, or CB_RESETCONTENT message. The system sends a WM_DELETEITEM message for each deleted item. The system sends the WM_DELETEITEM message for any deleted list box or combo box item with nonzero item data.
			/// </summary>
			DELETEITEM = 0x002D,
			/// <summary>
			/// Sent by a list box with the LBS_WANTKEYBOARDINPUT style to its owner in response to a WM_KEYDOWN message.
			/// </summary>
			VKEYTOITEM = 0x002E,
			/// <summary>
			/// Sent by a list box with the LBS_WANTKEYBOARDINPUT style to its owner in response to a WM_CHAR message.
			/// </summary>
			CHARTOITEM = 0x002F,
			/// <summary>
			/// An application sends a WM_SETFONT message to specify the font that a control is to use when drawing text.
			/// </summary>
			SETFONT = 0x0030,
			/// <summary>
			/// An application sends a WM_GETFONT message to a control to retrieve the font with which the control is currently drawing its text.
			/// </summary>
			GETFONT = 0x0031,
			/// <summary>
			/// An application sends a WM_SETHOTKEY message to a window to associate a hot key with the window. When the user presses the hot key, the system activates the window.
			/// </summary>
			SETHOTKEY = 0x0032,
			/// <summary>
			/// An application sends a WM_GETHOTKEY message to determine the hot key associated with a window.
			/// </summary>
			GETHOTKEY = 0x0033,
			/// <summary>
			/// The WM_QUERYDRAGICON message is sent to a minimized (iconic) window. The window is about to be dragged by the user but does not have an icon defined for its class. An application can return a handle to an icon or cursor. The system displays this cursor or icon while the user drags the icon.
			/// </summary>
			QUERYDRAGICON = 0x0037,
			/// <summary>
			/// The system sends the WM_COMPAREITEM message to determine the relative position of a new item in the sorted list of an owner-drawn combo box or list box. Whenever the application adds a new item, the system sends this message to the owner of a combo box or list box created with the CBS_SORT or LBS_SORT style.
			/// </summary>
			COMPAREITEM = 0x0039,
			/// <summary>
			/// Active Accessibility sends the WM_GETOBJECT message to obtain information about an accessible object contained in a server application.
			/// Applications never send this message directly. It is sent only by Active Accessibility in response to calls to AccessibleObjectFromPoint, AccessibleObjectFromEvent, or AccessibleObjectFromWindow. However, server applications handle this message.
			/// </summary>
			GETOBJECT = 0x003D,
			/// <summary>
			/// The WM_COMPACTING message is sent to all top-level windows when the system detects more than 12.5 percent of system time over a 30- to 60-second interval is being spent compacting memory. This indicates that system memory is low.
			/// </summary>
			COMPACTING = 0x0041,
			/// <summary>
			/// WM_COMMNOTIFY is Obsolete for Win32-Based Applications
			/// </summary>
			[Obsolete]
			COMMNOTIFY = 0x0044,
			/// <summary>
			/// The WM_WINDOWPOSCHANGING message is sent to a window whose size, position, or place in the Z order is about to change as a result of a call to the SetWindowPos function or another window-management function.
			/// </summary>
			WINDOWPOSCHANGING = 0x0046,
			/// <summary>
			/// The WM_WINDOWPOSCHANGED message is sent to a window whose size, position, or place in the Z order has changed as a result of a call to the SetWindowPos function or another window-management function.
			/// </summary>
			WINDOWPOSCHANGED = 0x0047,
			/// <summary>
			/// Notifies applications that the system, typically a battery-powered personal computer, is about to enter a suspended mode.
			/// Use: POWERBROADCAST
			/// </summary>
			[Obsolete]
			POWER = 0x0048,
			/// <summary>
			/// An application sends the WM_COPYDATA message to pass data to another application.
			/// </summary>
			COPYDATA = 0x004A,
			/// <summary>
			/// The WM_CANCELJOURNAL message is posted to an application when a user cancels the application's journaling activities. The message is posted with a NULL window handle.
			/// </summary>
			CANCELJOURNAL = 0x004B,
			/// <summary>
			/// Sent by a common control to its parent window when an event has occurred or the control requires some information.
			/// </summary>
			NOTIFY = 0x004E,
			/// <summary>
			/// The WM_INPUTLANGCHANGEREQUEST message is posted to the window with the focus when the user chooses a new input language, either with the hotkey (specified in the Keyboard control panel application) or from the indicator on the system taskbar. An application can accept the change by passing the message to the DefWindowProc function or reject the change (and prevent it from taking place) by returning immediately.
			/// </summary>
			INPUTLANGCHANGEREQUEST = 0x0050,
			/// <summary>
			/// The WM_INPUTLANGCHANGE message is sent to the topmost affected window after an application's input language has been changed. You should make any application-specific settings and pass the message to the DefWindowProc function, which passes the message to all first-level child windows. These child windows can pass the message to DefWindowProc to have it pass the message to their child windows, and so on.
			/// </summary>
			INPUTLANGCHANGE = 0x0051,
			/// <summary>
			/// Sent to an application that has initiated a training card with Microsoft Windows Help. The message informs the application when the user clicks an authorable button. An application initiates a training card by specifying the HELP_TCARD command in a call to the WinHelp function.
			/// </summary>
			TCARD = 0x0052,
			/// <summary>
			/// Indicates that the user pressed the F1 key. If a menu is active when F1 is pressed, WM_HELP is sent to the window associated with the menu; otherwise, WM_HELP is sent to the window that has the keyboard focus. If no window has the keyboard focus, WM_HELP is sent to the currently active window.
			/// </summary>
			HELP = 0x0053,
			/// <summary>
			/// The WM_USERCHANGED message is sent to all windows after the user has logged on or off. When the user logs on or off, the system updates the user-specific settings. The system sends this message immediately after updating the settings.
			/// </summary>
			USERCHANGED = 0x0054,
			/// <summary>
			/// Determines if a window accepts ANSI or Unicode structures in the WM_NOTIFY notification message. WM_NOTIFYFORMAT messages are sent from a common control to its parent window and from the parent window to the common control.
			/// </summary>
			NOTIFYFORMAT = 0x0055,
			/// <summary>
			/// The WM_CONTEXTMENU message notifies a window that the user clicked the right mouse button (right-clicked) in the window.
			/// </summary>
			CONTEXTMENU = 0x007B,
			/// <summary>
			/// The WM_STYLECHANGING message is sent to a window when the SetWindowLong function is about to change one or more of the window's styles.
			/// </summary>
			STYLECHANGING = 0x007C,
			/// <summary>
			/// The WM_STYLECHANGED message is sent to a window after the SetWindowLong function has changed one or more of the window's styles
			/// </summary>
			STYLECHANGED = 0x007D,
			/// <summary>
			/// The WM_DISPLAYCHANGE message is sent to all windows when the display resolution has changed.
			/// </summary>
			DISPLAYCHANGE = 0x007E,
			/// <summary>
			/// The WM_GETICON message is sent to a window to retrieve a handle to the large or small icon associated with a window. The system displays the large icon in the ALT+TAB dialog, and the small icon in the window caption.
			/// </summary>
			GETICON = 0x007F,
			/// <summary>
			/// An application sends the WM_SETICON message to associate a new large or small icon with a window. The system displays the large icon in the ALT+TAB dialog box, and the small icon in the window caption.
			/// </summary>
			SETICON = 0x0080,
			/// <summary>
			/// The WM_NCCREATE message is sent prior to the WM_CREATE message when a window is first created.
			/// </summary>
			NCCREATE = 0x0081,
			/// <summary>
			/// The WM_NCDESTROY message informs a window that its nonclient area is being destroyed. The DestroyWindow function sends the WM_NCDESTROY message to the window following the WM_DESTROY message. WM_DESTROY is used to free the allocated memory object associated with the window.
			/// The WM_NCDESTROY message is sent after the child windows have been destroyed. In contrast, WM_DESTROY is sent before the child windows are destroyed.
			/// </summary>
			NCDESTROY = 0x0082,
			/// <summary>
			/// The WM_NCCALCSIZE message is sent when the size and position of a window's client area must be calculated. By processing this message, an application can control the content of the window's client area when the size or position of the window changes.
			/// </summary>
			NCCALCSIZE = 0x0083,
			/// <summary>
			/// The WM_NCHITTEST message is sent to a window when the cursor moves, or when a mouse button is pressed or released. If the mouse is not captured, the message is sent to the window beneath the cursor. Otherwise, the message is sent to the window that has captured the mouse.
			/// </summary>
			NCHITTEST = 0x0084,
			/// <summary>
			/// The WM_NCPAINT message is sent to a window when its frame must be painted.
			/// </summary>
			NCPAINT = 0x0085,
			/// <summary>
			/// The WM_NCACTIVATE message is sent to a window when its nonclient area needs to be changed to indicate an active or inactive state.
			/// </summary>
			NCACTIVATE = 0x0086,
			/// <summary>
			/// The WM_GETDLGCODE message is sent to the window procedure associated with a control. By default, the system handles all keyboard input to the control; the system interprets certain types of keyboard input as dialog box navigation keys. To override this default behavior, the control can respond to the WM_GETDLGCODE message to indicate the types of input it wants to process itself.
			/// </summary>
			GETDLGCODE = 0x0087,
			/// <summary>
			/// The WM_SYNCPAINT message is used to synchronize painting while avoiding linking independent GUI threads.
			/// </summary>
			SYNCPAINT = 0x0088,
			/// <summary>
			/// The WM_NCMOUSEMOVE message is posted to a window when the cursor is moved within the nonclient area of the window. This message is posted to the window that contains the cursor. If a window has captured the mouse, this message is not posted.
			/// </summary>
			NCMOUSEMOVE = 0x00A0,
			/// <summary>
			/// The WM_NCLBUTTONDOWN message is posted when the user presses the left mouse button while the cursor is within the nonclient area of a window. This message is posted to the window that contains the cursor. If a window has captured the mouse, this message is not posted.
			/// </summary>
			NCLBUTTONDOWN = 0x00A1,
			/// <summary>
			/// The WM_NCLBUTTONUP message is posted when the user releases the left mouse button while the cursor is within the nonclient area of a window. This message is posted to the window that contains the cursor. If a window has captured the mouse, this message is not posted.
			/// </summary>
			NCLBUTTONUP = 0x00A2,
			/// <summary>
			/// The WM_NCLBUTTONDBLCLK message is posted when the user double-clicks the left mouse button while the cursor is within the nonclient area of a window. This message is posted to the window that contains the cursor. If a window has captured the mouse, this message is not posted.
			/// </summary>
			NCLBUTTONDBLCLK = 0x00A3,
			/// <summary>
			/// The WM_NCRBUTTONDOWN message is posted when the user presses the right mouse button while the cursor is within the nonclient area of a window. This message is posted to the window that contains the cursor. If a window has captured the mouse, this message is not posted.
			/// </summary>
			NCRBUTTONDOWN = 0x00A4,
			/// <summary>
			/// The WM_NCRBUTTONUP message is posted when the user releases the right mouse button while the cursor is within the nonclient area of a window. This message is posted to the window that contains the cursor. If a window has captured the mouse, this message is not posted.
			/// </summary>
			NCRBUTTONUP = 0x00A5,
			/// <summary>
			/// The WM_NCRBUTTONDBLCLK message is posted when the user double-clicks the right mouse button while the cursor is within the nonclient area of a window. This message is posted to the window that contains the cursor. If a window has captured the mouse, this message is not posted.
			/// </summary>
			NCRBUTTONDBLCLK = 0x00A6,
			/// <summary>
			/// The WM_NCMBUTTONDOWN message is posted when the user presses the middle mouse button while the cursor is within the nonclient area of a window. This message is posted to the window that contains the cursor. If a window has captured the mouse, this message is not posted.
			/// </summary>
			NCMBUTTONDOWN = 0x00A7,
			/// <summary>
			/// The WM_NCMBUTTONUP message is posted when the user releases the middle mouse button while the cursor is within the nonclient area of a window. This message is posted to the window that contains the cursor. If a window has captured the mouse, this message is not posted.
			/// </summary>
			NCMBUTTONUP = 0x00A8,
			/// <summary>
			/// The WM_NCMBUTTONDBLCLK message is posted when the user double-clicks the middle mouse button while the cursor is within the nonclient area of a window. This message is posted to the window that contains the cursor. If a window has captured the mouse, this message is not posted.
			/// </summary>
			NCMBUTTONDBLCLK = 0x00A9,
			/// <summary>
			/// The WM_NCXBUTTONDOWN message is posted when the user presses the first or second X button while the cursor is in the nonclient area of a window. This message is posted to the window that contains the cursor. If a window has captured the mouse, this message is not posted.
			/// </summary>
			NCXBUTTONDOWN = 0x00AB,
			/// <summary>
			/// The WM_NCXBUTTONUP message is posted when the user releases the first or second X button while the cursor is in the nonclient area of a window. This message is posted to the window that contains the cursor. If a window has captured the mouse, this message is not posted.
			/// </summary>
			NCXBUTTONUP = 0x00AC,
			/// <summary>
			/// The WM_NCXBUTTONDBLCLK message is posted when the user double-clicks the first or second X button while the cursor is in the nonclient area of a window. This message is posted to the window that contains the cursor. If a window has captured the mouse, this message is not posted.
			/// </summary>
			NCXBUTTONDBLCLK = 0x00AD,
			/// <summary>
			/// The WM_INPUT_DEVICE_CHANGE message is sent to the window that registered to receive raw input. A window receives this message through its WindowProc function.
			/// </summary>
			INPUT_DEVICE_CHANGE = 0x00FE,
			/// <summary>
			/// The WM_INPUT message is sent to the window that is getting raw input.
			/// </summary>
			INPUT = 0x00FF,
			/// <summary>
			/// This message filters for keyboard messages.
			/// </summary>
			KEYFIRST = 0x0100,
			/// <summary>
			/// The WM_KEYDOWN message is posted to the window with the keyboard focus when a nonsystem key is pressed. A nonsystem key is a key that is pressed when the ALT key is not pressed.
			/// </summary>
			KEYDOWN = 0x0100,
			/// <summary>
			/// The WM_KEYUP message is posted to the window with the keyboard focus when a nonsystem key is released. A nonsystem key is a key that is pressed when the ALT key is not pressed, or a keyboard key that is pressed when a window has the keyboard focus.
			/// </summary>
			KEYUP = 0x0101,
			/// <summary>
			/// The WM_CHAR message is posted to the window with the keyboard focus when a WM_KEYDOWN message is translated by the TranslateMessage function. The WM_CHAR message contains the character code of the key that was pressed.
			/// </summary>
			CHAR = 0x0102,
			/// <summary>
			/// The WM_DEADCHAR message is posted to the window with the keyboard focus when a WM_KEYUP message is translated by the TranslateMessage function. WM_DEADCHAR specifies a character code generated by a dead key. A dead key is a key that generates a character, such as the umlaut (double-dot), that is combined with another character to form a composite character. For example, the umlaut-O character (Ö) is generated by typing the dead key for the umlaut character, and then typing the O key.
			/// </summary>
			DEADCHAR = 0x0103,
			/// <summary>
			/// The WM_SYSKEYDOWN message is posted to the window with the keyboard focus when the user presses the F10 key (which activates the menu bar) or holds down the ALT key and then presses another key. It also occurs when no window currently has the keyboard focus; in this case, the WM_SYSKEYDOWN message is sent to the active window. The window that receives the message can distinguish between these two contexts by checking the context code in the lParam parameter.
			/// </summary>
			SYSKEYDOWN = 0x0104,
			/// <summary>
			/// The WM_SYSKEYUP message is posted to the window with the keyboard focus when the user releases a key that was pressed while the ALT key was held down. It also occurs when no window currently has the keyboard focus; in this case, the WM_SYSKEYUP message is sent to the active window. The window that receives the message can distinguish between these two contexts by checking the context code in the lParam parameter.
			/// </summary>
			SYSKEYUP = 0x0105,
			/// <summary>
			/// The WM_SYSCHAR message is posted to the window with the keyboard focus when a WM_SYSKEYDOWN message is translated by the TranslateMessage function. It specifies the character code of a system character key — that is, a character key that is pressed while the ALT key is down.
			/// </summary>
			SYSCHAR = 0x0106,
			/// <summary>
			/// The WM_SYSDEADCHAR message is sent to the window with the keyboard focus when a WM_SYSKEYDOWN message is translated by the TranslateMessage function. WM_SYSDEADCHAR specifies the character code of a system dead key — that is, a dead key that is pressed while holding down the ALT key.
			/// </summary>
			SYSDEADCHAR = 0x0107,
			/// <summary>
			/// The WM_UNICHAR message is posted to the window with the keyboard focus when a WM_KEYDOWN message is translated by the TranslateMessage function. The WM_UNICHAR message contains the character code of the key that was pressed.
			/// The WM_UNICHAR message is equivalent to WM_CHAR, but it uses Unicode Transformation Format (UTF)-32, whereas WM_CHAR uses UTF-16. It is designed to send or post Unicode characters to ANSI windows and it can can handle Unicode Supplementary Plane characters.
			/// </summary>
			UNICHAR = 0x0109,
			/// <summary>
			/// This message filters for keyboard messages.
			/// </summary>
			KEYLAST = 0x0108,
			/// <summary>
			/// Sent immediately before the IME generates the composition string as a result of a keystroke. A window receives this message through its WindowProc function.
			/// </summary>
			IME_STARTCOMPOSITION = 0x010D,
			/// <summary>
			/// Sent to an application when the IME ends composition. A window receives this message through its WindowProc function.
			/// </summary>
			IME_ENDCOMPOSITION = 0x010E,
			/// <summary>
			/// Sent to an application when the IME changes composition status as a result of a keystroke. A window receives this message through its WindowProc function.
			/// </summary>
			IME_COMPOSITION = 0x010F,
			IME_KEYLAST = 0x010F,
			/// <summary>
			/// The WM_INITDIALOG message is sent to the dialog box procedure immediately before a dialog box is displayed. Dialog box procedures typically use this message to initialize controls and carry out any other initialization tasks that affect the appearance of the dialog box.
			/// </summary>
			INITDIALOG = 0x0110,
			/// <summary>
			/// The WM_COMMAND message is sent when the user selects a command item from a menu, when a control sends a notification message to its parent window, or when an accelerator keystroke is translated.
			/// </summary>
			COMMAND = 0x0111,
			/// <summary>
			/// A window receives this message when the user chooses a command from the Window menu, clicks the maximize button, minimize button, restore button, close button, or moves the form. You can stop the form from moving by filtering this out.
			/// </summary>
			SYSCOMMAND = 0x0112,
			/// <summary>
			/// The WM_TIMER message is posted to the installing thread's message queue when a timer expires. The message is posted by the GetMessage or PeekMessage function.
			/// </summary>
			TIMER = 0x0113,
			/// <summary>
			/// The WM_HSCROLL message is sent to a window when a scroll event occurs in the window's standard horizontal scroll bar. This message is also sent to the owner of a horizontal scroll bar control when a scroll event occurs in the control.
			/// </summary>
			HSCROLL = 0x0114,
			/// <summary>
			/// The WM_VSCROLL message is sent to a window when a scroll event occurs in the window's standard vertical scroll bar. This message is also sent to the owner of a vertical scroll bar control when a scroll event occurs in the control.
			/// </summary>
			VSCROLL = 0x0115,
			/// <summary>
			/// The WM_INITMENU message is sent when a menu is about to become active. It occurs when the user clicks an item on the menu bar or presses a menu key. This allows the application to modify the menu before it is displayed.
			/// </summary>
			INITMENU = 0x0116,
			/// <summary>
			/// The WM_INITMENUPOPUP message is sent when a drop-down menu or submenu is about to become active. This allows an application to modify the menu before it is displayed, without changing the entire menu.
			/// </summary>
			INITMENUPOPUP = 0x0117,
			/// <summary>
			/// The WM_MENUSELECT message is sent to a menu's owner window when the user selects a menu item.
			/// </summary>
			MENUSELECT = 0x011F,
			/// <summary>
			/// The WM_MENUCHAR message is sent when a menu is active and the user presses a key that does not correspond to any mnemonic or accelerator key. This message is sent to the window that owns the menu.
			/// </summary>
			MENUCHAR = 0x0120,
			/// <summary>
			/// The WM_ENTERIDLE message is sent to the owner window of a modal dialog box or menu that is entering an idle state. A modal dialog box or menu enters an idle state when no messages are waiting in its queue after it has processed one or more previous messages.
			/// </summary>
			ENTERIDLE = 0x0121,
			/// <summary>
			/// The WM_MENURBUTTONUP message is sent when the user releases the right mouse button while the cursor is on a menu item.
			/// </summary>
			MENURBUTTONUP = 0x0122,
			/// <summary>
			/// The WM_MENUDRAG message is sent to the owner of a drag-and-drop menu when the user drags a menu item.
			/// </summary>
			MENUDRAG = 0x0123,
			/// <summary>
			/// The WM_MENUGETOBJECT message is sent to the owner of a drag-and-drop menu when the mouse cursor enters a menu item or moves from the center of the item to the top or bottom of the item.
			/// </summary>
			MENUGETOBJECT = 0x0124,
			/// <summary>
			/// The WM_UNINITMENUPOPUP message is sent when a drop-down menu or submenu has been destroyed.
			/// </summary>
			UNINITMENUPOPUP = 0x0125,
			/// <summary>
			/// The WM_MENUCOMMAND message is sent when the user makes a selection from a menu.
			/// </summary>
			MENUCOMMAND = 0x0126,
			/// <summary>
			/// An application sends the WM_CHANGEUISTATE message to indicate that the user interface (UI) state should be changed.
			/// </summary>
			CHANGEUISTATE = 0x0127,
			/// <summary>
			/// An application sends the WM_UPDATEUISTATE message to change the user interface (UI) state for the specified window and all its child windows.
			/// </summary>
			UPDATEUISTATE = 0x0128,
			/// <summary>
			/// An application sends the WM_QUERYUISTATE message to retrieve the user interface (UI) state for a window.
			/// </summary>
			QUERYUISTATE = 0x0129,
			/// <summary>
			/// The WM_CTLCOLORMSGBOX message is sent to the owner window of a message box before Windows draws the message box. By responding to this message, the owner window can set the text and background colors of the message box by using the given display device context handle.
			/// </summary>
			CTLCOLORMSGBOX = 0x0132,
			/// <summary>
			/// An edit control that is not read-only or disabled sends the WM_CTLCOLOREDIT message to its parent window when the control is about to be drawn. By responding to this message, the parent window can use the specified device context handle to set the text and background colors of the edit control.
			/// </summary>
			CTLCOLOREDIT = 0x0133,
			/// <summary>
			/// Sent to the parent window of a list box before the system draws the list box. By responding to this message, the parent window can set the text and background colors of the list box by using the specified display device context handle.
			/// </summary>
			CTLCOLORLISTBOX = 0x0134,
			/// <summary>
			/// The WM_CTLCOLORBTN message is sent to the parent window of a button before drawing the button. The parent window can change the button's text and background colors. However, only owner-drawn buttons respond to the parent window processing this message.
			/// </summary>
			CTLCOLORBTN = 0x0135,
			/// <summary>
			/// The WM_CTLCOLORDLG message is sent to a dialog box before the system draws the dialog box. By responding to this message, the dialog box can set its text and background colors using the specified display device context handle.
			/// </summary>
			CTLCOLORDLG = 0x0136,
			/// <summary>
			/// The WM_CTLCOLORSCROLLBAR message is sent to the parent window of a scroll bar control when the control is about to be drawn. By responding to this message, the parent window can use the display context handle to set the background color of the scroll bar control.
			/// </summary>
			CTLCOLORSCROLLBAR = 0x0137,
			/// <summary>
			/// A static control, or an edit control that is read-only or disabled, sends the WM_CTLCOLORSTATIC message to its parent window when the control is about to be drawn. By responding to this message, the parent window can use the specified device context handle to set the text and background colors of the static control.
			/// </summary>
			CTLCOLORSTATIC = 0x0138,
			/// <summary>
			/// Use WM_MOUSEFIRST to specify the first mouse message. Use the PeekMessage() Function.
			/// </summary>
			MOUSEFIRST = 0x0200,
			/// <summary>
			/// The WM_MOUSEMOVE message is posted to a window when the cursor moves. If the mouse is not captured, the message is posted to the window that contains the cursor. Otherwise, the message is posted to the window that has captured the mouse.
			/// </summary>
			MOUSEMOVE = 0x0200,
			/// <summary>
			/// The WM_LBUTTONDOWN message is posted when the user presses the left mouse button while the cursor is in the client area of a window. If the mouse is not captured, the message is posted to the window beneath the cursor. Otherwise, the message is posted to the window that has captured the mouse.
			/// </summary>
			LBUTTONDOWN = 0x0201,
			/// <summary>
			/// The WM_LBUTTONUP message is posted when the user releases the left mouse button while the cursor is in the client area of a window. If the mouse is not captured, the message is posted to the window beneath the cursor. Otherwise, the message is posted to the window that has captured the mouse.
			/// </summary>
			LBUTTONUP = 0x0202,
			/// <summary>
			/// The WM_LBUTTONDBLCLK message is posted when the user double-clicks the left mouse button while the cursor is in the client area of a window. If the mouse is not captured, the message is posted to the window beneath the cursor. Otherwise, the message is posted to the window that has captured the mouse.
			/// </summary>
			LBUTTONDBLCLK = 0x0203,
			/// <summary>
			/// The WM_RBUTTONDOWN message is posted when the user presses the right mouse button while the cursor is in the client area of a window. If the mouse is not captured, the message is posted to the window beneath the cursor. Otherwise, the message is posted to the window that has captured the mouse.
			/// </summary>
			RBUTTONDOWN = 0x0204,
			/// <summary>
			/// The WM_RBUTTONUP message is posted when the user releases the right mouse button while the cursor is in the client area of a window. If the mouse is not captured, the message is posted to the window beneath the cursor. Otherwise, the message is posted to the window that has captured the mouse.
			/// </summary>
			RBUTTONUP = 0x0205,
			/// <summary>
			/// The WM_RBUTTONDBLCLK message is posted when the user double-clicks the right mouse button while the cursor is in the client area of a window. If the mouse is not captured, the message is posted to the window beneath the cursor. Otherwise, the message is posted to the window that has captured the mouse.
			/// </summary>
			RBUTTONDBLCLK = 0x0206,
			/// <summary>
			/// The WM_MBUTTONDOWN message is posted when the user presses the middle mouse button while the cursor is in the client area of a window. If the mouse is not captured, the message is posted to the window beneath the cursor. Otherwise, the message is posted to the window that has captured the mouse.
			/// </summary>
			MBUTTONDOWN = 0x0207,
			/// <summary>
			/// The WM_MBUTTONUP message is posted when the user releases the middle mouse button while the cursor is in the client area of a window. If the mouse is not captured, the message is posted to the window beneath the cursor. Otherwise, the message is posted to the window that has captured the mouse.
			/// </summary>
			MBUTTONUP = 0x0208,
			/// <summary>
			/// The WM_MBUTTONDBLCLK message is posted when the user double-clicks the middle mouse button while the cursor is in the client area of a window. If the mouse is not captured, the message is posted to the window beneath the cursor. Otherwise, the message is posted to the window that has captured the mouse.
			/// </summary>
			MBUTTONDBLCLK = 0x0209,
			/// <summary>
			/// The WM_MOUSEWHEEL message is sent to the focus window when the mouse wheel is rotated. The DefWindowProc function propagates the message to the window's parent. There should be no internal forwarding of the message, since DefWindowProc propagates it up the parent chain until it finds a window that processes it.
			/// </summary>
			MOUSEWHEEL = 0x020A,
			/// <summary>
			/// The WM_XBUTTONDOWN message is posted when the user presses the first or second X button while the cursor is in the client area of a window. If the mouse is not captured, the message is posted to the window beneath the cursor. Otherwise, the message is posted to the window that has captured the mouse.
			/// </summary>
			XBUTTONDOWN = 0x020B,
			/// <summary>
			/// The WM_XBUTTONUP message is posted when the user releases the first or second X button while the cursor is in the client area of a window. If the mouse is not captured, the message is posted to the window beneath the cursor. Otherwise, the message is posted to the window that has captured the mouse.
			/// </summary>
			XBUTTONUP = 0x020C,
			/// <summary>
			/// The WM_XBUTTONDBLCLK message is posted when the user double-clicks the first or second X button while the cursor is in the client area of a window. If the mouse is not captured, the message is posted to the window beneath the cursor. Otherwise, the message is posted to the window that has captured the mouse.
			/// </summary>
			XBUTTONDBLCLK = 0x020D,
			/// <summary>
			/// The WM_MOUSEHWHEEL message is sent to the focus window when the mouse's horizontal scroll wheel is tilted or rotated. The DefWindowProc function propagates the message to the window's parent. There should be no internal forwarding of the message, since DefWindowProc propagates it up the parent chain until it finds a window that processes it.
			/// </summary>
			MOUSEHWHEEL = 0x020E,
			/// <summary>
			/// Use WM_MOUSELAST to specify the last mouse message. Used with PeekMessage() Function.
			/// </summary>
			MOUSELAST = 0x020E,
			/// <summary>
			/// The WM_PARENTNOTIFY message is sent to the parent of a child window when the child window is created or destroyed, or when the user clicks a mouse button while the cursor is over the child window. When the child window is being created, the system sends WM_PARENTNOTIFY just before the CreateWindow or CreateWindowEx function that creates the window returns. When the child window is being destroyed, the system sends the message before any processing to destroy the window takes place.
			/// </summary>
			PARENTNOTIFY = 0x0210,
			/// <summary>
			/// The WM_ENTERMENULOOP message informs an application's main window procedure that a menu modal loop has been entered.
			/// </summary>
			ENTERMENULOOP = 0x0211,
			/// <summary>
			/// The WM_EXITMENULOOP message informs an application's main window procedure that a menu modal loop has been exited.
			/// </summary>
			EXITMENULOOP = 0x0212,
			/// <summary>
			/// The WM_NEXTMENU message is sent to an application when the right or left arrow key is used to switch between the menu bar and the system menu.
			/// </summary>
			NEXTMENU = 0x0213,
			/// <summary>
			/// The WM_SIZING message is sent to a window that the user is resizing. By processing this message, an application can monitor the size and position of the drag rectangle and, if needed, change its size or position.
			/// </summary>
			SIZING = 0x0214,
			/// <summary>
			/// The WM_CAPTURECHANGED message is sent to the window that is losing the mouse capture.
			/// </summary>
			CAPTURECHANGED = 0x0215,
			/// <summary>
			/// The WM_MOVING message is sent to a window that the user is moving. By processing this message, an application can monitor the position of the drag rectangle and, if needed, change its position.
			/// </summary>
			MOVING = 0x0216,
			/// <summary>
			/// Notifies applications that a power-management event has occurred.
			/// </summary>
			POWERBROADCAST = 0x0218,
			/// <summary>
			/// Notifies an application of a change to the hardware configuration of a device or the computer.
			/// </summary>
			DEVICECHANGE = 0x0219,
			/// <summary>
			/// An application sends the WM_MDICREATE message to a multiple-document interface (MDI) client window to create an MDI child window.
			/// </summary>
			MDICREATE = 0x0220,
			/// <summary>
			/// An application sends the WM_MDIDESTROY message to a multiple-document interface (MDI) client window to close an MDI child window.
			/// </summary>
			MDIDESTROY = 0x0221,
			/// <summary>
			/// An application sends the WM_MDIACTIVATE message to a multiple-document interface (MDI) client window to instruct the client window to activate a different MDI child window.
			/// </summary>
			MDIACTIVATE = 0x0222,
			/// <summary>
			/// An application sends the WM_MDIRESTORE message to a multiple-document interface (MDI) client window to restore an MDI child window from maximized or minimized size.
			/// </summary>
			MDIRESTORE = 0x0223,
			/// <summary>
			/// An application sends the WM_MDINEXT message to a multiple-document interface (MDI) client window to activate the next or previous child window.
			/// </summary>
			MDINEXT = 0x0224,
			/// <summary>
			/// An application sends the WM_MDIMAXIMIZE message to a multiple-document interface (MDI) client window to maximize an MDI child window. The system resizes the child window to make its client area fill the client window. The system places the child window's window menu icon in the rightmost position of the frame window's menu bar, and places the child window's restore icon in the leftmost position. The system also appends the title bar text of the child window to that of the frame window.
			/// </summary>
			MDIMAXIMIZE = 0x0225,
			/// <summary>
			/// An application sends the WM_MDITILE message to a multiple-document interface (MDI) client window to arrange all of its MDI child windows in a tile format.
			/// </summary>
			MDITILE = 0x0226,
			/// <summary>
			/// An application sends the WM_MDICASCADE message to a multiple-document interface (MDI) client window to arrange all its child windows in a cascade format.
			/// </summary>
			MDICASCADE = 0x0227,
			/// <summary>
			/// An application sends the WM_MDIICONARRANGE message to a multiple-document interface (MDI) client window to arrange all minimized MDI child windows. It does not affect child windows that are not minimized.
			/// </summary>
			MDIICONARRANGE = 0x0228,
			/// <summary>
			/// An application sends the WM_MDIGETACTIVE message to a multiple-document interface (MDI) client window to retrieve the handle to the active MDI child window.
			/// </summary>
			MDIGETACTIVE = 0x0229,
			/// <summary>
			/// An application sends the WM_MDISETMENU message to a multiple-document interface (MDI) client window to replace the entire menu of an MDI frame window, to replace the window menu of the frame window, or both.
			/// </summary>
			MDISETMENU = 0x0230,
			/// <summary>
			/// The WM_ENTERSIZEMOVE message is sent one time to a window after it enters the moving or sizing modal loop. The window enters the moving or sizing modal loop when the user clicks the window's title bar or sizing border, or when the window passes the WM_SYSCOMMAND message to the DefWindowProc function and the wParam parameter of the message specifies the SC_MOVE or SC_SIZE value. The operation is complete when DefWindowProc returns.
			/// The system sends the WM_ENTERSIZEMOVE message regardless of whether the dragging of full windows is enabled.
			/// </summary>
			ENTERSIZEMOVE = 0x0231,
			/// <summary>
			/// The WM_EXITSIZEMOVE message is sent one time to a window, after it has exited the moving or sizing modal loop. The window enters the moving or sizing modal loop when the user clicks the window's title bar or sizing border, or when the window passes the WM_SYSCOMMAND message to the DefWindowProc function and the wParam parameter of the message specifies the SC_MOVE or SC_SIZE value. The operation is complete when DefWindowProc returns.
			/// </summary>
			EXITSIZEMOVE = 0x0232,
			/// <summary>
			/// Sent when the user drops a file on the window of an application that has registered itself as a recipient of dropped files.
			/// </summary>
			DROPFILES = 0x0233,
			/// <summary>
			/// An application sends the WM_MDIREFRESHMENU message to a multiple-document interface (MDI) client window to refresh the window menu of the MDI frame window.
			/// </summary>
			MDIREFRESHMENU = 0x0234,
			/// <summary>
			/// Sent to an application when a window is activated. A window receives this message through its WindowProc function.
			/// </summary>
			IME_SETCONTEXT = 0x0281,
			/// <summary>
			/// Sent to an application to notify it of changes to the IME window. A window receives this message through its WindowProc function.
			/// </summary>
			IME_NOTIFY = 0x0282,
			/// <summary>
			/// Sent by an application to direct the IME window to carry out the requested command. The application uses this message to control the IME window that it has created. To send this message, the application calls the SendMessage function with the following parameters.
			/// </summary>
			IME_CONTROL = 0x0283,
			/// <summary>
			/// Sent to an application when the IME window finds no space to extend the area for the composition window. A window receives this message through its WindowProc function.
			/// </summary>
			IME_COMPOSITIONFULL = 0x0284,
			/// <summary>
			/// Sent to an application when the operating system is about to change the current IME. A window receives this message through its WindowProc function.
			/// </summary>
			IME_SELECT = 0x0285,
			/// <summary>
			/// Sent to an application when the IME gets a character of the conversion result. A window receives this message through its WindowProc function.
			/// </summary>
			IME_CHAR = 0x0286,
			/// <summary>
			/// Sent to an application to provide commands and request information. A window receives this message through its WindowProc function.
			/// </summary>
			IME_REQUEST = 0x0288,
			/// <summary>
			/// Sent to an application by the IME to notify the application of a key press and to keep message order. A window receives this message through its WindowProc function.
			/// </summary>
			IME_KEYDOWN = 0x0290,
			/// <summary>
			/// Sent to an application by the IME to notify the application of a key release and to keep message order. A window receives this message through its WindowProc function.
			/// </summary>
			IME_KEYUP = 0x0291,
			/// <summary>
			/// The WM_MOUSEHOVER message is posted to a window when the cursor hovers over the client area of the window for the period of time specified in a prior call to TrackMouseEvent.
			/// </summary>
			MOUSEHOVER = 0x02A1,
			/// <summary>
			/// The WM_MOUSELEAVE message is posted to a window when the cursor leaves the client area of the window specified in a prior call to TrackMouseEvent.
			/// </summary>
			MOUSELEAVE = 0x02A3,
			/// <summary>
			/// The WM_NCMOUSEHOVER message is posted to a window when the cursor hovers over the nonclient area of the window for the period of time specified in a prior call to TrackMouseEvent.
			/// </summary>
			NCMOUSEHOVER = 0x02A0,
			/// <summary>
			/// The WM_NCMOUSELEAVE message is posted to a window when the cursor leaves the nonclient area of the window specified in a prior call to TrackMouseEvent.
			/// </summary>
			NCMOUSELEAVE = 0x02A2,
			/// <summary>
			/// The WM_WTSSESSION_CHANGE message notifies applications of changes in session state.
			/// </summary>
			WTSSESSION_CHANGE = 0x02B1,
			TABLET_FIRST = 0x02c0,
			TABLET_LAST = 0x02df,
			/// <summary>
			/// An application sends a WM_CUT message to an edit control or combo box to delete (cut) the current selection, if any, in the edit control and copy the deleted text to the clipboard in CF_TEXT format.
			/// </summary>
			CUT = 0x0300,
			/// <summary>
			/// An application sends the WM_COPY message to an edit control or combo box to copy the current selection to the clipboard in CF_TEXT format.
			/// </summary>
			COPY = 0x0301,
			/// <summary>
			/// An application sends a WM_PASTE message to an edit control or combo box to copy the current content of the clipboard to the edit control at the current caret position. Data is inserted only if the clipboard contains data in CF_TEXT format.
			/// </summary>
			PASTE = 0x0302,
			/// <summary>
			/// An application sends a WM_CLEAR message to an edit control or combo box to delete (clear) the current selection, if any, from the edit control.
			/// </summary>
			CLEAR = 0x0303,
			/// <summary>
			/// An application sends a WM_UNDO message to an edit control to undo the last operation. When this message is sent to an edit control, the previously deleted text is restored or the previously added text is deleted.
			/// </summary>
			UNDO = 0x0304,
			/// <summary>
			/// The WM_RENDERFORMAT message is sent to the clipboard owner if it has delayed rendering a specific clipboard format and if an application has requested data in that format. The clipboard owner must render data in the specified format and place it on the clipboard by calling the SetClipboardData function.
			/// </summary>
			RENDERFORMAT = 0x0305,
			/// <summary>
			/// The WM_RENDERALLFORMATS message is sent to the clipboard owner before it is destroyed, if the clipboard owner has delayed rendering one or more clipboard formats. For the content of the clipboard to remain available to other applications, the clipboard owner must render data in all the formats it is capable of generating, and place the data on the clipboard by calling the SetClipboardData function.
			/// </summary>
			RENDERALLFORMATS = 0x0306,
			/// <summary>
			/// The WM_DESTROYCLIPBOARD message is sent to the clipboard owner when a call to the EmptyClipboard function empties the clipboard.
			/// </summary>
			DESTROYCLIPBOARD = 0x0307,
			/// <summary>
			/// The WM_DRAWCLIPBOARD message is sent to the first window in the clipboard viewer chain when the content of the clipboard changes. This enables a clipboard viewer window to display the new content of the clipboard.
			/// </summary>
			DRAWCLIPBOARD = 0x0308,
			/// <summary>
			/// The WM_PAINTCLIPBOARD message is sent to the clipboard owner by a clipboard viewer window when the clipboard contains data in the CF_OWNERDISPLAY format and the clipboard viewer's client area needs repainting.
			/// </summary>
			PAINTCLIPBOARD = 0x0309,
			/// <summary>
			/// The WM_VSCROLLCLIPBOARD message is sent to the clipboard owner by a clipboard viewer window when the clipboard contains data in the CF_OWNERDISPLAY format and an event occurs in the clipboard viewer's vertical scroll bar. The owner should scroll the clipboard image and update the scroll bar values.
			/// </summary>
			VSCROLLCLIPBOARD = 0x030A,
			/// <summary>
			/// The WM_SIZECLIPBOARD message is sent to the clipboard owner by a clipboard viewer window when the clipboard contains data in the CF_OWNERDISPLAY format and the clipboard viewer's client area has changed size.
			/// </summary>
			SIZECLIPBOARD = 0x030B,
			/// <summary>
			/// The WM_ASKCBFORMATNAME message is sent to the clipboard owner by a clipboard viewer window to request the name of a CF_OWNERDISPLAY clipboard format.
			/// </summary>
			ASKCBFORMATNAME = 0x030C,
			/// <summary>
			/// The WM_CHANGECBCHAIN message is sent to the first window in the clipboard viewer chain when a window is being removed from the chain.
			/// </summary>
			CHANGECBCHAIN = 0x030D,
			/// <summary>
			/// The WM_HSCROLLCLIPBOARD message is sent to the clipboard owner by a clipboard viewer window. This occurs when the clipboard contains data in the CF_OWNERDISPLAY format and an event occurs in the clipboard viewer's horizontal scroll bar. The owner should scroll the clipboard image and update the scroll bar values.
			/// </summary>
			HSCROLLCLIPBOARD = 0x030E,
			/// <summary>
			/// This message informs a window that it is about to receive the keyboard focus, giving the window the opportunity to realize its logical palette when it receives the focus.
			/// </summary>
			QUERYNEWPALETTE = 0x030F,
			/// <summary>
			/// The WM_PALETTEISCHANGING message informs applications that an application is going to realize its logical palette.
			/// </summary>
			PALETTEISCHANGING = 0x0310,
			/// <summary>
			/// This message is sent by the OS to all top-level and overlapped windows after the window with the keyboard focus realizes its logical palette.
			/// This message enables windows that do not have the keyboard focus to realize their logical palettes and update their client areas.
			/// </summary>
			PALETTECHANGED = 0x0311,
			/// <summary>
			/// The WM_HOTKEY message is posted when the user presses a hot key registered by the RegisterHotKey function. The message is placed at the top of the message queue associated with the thread that registered the hot key.
			/// </summary>
			HOTKEY = 0x0312,
			/// <summary>
			/// The WM_PRINT message is sent to a window to request that it draw itself in the specified device context, most commonly in a printer device context.
			/// </summary>
			PRINT = 0x0317,
			/// <summary>
			/// The WM_PRINTCLIENT message is sent to a window to request that it draw its client area in the specified device context, most commonly in a printer device context.
			/// </summary>
			PRINTCLIENT = 0x0318,
			/// <summary>
			/// The WM_APPCOMMAND message notifies a window that the user generated an application command event, for example, by clicking an application command button using the mouse or typing an application command key on the keyboard.
			/// </summary>
			APPCOMMAND = 0x0319,
			/// <summary>
			/// The WM_THEMECHANGED message is broadcast to every window following a theme change event. Examples of theme change events are the activation of a theme, the deactivation of a theme, or a transition from one theme to another.
			/// </summary>
			THEMECHANGED = 0x031A,
			/// <summary>
			/// Sent when the contents of the clipboard have changed.
			/// </summary>
			CLIPBOARDUPDATE = 0x031D,
			/// <summary>
			/// The system will send a window the WM_DWMCOMPOSITIONCHANGED message to indicate that the availability of desktop composition has changed.
			/// </summary>
			DWMCOMPOSITIONCHANGED = 0x031E,
			/// <summary>
			/// WM_DWMNCRENDERINGCHANGED is called when the non-client area rendering status of a window has changed. Only windows that have set the flag DWM_BLURBEHIND.fTransitionOnMaximized to true will get this message.
			/// </summary>
			DWMNCRENDERINGCHANGED = 0x031F,
			/// <summary>
			/// Sent to all top-level windows when the colorization color has changed.
			/// </summary>
			DWMCOLORIZATIONCOLORCHANGED = 0x0320,
			/// <summary>
			/// WM_DWMWINDOWMAXIMIZEDCHANGE will let you know when a DWM composed window is maximized. You also have to register for this message as well. You'd have other windowd go opaque when this message is sent.
			/// </summary>
			DWMWINDOWMAXIMIZEDCHANGE = 0x0321,
			/// <summary>
			/// Sent to request extended title bar information. A window receives this message through its WindowProc function.
			/// </summary>
			GETTITLEBARINFOEX = 0x033F,
			HANDHELDFIRST = 0x0358,
			HANDHELDLAST = 0x035F,
			AFXFIRST = 0x0360,
			AFXLAST = 0x037F,
			PENWINFIRST = 0x0380,
			PENWINLAST = 0x038F,
			/// <summary>
			/// The WM_APP constant is used by applications to help define private messages, usually of the form WM_APP+X, where X is an integer value.
			/// </summary>
			APP = 0x8000,
			/// <summary>
			/// The WM_USER constant is used by applications to help define private messages for use by private window classes, usually of the form WM_USER+X, where X is an integer value.
			/// </summary>
			USER = 0x0400,

			/// <summary>
			/// An application sends the WM_CPL_LAUNCH message to Windows Control Panel to request that a Control Panel application be started.
			/// </summary>
			CPL_LAUNCH = USER + 0x1000,
			/// <summary>
			/// The WM_CPL_LAUNCHED message is sent when a Control Panel application, started by the WM_CPL_LAUNCH message, has closed. The WM_CPL_LAUNCHED message is sent to the window identified by the wParam parameter of the WM_CPL_LAUNCH message that started the application.
			/// </summary>
			CPL_LAUNCHED = USER + 0x1001,
			/// <summary>
			/// WM_SYSTIMER is a well-known yet still undocumented message. Windows uses WM_SYSTIMER for internal actions like scrolling.
			/// </summary>
			SYSTIMER = 0x118,

			/// <summary>
			/// The accessibility state has changed.
			/// </summary>
			HSHELL_ACCESSIBILITYSTATE = 11,
			/// <summary>
			/// The shell should activate its main window.
			/// </summary>
			HSHELL_ACTIVATESHELLWINDOW = 3,
			/// <summary>
			/// The user completed an input event (for example, pressed an application command button on the mouse or an application command key on the keyboard), and the application did not handle the WM_APPCOMMAND message generated by that input.
			/// If the Shell procedure handles the WM_COMMAND message, it should not call CallNextHookEx. See the Return Value section for more information.
			/// </summary>
			HSHELL_APPCOMMAND = 12,
			/// <summary>
			/// A window is being minimized or maximized. The system needs the coordinates of the minimized rectangle for the window.
			/// </summary>
			HSHELL_GETMINRECT = 5,
			/// <summary>
			/// Keyboard language was changed or a new keyboard layout was loaded.
			/// </summary>
			HSHELL_LANGUAGE = 8,
			/// <summary>
			/// The title of a window in the task bar has been redrawn.
			/// </summary>
			HSHELL_REDRAW = 6,
			/// <summary>
			/// The user has selected the task list. A shell application that provides a task list should return TRUE to prevent Windows from starting its task list.
			/// </summary>
			HSHELL_TASKMAN = 7,
			/// <summary>
			/// A top-level, unowned window has been created. The window exists when the system calls this hook.
			/// </summary>
			HSHELL_WINDOWCREATED = 1,
			/// <summary>
			/// A top-level, unowned window is about to be destroyed. The window still exists when the system calls this hook.
			/// </summary>
			HSHELL_WINDOWDESTROYED = 2,
			/// <summary>
			/// The activation has changed to a different top-level, unowned window.
			/// </summary>
			HSHELL_WINDOWACTIVATED = 4,
			/// <summary>
			/// A top-level window is being replaced. The window exists when the system calls this hook.
			/// </summary>
			HSHELL_WINDOWREPLACED = 13
		}

		public enum VK : int
		{
			///<summary>
			///Left mouse button
			///</summary>
			LBUTTON = 0x01,
			///<summary>
			///Right mouse button
			///</summary>
			RBUTTON = 0x02,
			///<summary>
			///Control-break processing
			///</summary>
			CANCEL = 0x03,
			///<summary>
			///Middle mouse button (three-button mouse)
			///</summary>
			MBUTTON = 0x04,
			///<summary>
			///Windows 2000/XP: X1 mouse button
			///</summary>
			XBUTTON1 = 0x05,
			///<summary>
			///Windows 2000/XP: X2 mouse button
			///</summary>
			XBUTTON2 = 0x06,
			///<summary>
			///BACKSPACE key
			///</summary>
			BACK = 0x08,
			///<summary>
			///TAB key
			///</summary>
			TAB = 0x09,
			///<summary>
			///CLEAR key
			///</summary>
			CLEAR = 0x0C,
			///<summary>
			///ENTER key
			///</summary>
			RETURN = 0x0D,
			///<summary>
			///SHIFT key
			///</summary>
			SHIFT = 0x10,
			///<summary>
			///CTRL key
			///</summary>
			CONTROL = 0x11,
			///<summary>
			///ALT key
			///</summary>
			MENU = 0x12,
			///<summary>
			///PAUSE key
			///</summary>
			PAUSE = 0x13,
			///<summary>
			///CAPS LOCK key
			///</summary>
			CAPITAL = 0x14,
			///<summary>
			///Input Method Editor (IME) Kana mode
			///</summary>
			KANA = 0x15,
			///<summary>
			///IME Hangul mode
			///</summary>
			HANGUL = 0x15,
			///<summary>
			///IME Junja mode
			///</summary>
			JUNJA = 0x17,
			///<summary>
			///IME final mode
			///</summary>
			FINAL = 0x18,
			///<summary>
			///IME Hanja mode
			///</summary>
			HANJA = 0x19,
			///<summary>
			///IME Kanji mode
			///</summary>
			KANJI = 0x19,
			///<summary>
			///ESC key
			///</summary>
			ESCAPE = 0x1B,
			///<summary>
			///IME convert
			///</summary>
			CONVERT = 0x1C,
			///<summary>
			///IME nonconvert
			///</summary>
			NONCONVERT = 0x1D,
			///<summary>
			///IME accept
			///</summary>
			ACCEPT = 0x1E,
			///<summary>
			///IME mode change request
			///</summary>
			MODECHANGE = 0x1F,
			///<summary>
			///SPACEBAR
			///</summary>
			SPACE = 0x20,
			///<summary>
			///PAGE UP key
			///</summary>
			PRIOR = 0x21,
			///<summary>
			///PAGE DOWN key
			///</summary>
			NEXT = 0x22,
			///<summary>
			///END key
			///</summary>
			END = 0x23,
			///<summary>
			///HOME key
			///</summary>
			HOME = 0x24,
			///<summary>
			///LEFT ARROW key
			///</summary>
			LEFT = 0x25,
			///<summary>
			///UP ARROW key
			///</summary>
			UP = 0x26,
			///<summary>
			///RIGHT ARROW key
			///</summary>
			RIGHT = 0x27,
			///<summary>
			///DOWN ARROW key
			///</summary>
			DOWN = 0x28,
			///<summary>
			///SELECT key
			///</summary>
			SELECT = 0x29,
			///<summary>
			///PRINT key
			///</summary>
			PRINT = 0x2A,
			///<summary>
			///EXECUTE key
			///</summary>
			EXECUTE = 0x2B,
			///<summary>
			///PRINT SCREEN key
			///</summary>
			SNAPSHOT = 0x2C,
			///<summary>
			///INS key
			///</summary>
			INSERT = 0x2D,
			///<summary>
			///DEL key
			///</summary>
			DELETE = 0x2E,
			///<summary>
			///HELP key
			///</summary>
			HELP = 0x2F,
			///<summary>
			///0 key
			///</summary>
			KEY_0 = 0x30,
			///<summary>
			///1 key
			///</summary>
			KEY_1 = 0x31,
			///<summary>
			///2 key
			///</summary>
			KEY_2 = 0x32,
			///<summary>
			///3 key
			///</summary>
			KEY_3 = 0x33,
			///<summary>
			///4 key
			///</summary>
			KEY_4 = 0x34,
			///<summary>
			///5 key
			///</summary>
			KEY_5 = 0x35,
			///<summary>
			///6 key
			///</summary>
			KEY_6 = 0x36,
			///<summary>
			///7 key
			///</summary>
			KEY_7 = 0x37,
			///<summary>
			///8 key
			///</summary>
			KEY_8 = 0x38,
			///<summary>
			///9 key
			///</summary>
			KEY_9 = 0x39,
			///<summary>
			///A key
			///</summary>
			KEY_A = 0x41,
			///<summary>
			///B key
			///</summary>
			KEY_B = 0x42,
			///<summary>
			///C key
			///</summary>
			KEY_C = 0x43,
			///<summary>
			///D key
			///</summary>
			KEY_D = 0x44,
			///<summary>
			///E key
			///</summary>
			KEY_E = 0x45,
			///<summary>
			///F key
			///</summary>
			KEY_F = 0x46,
			///<summary>
			///G key
			///</summary>
			KEY_G = 0x47,
			///<summary>
			///H key
			///</summary>
			KEY_H = 0x48,
			///<summary>
			///I key
			///</summary>
			KEY_I = 0x49,
			///<summary>
			///J key
			///</summary>
			KEY_J = 0x4A,
			///<summary>
			///K key
			///</summary>
			KEY_K = 0x4B,
			///<summary>
			///L key
			///</summary>
			KEY_L = 0x4C,
			///<summary>
			///M key
			///</summary>
			KEY_M = 0x4D,
			///<summary>
			///N key
			///</summary>
			KEY_N = 0x4E,
			///<summary>
			///O key
			///</summary>
			KEY_O = 0x4F,
			///<summary>
			///P key
			///</summary>
			KEY_P = 0x50,
			///<summary>
			///Q key
			///</summary>
			KEY_Q = 0x51,
			///<summary>
			///R key
			///</summary>
			KEY_R = 0x52,
			///<summary>
			///S key
			///</summary>
			KEY_S = 0x53,
			///<summary>
			///T key
			///</summary>
			KEY_T = 0x54,
			///<summary>
			///U key
			///</summary>
			KEY_U = 0x55,
			///<summary>
			///V key
			///</summary>
			KEY_V = 0x56,
			///<summary>
			///W key
			///</summary>
			KEY_W = 0x57,
			///<summary>
			///X key
			///</summary>
			KEY_X = 0x58,
			///<summary>
			///Y key
			///</summary>
			KEY_Y = 0x59,
			///<summary>
			///Z key
			///</summary>
			KEY_Z = 0x5A,
			///<summary>
			///Left Windows key (Microsoft Natural keyboard)
			///</summary>
			LWIN = 0x5B,
			///<summary>
			///Right Windows key (Natural keyboard)
			///</summary>
			RWIN = 0x5C,
			///<summary>
			///Applications key (Natural keyboard)
			///</summary>
			APPS = 0x5D,
			///<summary>
			///Computer Sleep key
			///</summary>
			SLEEP = 0x5F,
			///<summary>
			///Numeric keypad 0 key
			///</summary>
			NUMPAD0 = 0x60,
			///<summary>
			///Numeric keypad 1 key
			///</summary>
			NUMPAD1 = 0x61,
			///<summary>
			///Numeric keypad 2 key
			///</summary>
			NUMPAD2 = 0x62,
			///<summary>
			///Numeric keypad 3 key
			///</summary>
			NUMPAD3 = 0x63,
			///<summary>
			///Numeric keypad 4 key
			///</summary>
			NUMPAD4 = 0x64,
			///<summary>
			///Numeric keypad 5 key
			///</summary>
			NUMPAD5 = 0x65,
			///<summary>
			///Numeric keypad 6 key
			///</summary>
			NUMPAD6 = 0x66,
			///<summary>
			///Numeric keypad 7 key
			///</summary>
			NUMPAD7 = 0x67,
			///<summary>
			///Numeric keypad 8 key
			///</summary>
			NUMPAD8 = 0x68,
			///<summary>
			///Numeric keypad 9 key
			///</summary>
			NUMPAD9 = 0x69,
			///<summary>
			///Multiply key
			///</summary>
			MULTIPLY = 0x6A,
			///<summary>
			///Add key
			///</summary>
			ADD = 0x6B,
			///<summary>
			///Separator key
			///</summary>
			SEPARATOR = 0x6C,
			///<summary>
			///Subtract key
			///</summary>
			SUBTRACT = 0x6D,
			///<summary>
			///Decimal key
			///</summary>
			DECIMAL = 0x6E,
			///<summary>
			///Divide key
			///</summary>
			DIVIDE = 0x6F,
			///<summary>
			///F1 key
			///</summary>
			F1 = 0x70,
			///<summary>
			///F2 key
			///</summary>
			F2 = 0x71,
			///<summary>
			///F3 key
			///</summary>
			F3 = 0x72,
			///<summary>
			///F4 key
			///</summary>
			F4 = 0x73,
			///<summary>
			///F5 key
			///</summary>
			F5 = 0x74,
			///<summary>
			///F6 key
			///</summary>
			F6 = 0x75,
			///<summary>
			///F7 key
			///</summary>
			F7 = 0x76,
			///<summary>
			///F8 key
			///</summary>
			F8 = 0x77,
			///<summary>
			///F9 key
			///</summary>
			F9 = 0x78,
			///<summary>
			///F10 key
			///</summary>
			F10 = 0x79,
			///<summary>
			///F11 key
			///</summary>
			F11 = 0x7A,
			///<summary>
			///F12 key
			///</summary>
			F12 = 0x7B,
			///<summary>
			///F13 key
			///</summary>
			F13 = 0x7C,
			///<summary>
			///F14 key
			///</summary>
			F14 = 0x7D,
			///<summary>
			///F15 key
			///</summary>
			F15 = 0x7E,
			///<summary>
			///F16 key
			///</summary>
			F16 = 0x7F,
			///<summary>
			///F17 key  
			///</summary>
			F17 = 0x80,
			///<summary>
			///F18 key  
			///</summary>
			F18 = 0x81,
			///<summary>
			///F19 key  
			///</summary>
			F19 = 0x82,
			///<summary>
			///F20 key  
			///</summary>
			F20 = 0x83,
			///<summary>
			///F21 key  
			///</summary>
			F21 = 0x84,
			///<summary>
			///F22 key, (PPC only) Key used to lock device.
			///</summary>
			F22 = 0x85,
			///<summary>
			///F23 key  
			///</summary>
			F23 = 0x86,
			///<summary>
			///F24 key  
			///</summary>
			F24 = 0x87,
			///<summary>
			///NUM LOCK key
			///</summary>
			NUMLOCK = 0x90,
			///<summary>
			///SCROLL LOCK key
			///</summary>
			SCROLL = 0x91,
			///<summary>
			///Left SHIFT key
			///</summary>
			LSHIFT = 0xA0,
			///<summary>
			///Right SHIFT key
			///</summary>
			RSHIFT = 0xA1,
			///<summary>
			///Left CONTROL key
			///</summary>
			LCONTROL = 0xA2,
			///<summary>
			///Right CONTROL key
			///</summary>
			RCONTROL = 0xA3,
			///<summary>
			///Left MENU key
			///</summary>
			LMENU = 0xA4,
			///<summary>
			///Right MENU key
			///</summary>
			RMENU = 0xA5,
			///<summary>
			///Windows 2000/XP: Browser Back key
			///</summary>
			BROWSER_BACK = 0xA6,
			///<summary>
			///Windows 2000/XP: Browser Forward key
			///</summary>
			BROWSER_FORWARD = 0xA7,
			///<summary>
			///Windows 2000/XP: Browser Refresh key
			///</summary>
			BROWSER_REFRESH = 0xA8,
			///<summary>
			///Windows 2000/XP: Browser Stop key
			///</summary>
			BROWSER_STOP = 0xA9,
			///<summary>
			///Windows 2000/XP: Browser Search key
			///</summary>
			BROWSER_SEARCH = 0xAA,
			///<summary>
			///Windows 2000/XP: Browser Favorites key
			///</summary>
			BROWSER_FAVORITES = 0xAB,
			///<summary>
			///Windows 2000/XP: Browser Start and Home key
			///</summary>
			BROWSER_HOME = 0xAC,
			///<summary>
			///Windows 2000/XP: Volume Mute key
			///</summary>
			VOLUME_MUTE = 0xAD,
			///<summary>
			///Windows 2000/XP: Volume Down key
			///</summary>
			VOLUME_DOWN = 0xAE,
			///<summary>
			///Windows 2000/XP: Volume Up key
			///</summary>
			VOLUME_UP = 0xAF,
			///<summary>
			///Windows 2000/XP: Next Track key
			///</summary>
			MEDIA_NEXT_TRACK = 0xB0,
			///<summary>
			///Windows 2000/XP: Previous Track key
			///</summary>
			MEDIA_PREV_TRACK = 0xB1,
			///<summary>
			///Windows 2000/XP: Stop Media key
			///</summary>
			MEDIA_STOP = 0xB2,
			///<summary>
			///Windows 2000/XP: Play/Pause Media key
			///</summary>
			MEDIA_PLAY_PAUSE = 0xB3,
			///<summary>
			///Windows 2000/XP: Start Mail key
			///</summary>
			LAUNCH_MAIL = 0xB4,
			///<summary>
			///Windows 2000/XP: Select Media key
			///</summary>
			LAUNCH_MEDIA_SELECT = 0xB5,
			///<summary>
			///Windows 2000/XP: Start Application 1 key
			///</summary>
			LAUNCH_APP1 = 0xB6,
			///<summary>
			///Windows 2000/XP: Start Application 2 key
			///</summary>
			LAUNCH_APP2 = 0xB7,
			///<summary>
			///Used for miscellaneous characters; it can vary by keyboard.
			///</summary>
			OEM_1 = 0xBA,
			///<summary>
			///Windows 2000/XP: For any country/region, the '+' key
			///</summary>
			OEM_PLUS = 0xBB,
			///<summary>
			///Windows 2000/XP: For any country/region, the ',' key
			///</summary>
			OEM_COMMA = 0xBC,
			///<summary>
			///Windows 2000/XP: For any country/region, the '-' key
			///</summary>
			OEM_MINUS = 0xBD,
			///<summary>
			///Windows 2000/XP: For any country/region, the '.' key
			///</summary>
			OEM_PERIOD = 0xBE,
			///<summary>
			///Used for miscellaneous characters; it can vary by keyboard.
			///</summary>
			OEM_2 = 0xBF,
			///<summary>
			///Used for miscellaneous characters; it can vary by keyboard.
			///</summary>
			OEM_3 = 0xC0,
			///<summary>
			///Used for miscellaneous characters; it can vary by keyboard.
			///</summary>
			OEM_4 = 0xDB,
			///<summary>
			///Used for miscellaneous characters; it can vary by keyboard.
			///</summary>
			OEM_5 = 0xDC,
			///<summary>
			///Used for miscellaneous characters; it can vary by keyboard.
			///</summary>
			OEM_6 = 0xDD,
			///<summary>
			///Used for miscellaneous characters; it can vary by keyboard.
			///</summary>
			OEM_7 = 0xDE,
			///<summary>
			///Used for miscellaneous characters; it can vary by keyboard.
			///</summary>
			OEM_8 = 0xDF,
			///<summary>
			///Windows 2000/XP: Either the angle bracket key or the backslash key on the RT 102-key keyboard
			///</summary>
			OEM_102 = 0xE2,
			///<summary>
			///Windows 95/98/Me, Windows NT 4.0, Windows 2000/XP: IME PROCESS key
			///</summary>
			PROCESSKEY = 0xE5,
			///<summary>
			///Windows 2000/XP: Used to pass Unicode characters as if they were keystrokes. The VK_PACKET key is the low word of a 32-bit Virtual Key value used for non-keyboard input methods. For more information, see Remark in KEYBDINPUT, SendInput, WM_KEYDOWN, and WM_KEYUP
			///</summary>
			PACKET = 0xE7,
			///<summary>
			///Attn key
			///</summary>
			ATTN = 0xF6,
			///<summary>
			///CrSel key
			///</summary>
			CRSEL = 0xF7,
			///<summary>
			///ExSel key
			///</summary>
			EXSEL = 0xF8,
			///<summary>
			///Erase EOF key
			///</summary>
			EREOF = 0xF9,
			///<summary>
			///Play key
			///</summary>
			PLAY = 0xFA,
			///<summary>
			///Zoom key
			///</summary>
			ZOOM = 0xFB,
			///<summary>
			///Reserved
			///</summary>
			NONAME = 0xFC,
			///<summary>
			///PA1 key
			///</summary>
			PA1 = 0xFD,
			///<summary>
			///Clear key
			///</summary>
			OEM_CLEAR = 0xFE
		}

		// STRUCTS

		[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
		public struct POINT
		{
			public int x; // LONG
			public int y; // LONG
		}


		[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
		public struct MSG
		{
			public IntPtr hwnd; // HWND
			public uint message; // UINT
			public UIntPtr wParam; // WPARAM
			public IntPtr lParam; // LPARAM
			public uint time; // DWORD
			public POINT pt;
			public uint lPrivate; // DWORD
		}

		[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
		public struct WNDCLASSEX
		{
			[MarshalAs(UnmanagedType.U4)]
			public int cbSize;
			[MarshalAs(UnmanagedType.U4)]
			public int style;
			public IntPtr lpfnWndProc; // not WndProc
			public int cbClsExtra;
			public int cbWndExtra;
			public IntPtr hInstance;
			public IntPtr hIcon;
			public IntPtr hCursor;
			public IntPtr hbrBackground;
			public string lpszMenuName;
			public string lpszClassName;
			public IntPtr hIconSm;

			//Use this function to make a new one with cbSize already filled in.
			//For example:
			//var WndClss = WNDCLASSEX.Build()
			public static WNDCLASSEX Build()
			{
				var nw = new WNDCLASSEX
				{
					cbSize = Marshal.SizeOf(typeof(WNDCLASSEX))
				};
				return nw;
			}
		}

		[StructLayout(LayoutKind.Sequential)]
		public struct RECT
		{
			public int Left, Top, Right, Bottom;

			public RECT(int left, int top, int right, int bottom)
			{
				Left = left;
				Top = top;
				Right = right;
				Bottom = bottom;
			}

			public RECT(System.Drawing.Rectangle r) : this(r.Left, r.Top, r.Right, r.Bottom) { }

			public int X
			{
				get { return Left; }
				set { Right -= (Left - value); Left = value; }
			}

			public int Y
			{
				get { return Top; }
				set { Bottom -= (Top - value); Top = value; }
			}

			public int Height
			{
				get { return Bottom - Top; }
				set { Bottom = value + Top; }
			}

			public int Width
			{
				get { return Right - Left; }
				set { Right = value + Left; }
			}

			public System.Drawing.Point Location
			{
				get { return new System.Drawing.Point(Left, Top); }
				set { X = value.X; Y = value.Y; }
			}

			public System.Drawing.Size Size
			{
				get { return new System.Drawing.Size(Width, Height); }
				set { Width = value.Width; Height = value.Height; }
			}

			public static implicit operator System.Drawing.Rectangle(RECT r)
			{
				return new System.Drawing.Rectangle(r.Left, r.Top, r.Width, r.Height);
			}

			public static implicit operator RECT(System.Drawing.Rectangle r)
			{
				return new RECT(r);
			}

			public static bool operator ==(RECT r1, RECT r2)
			{
				return r1.Equals(r2);
			}

			public static bool operator !=(RECT r1, RECT r2)
			{
				return !r1.Equals(r2);
			}

			public bool Equals(RECT r)
			{
				return r.Left == Left && r.Top == Top && r.Right == Right && r.Bottom == Bottom;
			}

			public override bool Equals(object obj)
			{
				if (obj is RECT)
					return Equals((RECT)obj);
				else if (obj is System.Drawing.Rectangle)
					return Equals(new RECT((System.Drawing.Rectangle)obj));
				return false;
			}

			public override int GetHashCode()
			{
				return ((System.Drawing.Rectangle)this).GetHashCode();
			}

			public override string ToString()
			{
				return string.Format(System.Globalization.CultureInfo.CurrentCulture, "{{Left={0},Top={1},Right={2},Bottom={3}}}", Left, Top, Right, Bottom);
			}
		}

		[StructLayout(LayoutKind.Sequential)]
		public struct PAINTSTRUCT
		{
			public IntPtr hdc;
			public bool fErase;
			public RECT rcPaint;
			public bool fRestore;
			public bool fIncUpdate;
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)] public byte[] rgbReserved;
		}

		[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
		public struct MonitorInfoEx
		{
			/// <summary>
			/// The size, in bytes, of the structure. Set this member to sizeof(MONITORINFOEX) (72) before calling the GetMonitorInfo function.
			/// Doing so lets the function determine the type of structure you are passing to it.
			/// </summary>
			public int Size;

			/// <summary>
			/// A RECT structure that specifies the display monitor rectangle, expressed in virtual-screen coordinates.
			/// Note that if the monitor is not the primary display monitor, some of the rectangle's coordinates may be negative values.
			/// </summary>
			public RectStruct Monitor;

			/// <summary>
			/// A RECT structure that specifies the work area rectangle of the display monitor that can be used by applications,
			/// expressed in virtual-screen coordinates. Windows uses this rectangle to maximize an application on the monitor.
			/// The rest of the area in rcMonitor contains system windows such as the task bar and side bars.
			/// Note that if the monitor is not the primary display monitor, some of the rectangle's coordinates may be negative values.
			/// </summary>
			public RectStruct WorkArea;

			/// <summary>
			/// The attributes of the display monitor.
			///
			/// This member can be the following value:
			///   1 : MONITORINFOF_PRIMARY
			/// </summary>
			public uint Flags;

			/// <summary>
			/// A string that specifies the device name of the monitor being used. Most applications have no use for a display monitor name,
			/// and so can save some bytes by using a MONITORINFO structure.
			/// </summary>
			[MarshalAs(UnmanagedType.ByValTStr, SizeConst = CCHDEVICENAME)]
			public string DeviceName;

			public void Init()
			{
				this.Size = 40 + 2 * CCHDEVICENAME;
				this.DeviceName = string.Empty;
			}
		}

		/// <summary>
		/// The RECT structure defines the coordinates of the upper-left and lower-right corners of a rectangle.
		/// </summary>
		/// <see cref="http://msdn.microsoft.com/en-us/library/dd162897%28VS.85%29.aspx"/>
		/// <remarks>
		/// By convention, the right and bottom edges of the rectangle are normally considered exclusive.
		/// In other words, the pixel whose coordinates are ( right, bottom ) lies immediately outside of the the rectangle.
		/// For example, when RECT is passed to the FillRect function, the rectangle is filled up to, but not including,
		/// the right column and bottom row of pixels. This structure is identical to the RECTL structure.
		/// </remarks>
		[StructLayout(LayoutKind.Sequential)]
		public struct RectStruct
		{
			/// <summary>
			/// The x-coordinate of the upper-left corner of the rectangle.
			/// </summary>
			public int Left;

			/// <summary>
			/// The y-coordinate of the upper-left corner of the rectangle.
			/// </summary>
			public int Top;

			/// <summary>
			/// The x-coordinate of the lower-right corner of the rectangle.
			/// </summary>
			public int Right;

			/// <summary>
			/// The y-coordinate of the lower-right corner of the rectangle.
			/// </summary>
			public int Bottom;
		}

		// APIS USER32

		[DllImport("user32.dll", SetLastError = true)]
		public static extern bool GetMessage(
			out MSG lpMsg,  // LPMSG
			IntPtr hWnd,
			uint wMsgFilterMin,
			uint wMsgFilterMax
		);

		[DllImport("user32.dll", SetLastError = true)]
		public static extern bool PeekMessageA(
			out MSG lpMsg,  // LPMSG
			IntPtr hWnd,
			uint wMsgFilterMin,
			uint wMsgFilterMax,
			uint wRemoveMsg
			);

		[DllImport("user32.dll", SetLastError = true)]
		public static extern bool TranslateMessage(
			ref MSG lpMsg  // LPMSG
			);

		[DllImport("user32.dll", SetLastError = true)]
		public static extern IntPtr DispatchMessage( // LRESULT
			ref MSG lpMsg  // LPMSG
			);

		[DllImport("user32.dll", SetLastError = true)]
		public static extern IntPtr LoadIcon(IntPtr hInstance, IntPtr lpIconName);

		[DllImport("user32.dll")]
		public static extern IntPtr LoadCursor(IntPtr hInstance, int lpCursorName);

		[DllImport("user32.dll")]
		[return: MarshalAs(UnmanagedType.U2)]
		public static extern ushort RegisterClassEx([In] ref WNDCLASSEX lpwcx);

		[DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
		public static extern int MessageBox(IntPtr hWnd, string text, string caption, uint type);

		[DllImport("user32.dll", SetLastError = true)]
		public static extern IntPtr CreateWindowEx(
			uint dwExStyle,
			ushort lpClassName,
			//[MarshalAs(UnmanagedType.LPStr)] string lpClassName,
			[MarshalAs(UnmanagedType.LPStr)] string lpWindowName,
			uint dwStyle,
			int x,
			int y,
			int nWidth,
			int nHeight,
			IntPtr hWndParent,
			IntPtr hMenu,
			IntPtr hInstance,
			IntPtr lpParam);

		[DllImport("user32.dll")]
		public static extern IntPtr BeginPaint(IntPtr hwnd, out PAINTSTRUCT lpPaint);

		[DllImport("user32.dll")]
		public static extern bool EndPaint(IntPtr hWnd, [In] ref PAINTSTRUCT lpPaint);

		[DllImport("user32.dll")]
		public static extern void PostQuitMessage(int nExitCode);

		[DllImport("user32.dll")]
		public static extern IntPtr DefWindowProc(IntPtr hWnd, WindowsMessages uMsg, IntPtr wParam, IntPtr lParam);

		[DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
		public static extern bool SetWindowText(IntPtr hwnd, String lpString);

		[DllImport("user32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
		[return: MarshalAs(UnmanagedType.Bool)]
		public static extern bool DestroyWindow(IntPtr hwnd);

		[return: MarshalAs(UnmanagedType.Bool)]
		[DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
		public static extern bool PostMessage(IntPtr hWnd, WindowsMessages uMsg, IntPtr wParam, IntPtr lParam);

		[DllImport("user32.dll")]
		public static extern IntPtr MonitorFromWindow(IntPtr hwnd, uint dwFlags);

		[DllImport("user32.dll", CharSet = CharSet.Auto)]
		public static extern bool GetMonitorInfo(IntPtr hMonitor, ref MonitorInfoEx lpmi);

		[DllImport("user32.dll")]
		public static extern bool AdjustWindowRectEx(ref RECT lpRect, uint dwStyle, bool bMenu, uint dwExStyle);

		[DllImport("user32.dll", EntryPoint = "GetWindowLong")]
		public static extern IntPtr GetWindowLongPtr(IntPtr hWnd, int nIndex);

		// This helper static method is required because the 32-bit version of user32.dll does not contain this API
		// (on any versions of Windows), so linking the method will fail at run-time. The bridge dispatches the request
		// to the correct function (GetWindowLong in 32-bit mode and GetWindowLongPtr in 64-bit mode)
		public static IntPtr SetWindowLongPtr(IntPtr hWnd, int nIndex, IntPtr dwNewLong)
		{
			if (IntPtr.Size == 8)
				return SetWindowLongPtr64(hWnd, nIndex, dwNewLong);
			else
				return new IntPtr(SetWindowLong32(hWnd, nIndex, dwNewLong.ToInt32()));
		}

		[DllImport("user32.dll", EntryPoint = "SetWindowLong")]
		private static extern int SetWindowLong32(IntPtr hWnd, int nIndex, int dwNewLong);

		[DllImport("user32.dll", EntryPoint = "SetWindowLongPtr")]
		private static extern IntPtr SetWindowLongPtr64(IntPtr hWnd, int nIndex, IntPtr dwNewLong);

		[DllImport("user32.dll", EntryPoint = "FindWindow", SetLastError = true)]
		public static extern IntPtr FindWindowByCaption(IntPtr ZeroOnly, string lpWindowName);

		[DllImport("user32.dll", SetLastError = true)]
		public static extern bool GetWindowRect(IntPtr hwnd, out RECT lpRect);

		// APIS GDI32
		[DllImport("gdi32.dll", CharSet = CharSet.Auto)]
		public static extern bool TextOut(IntPtr hdc, int nXStart, int nYStart, string lpString, int cbString);
	}
}
