#include "AppDelegate.h"
#include "cocos2d.h"


#ifndef __MAIN_H__
#define __MAIN_H__

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

 // Windows Header Files:
#include <windows.h>
#include <tchar.h>

// C RunTime Header Files
#include "platform/CCStdC.h"

#endif    // __MAIN_H__

USING_NS_CC;

int WINAPI _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}
