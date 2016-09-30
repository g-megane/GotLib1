//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/9/27
// 制作者:Got
//////////////////////////////////////////////////
#include"Window.h"
#include"DirectX11.h"
#include"GV.h"

namespace Got
{
	// コンストラクタ
	Window::Window(const LPCWCHAR _windowName)
		:windowName(_windowName)
	{
		Initialize();
	}
	// デストラクタ
	Window::~Window()
	{
	}
	// 初期化
	int Window::Initialize()
	{
		windowSize = Dimention<int>(static_cast<int>(WINDOW_WIDTH), static_cast<int>(WINDOW_HEIGHT));
		texture = std::make_shared<Texture>();
		auto hInstance = GetModuleHandle(NULL);
		auto nCmdShow = SW_SHOWNORMAL;

		if (FAILED(InitWindow(hInstance, nCmdShow))) {
			return 0;
		}

		return 0;
	}
	// hWndの取得
	HWND Window::getHWND() const
	{
		return hWnd;
	}
	Dimention<int> Window::getWindowSize() const
	{
		return windowSize;
	}
	// ウィンドウの初期化
	HRESULT Window::InitWindow(HINSTANCE hInstance, int nCmdShow)
	{
		WNDCLASSEX wcex;
		wcex.cbSize		   = sizeof(WNDCLASSEX);						 // 構造体のサイズ
		wcex.style		   = CS_HREDRAW | CS_VREDRAW;					 // ウィンドウスタイル
		wcex.lpfnWndProc   = WndProck;									 // ウィンドウプロシージャ
		wcex.cbClsExtra	   = 0;											 // ウィンドウクラスに付加したいメモリ
		wcex.cbWndExtra	   = 0;											 // ウィンドウに付加したいメモリ
		wcex.hInstance	   = hInstance;									 // インスタンスハンドル
		wcex.hIcon		   = NULL;										 // アイコン
		wcex.hCursor	   = NULL;										 // カーソル
		wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1); // 背景色
		wcex.lpszMenuName  = L"GotLib";									 // メニュー
		wcex.lpszClassName = windowName;								 // ウィンドウクラスの名前
		wcex.hIconSm	   = NULL;										 // アイコン小
		if (!RegisterClassEx(&wcex)) {
			return E_FAIL;
		}

		// ウィンドウの作成
		RECT rect = { 0, 0, static_cast<LONG>(WINDOW_WIDTH), static_cast<LONG>(WINDOW_HEIGHT) };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
		hWnd = CreateWindow(
			L"GotLib",				// ウィンドウクラス名
			L"GotLib",				// ウィンドウタイトル
			WS_OVERLAPPEDWINDOW,	// ウィンドウスタイル
			CW_USEDEFAULT,			// Y座標の初期値
			CW_USEDEFAULT,			// X座標の初期値
			rect.right - rect.left, // 幅の初期値
			rect.bottom - rect.top, // 高さの初期値
			NULL,					// 親ウィンドウのハンドル
			NULL,					// ウィンドウメニュー
			hInstance,				// インスタンスハンドル
			NULL);					// 作成パラメータ
		if (!hWnd) {
			return E_FAIL;
		}

		ShowWindow(hWnd, nCmdShow);

		return S_OK;
	}
	// ウィンドウプロシージャ
	LRESULT Window::WndProck(HWND _hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		PAINTSTRUCT ps;
		HDC hdc;

		switch (message)
		{
		case WM_PAINT:
			hdc = BeginPaint(_hWnd, &ps);
			EndPaint(_hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(_hWnd, message, wParam, lParam);
		}

		return 0;
	}
	// アップデート
	int Window::Update()
	{
		MSG msg = { 0 };
		texture->create(L"plane.png");

		while (WM_QUIT != msg.message) {
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				DirectX11::getInstance().begineFrame();

				texture->render();

				DirectX11::getInstance().endFrame();
			}
		}

		return static_cast<int>(msg.wParam);
	}
}