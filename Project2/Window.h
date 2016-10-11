//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/9/27
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include<Windows.h>
#include<memory>
#include"Texture.h"
#include"Dimention.h"

// ウィンドウ生成クラス
namespace got
{
	class Window
	{
	public:
		Window(const LPCWCHAR _windowName);
		~Window();

		MSG Update();
		HWND getHWND() const;
		Dimention<int> getWindowSize() const;

	private:
		HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
		static LRESULT CALLBACK WndProck(HWND _hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		int Initialize();

		LPCWCHAR windowName;
		HWND hWnd;
		Dimention<int> windowSize;
		std::shared_ptr<Texture> texture;
	};
}