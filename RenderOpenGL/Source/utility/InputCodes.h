// ReSharper disable CppClangTidyClangDiagnosticUnusedMacros
#pragma once


namespace KREngine
{
#pragma once
	namespace Input
	{
		typedef enum class KeyCodes: size_t
		{
			// From glfw3.h
			Space = 32,
			Apostrophe = 39, /* ' */
			Comma = 44, /* , */
			Minus = 45, /* - */
			Period = 46, /* . */
			Slash = 47, /* / */

			D0 = 48, /* 0 */
			D1 = 49, /* 1 */
			D2 = 50, /* 2 */
			D3 = 51, /* 3 */
			D4 = 52, /* 4 */
			D5 = 53, /* 5 */
			D6 = 54, /* 6 */
			D7 = 55, /* 7 */
			D8 = 56, /* 8 */
			D9 = 57, /* 9 */

			Semicolon = 59, /* ; */
			Equal = 61, /* = */

			A = 65,
			B = 66,
			C = 67,
			D = 68,
			E = 69,
			F = 70,
			G = 71,
			H = 72,
			I = 73,
			J = 74,
			K = 75,
			L = 76,
			M = 77,
			N = 78,
			O = 79,
			P = 80,
			Q = 81,
			R = 82,
			S = 83,
			T = 84,
			U = 85,
			V = 86,
			W = 87,
			X = 88,
			Y = 89,
			Z = 90,

			LeftBracket = 91,  /* [ */
			Backslash = 92,  /* \ */
			RightBracket = 93,  /* ] */
			GraveAccent = 96,  /* ` */

			World1 = 161, /* non-US #1 */
			World2 = 162, /* non-US #2 */

			/* Function keys */
			Escape = 256,
			Enter = 257,
			Tab = 258,
			Backspace = 259,
			Insert = 260,
			Delete = 261,
			Right = 262,
			Left = 263,
			Down = 264,
			Up = 265,
			PageUp = 266,
			PageDown = 267,
			Home = 268,
			End = 269,
			CapsLock = 280,
			ScrollLock = 281,
			NumLock = 282,
			PrintScreen = 283,
			Pause = 284,
			F1 = 290,
			F2 = 291,
			F3 = 292,
			F4 = 293,
			F5 = 294,
			F6 = 295,
			F7 = 296,
			F8 = 297,
			F9 = 298,
			F10 = 299,
			F11 = 300,
			F12 = 301,
			F13 = 302,
			F14 = 303,
			F15 = 304,
			F16 = 305,
			F17 = 306,
			F18 = 307,
			F19 = 308,
			F20 = 309,
			F21 = 310,
			F22 = 311,
			F23 = 312,
			F24 = 313,
			F25 = 314,

			/* Keypad */
			KP0 = 320,
			KP1 = 321,
			KP2 = 322,
			KP3 = 323,
			KP4 = 324,
			KP5 = 325,
			KP6 = 326,
			KP7 = 327,
			KP8 = 328,
			KP9 = 329,
			KPDecimal = 330,
			KPDivide = 331,
			KPMultiply = 332,
			KPSubtract = 333,
			KPAdd = 334,
			KPEnter = 335,
			KPEqual = 336,

			LeftShift = 340,
			LeftControl = 341,
			LeftAlt = 342,
			LeftSuper = 343,
			RightShift = 344,
			RightControl = 345,
			RightAlt = 346,
			RightSuper = 347,
			Menu = 348,
			Count = 349
		} Key;


		//FROM glfw3.h
		typedef enum class MouseCode
		{
			Button1 = 0,
			Button2 = 1,
			Button3 = 2,
			Button4 = 3,
			Button5 = 4,
			Button6 = 5,
			Button7 = 6,
			Button8 = 7,
			ButtonLeft = Button1,
			ButtonLast = Button8,
			ButtonRight = Button2,
			ButtonMiddle = Button3,
			Count = 12


		}Mouse;
	}
}


//from GLFW.h

//KR KEYCODES.


