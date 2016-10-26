//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/9/27
// 制作者:got
//////////////////////////////////////////////////
#include<memory>
#include"Game.h"
#include"DirectX11.h"

// メイン関数
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	auto & game = Game::getInstance();

	game.init();

	game.update();

	game.end();

	return 0;
}