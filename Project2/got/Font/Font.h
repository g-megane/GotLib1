#pragma once
#include <dxgi1_2.h>
#include <d2d1_1.h>
#include <dwrite_1.h>
#include "../DirectX/DirectX11.h"
#include "../Utility/Singleton.h"
#include "../Math/Vector2.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

namespace got
{
    class Font : public Singleton<Font>
    {
    public:
        ~Font();
        HRESULT init();
        void setFont();
        void draw(const WCHAR *drawStr_);
        void drawBegine();
        void drawEnd();

    private:
        friend class Singleton<Font>;
        Font();
        
        std::shared_ptr<ID2D1RenderTarget> spRenderTarget;
    };
}