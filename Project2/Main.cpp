//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/9/27
// 制作者:Got
//////////////////////////////////////////////////
#include"Window.h"
#include"DirectX11.h"

// メイン関数
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	std::shared_ptr<Got::Window> window;
	window = std::make_shared<Got::Window>(L"GotLib");

	Got::DirectX11::getInstance().initialize(window);

	window->Update();

	return 0;
}