/* Printable keys */
#define KR_KEY_SPACE              32
#define KR_KEY_APOSTROPHE         39  /* ' */
#define KR_KEY_COMMA              44  /* , */
#define KR_KEY_MINUS              45  /* - */
#define KR_KEY_PERIOD             46  /* . */
#define KR_KEY_SLASH              47  /* / */
#define KR_KEY_0                  48
#define KR_KEY_1                  49
#define KR_KEY_2                  50
#define KR_KEY_3                  51
#define KR_KEY_4                  52
#define KR_KEY_5                  53
#define KR_KEY_6                  54
#define KR_KEY_7                  55
#define KR_KEY_8                  56
#define KR_KEY_9                  57
#define KR_KEY_SEMICOLON          59  /* ; */
#define KR_KEY_EQUAL              61  /* = */
#define KR_KEY_A                  65
#define KR_KEY_B                  66
#define KR_KEY_C                  67
#define KR_KEY_D                  68
#define KR_KEY_E                  69
#define KR_KEY_F                  70
#define KR_KEY_G                  71
#define KR_KEY_H                  72
#define KR_KEY_I                  73
#define KR_KEY_J                  74
#define KR_KEY_K                  75
#define KR_KEY_L                  76
#define KR_KEY_M                  77
#define KR_KEY_N                  78
#define KR_KEY_O                  79
#define KR_KEY_P                  80
#define KR_KEY_Q                  81
#define KR_KEY_R                  82
#define KR_KEY_S                  83
#define KR_KEY_T                  84
#define KR_KEY_U                  85
#define KR_KEY_V                  86
#define KR_KEY_W                  87
#define KR_KEY_X                  88
#define KR_KEY_Y                  89
#define KR_KEY_Z                  90
#define KR_KEY_LEFT_BRACKET       91  /* [ */
#define KR_KEY_BACKSLASH          92  /* \ */
#define KR_KEY_RIGHT_BRACKET      93  /* ] */
#define KR_KEY_GRAVE_ACCENT       96  /* ` */
#define KR_KEY_WORLD_1            161 /* non-US #1 */
#define KR_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define KR_KEY_ESCAPE             256
#define KR_KEY_ENTER              257
#define KR_KEY_TAB                258
#define KR_KEY_BACKSPACE          259
#define KR_KEY_INSERT             260
#define KR_KEY_DELETE             261
#define KR_KEY_RIGHT              262
#define KR_KEY_LEFT               263
#define KR_KEY_DOWN               264
#define KR_KEY_UP                 265
#define KR_KEY_PAGE_UP            266
#define KR_KEY_PAGE_DOWN          267
#define KR_KEY_HOME               268
#define KR_KEY_END                269
#define KR_KEY_CAPS_LOCK          280
#define KR_KEY_SCROLL_LOCK        281
#define KR_KEY_NUM_LOCK           282
#define KR_KEY_PRINT_SCREEN       283
#define KR_KEY_PAUSE              284
#define KR_KEY_F1                 290
#define KR_KEY_F2                 291
#define KR_KEY_F3                 292
#define KR_KEY_F4                 293
#define KR_KEY_F5                 294
#define KR_KEY_F6                 295
#define KR_KEY_F7                 296
#define KR_KEY_F8                 297
#define KR_KEY_F9                 298
#define KR_KEY_F10                299
#define KR_KEY_F11                300
#define KR_KEY_F12                301
#define KR_KEY_F13                302
#define KR_KEY_F14                303
#define KR_KEY_F15                304
#define KR_KEY_F16                305
#define KR_KEY_F17                306
#define KR_KEY_F18                307
#define KR_KEY_F19                308
#define KR_KEY_F20                309
#define KR_KEY_F21                310
#define KR_KEY_F22                311
#define KR_KEY_F23                312
#define KR_KEY_F24                313
#define KR_KEY_F25                314
#define KR_KEY_KP_0               320
#define KR_KEY_KP_1               321
#define KR_KEY_KP_2               322
#define KR_KEY_KP_3               323
#define KR_KEY_KP_4               324
#define KR_KEY_KP_5               325
#define KR_KEY_KP_6               326
#define KR_KEY_KP_7               327
#define KR_KEY_KP_8               328
#define KR_KEY_KP_9               329
#define KR_KEY_KP_DECIMAL         330
#define KR_KEY_KP_DIVIDE          331
#define KR_KEY_KP_MULTIPLY        332
#define KR_KEY_KP_SUBTRACT        333
#define KR_KEY_KP_ADD             334
#define KR_KEY_KP_ENTER           335
#define KR_KEY_KP_EQUAL           336
#define KR_KEY_LEFT_SHIFT         340
#define KR_KEY_LEFT_CONTROL       341
#define KR_KEY_LEFT_ALT           342
#define KR_KEY_LEFT_SUPER         343
#define KR_KEY_RIGHT_SHIFT        344
#define KR_KEY_RIGHT_CONTROL      345
#define KR_KEY_RIGHT_ALT          346
#define KR_KEY_RIGHT_SUPER        347
#define KR_KEY_MENU               348

















#define KR_MOUSE_BUTTON_1      0,
#define KR_MOUSE_BUTTON_2      1,
#define KR_MOUSE_BUTTON_3      2,
#define KR_MOUSE_BUTTON_4      3,
#define KR_MOUSE_BUTTON_5      4,
#define KR_MOUSE_BUTTON_6      5,
#define KR_MOUSE_BUTTON_7      6,
#define KR_MOUSE_BUTTON_8      7,
#define KR_MOUSE_BUTTON_LAST   KR_MOUSE_BUTTON_8
#define KR_MOUSE_BUTTON_LEFT   KR_MOUSE_BUTTON_1
#define KR_MOUSE_BUTTON_RIGHT  KR_MOUSE_BUTTON_2
#define KR_MOUSE_BUTTON_MIDDLE KR_MOUSE_BUTTON_3

