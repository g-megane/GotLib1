//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/9/27
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <memory>
#include "..\..\got\Utility\Texture.h"
#include "..\..\got\Utility\Dimention.h"

// ウィンドウ生成クラス
namespace got
{
	class Window
	{
	public:
		Window(const LPCSTR _windowName);
		~Window();

		MSG Update();
		HWND getHWND() const;
		Dimention<int> getWindowSize() const;

	private:
		HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
		static LRESULT CALLBACK WndProck(HWND _hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		int Initialize();

		LPCSTR windowName;
		HWND hWnd;
		Dimention<int> windowSize;
		std::shared_ptr<Texture> texture;
	};
}