#include "Font.h"

template<typename Ptr>
void safeRelease(Ptr *& ptr)
{
    if (ptr == nullptr) return;
    ptr->Release();
    ptr = nullptr;
}

namespace got
{
    Font::Font()
    {
        
    }

    Font::~Font()
    {
     
    }

    HRESULT Font::init()
    {
        //ID3D11Texture2D *backBuffer;
        //ID3D11RenderTargetView *backBufferView;
        //DirectX11::getInstance().getSwapChain()->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
        //DirectX11::getInstance().getDevice()->CreateRenderTargetView(backBuffer, nullptr, &backBufferView);
        //DirectX11::getInstance().getDeviceContext()->OMSetRenderTargets(1, &backBufferView, nullptr);

        // create the D2D factory
        ID2D1Factory *factory;
        D2D1_FACTORY_OPTIONS options;
        options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
        D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, options, &factory);

        // set up the D2D render target using the back buffer
        IDXGISurface *dxgiBackbuffer;
        DirectX11::getInstance().getSwapChain()->GetBuffer(0, IID_PPV_ARGS(&dxgiBackbuffer));
        ID2D1RenderTarget *d2dRenderTarget;
        D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
            D2D1_RENDER_TARGET_TYPE_DEFAULT,
            D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));
        factory->CreateDxgiSurfaceRenderTarget(dxgiBackbuffer, props, &d2dRenderTarget);
        dxgiBackbuffer->Release();

        // create the DWrite factory
       /* IDWriteFactory1 *writeFactory;
        DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(writeFactory), (IUnknown**)(&writeFactory));
*/
        // create the DRwite text format
        /*IDWriteTextFormat *textFormat;
        writeFactory->CreateTextFormat(
            L"Arial",
            NULL,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            50,
            L"",
            &textFormat);*/

        // create a brush
        //ID2D1SolidColorBrush *whiteBrush;
        //d2dRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &whiteBrush);

        spRenderTarget = std::shared_ptr<ID2D1RenderTarget>(d2dRenderTarget, safeRelease<ID2D1RenderTarget>);

        return S_OK;
    }

    void Font::setFont()
    {
        
    }

    void Font::drawBegine()
    {
      spRenderTarget->BeginDraw();
    }
    
    void Font::draw(const WCHAR* drawStr)
    {
        IDWriteFactory1 *writeFactory;
        DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(writeFactory), (IUnknown**)(&writeFactory));


        IDWriteTextFormat *textFormat;
        writeFactory->CreateTextFormat(
            L"Arial",
            NULL,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            50,
            L"",
            &textFormat);

        ID2D1SolidColorBrush *whiteBrush;
        spRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &whiteBrush);

        spRenderTarget->DrawTextA(drawStr, wcslen(drawStr), textFormat, D2D1::RectF(0, 0, 800, 600), whiteBrush);
    }
    
    void Font::drawEnd()
    {
        spRenderTarget->EndDraw();
    }
}