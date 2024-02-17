#include "Libs.h"
#include "MyException.h"
#include "App.h"



int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
)
{
    try {
        return App{}.Go();
    }
    catch (MyException e) {
        MessageBoxA(nullptr, e.GetMessage().c_str(), "Error", MB_OK);
    }
   
    

}