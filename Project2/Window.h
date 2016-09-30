//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/9/27
// 制作者:Got
//////////////////////////////////////////////////
#pragma once
#include<Windows.h>
#include<memory>
#include"Texture.h"

// ウィンドウ生成クラス
namespace Got
{
	class Window
	{
	public:
		Window(const LPCWCHAR _windowName);
		~Window();

		int Update();
		HWND getHWND() const;

	private:
		HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
		static LRESULT CALLBACK WndProck(HWND _hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		int Initialize();

		LPCWCHAR windowName;
		HWND hWnd;
		std::shared_ptr<Texture> texture;
	};
}