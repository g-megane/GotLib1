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
        
    }
    
    void Font::drawEnd()
    {
        spRenderTarget->EndDraw();
    }
}