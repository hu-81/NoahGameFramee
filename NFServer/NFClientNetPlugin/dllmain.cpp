// dllmain.cpp : Defines the entry point for the DLL application.
//#include "stdafx.h"
#include "NFComm/NFCore/NFPlatform.h"

#if NF_PLATFORM == NF_PLATFORM_WIN32

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

#endif


#ifdef _DEBUG

#if NF_PLATFORM == NF_PLATFORM_WIN32
#pragma comment( lib, "ws2_32" )
#pragma comment( lib, "RakNet_LibStatic_Debug_Win32.lib" )
#pragma comment( lib, "NFNet_d.lib" )
#pragma comment( lib, "NFCore_d.lib" )
#pragma comment( lib, "NFMessageDefine_d.lib" )
#elif NF_PLATFORM == NF_PLATFORM_LINUX || NF_PLATFORM == NF_PLATFORM_ANDROID
#pragma comment( lib, "RakNet_LibStatic_Debug_Win32.a" )
#pragma comment( lib, "NFNet_d.a" )
#pragma comment( lib, "NFCore_d.a" )
#pragma comment( lib, "NFMessageDefine_d.a" )
#elif NF_PLATFORM == NF_PLATFORM_APPLE || NF_PLATFORM == NF_PLATFORM_APPLE_IOS
#endif

#else

#if NF_PLATFORM == NF_PLATFORM_WIN32
#pragma comment( lib, "ws2_32" )
#pragma comment( lib, "RakNet_LibStatic_Release_Win32.lib" )
#pragma comment( lib, "NFNet.lib" )
#pragma comment( lib, "NFCore.lib" )
#pragma comment( lib, "NFMessageDefine.lib" )
#elif NF_PLATFORM == NF_PLATFORM_LINUX || NF_PLATFORM == NF_PLATFORM_ANDROID
#pragma comment( lib, "RakNet_LibStatic_Release_Win32.a" )
#pragma comment( lib, "NFNet.a" )
#pragma comment( lib, "NFCore.a" )
#pragma comment( lib, "NFMessageDefine.a" )
#elif NF_PLATFORM == NF_PLATFORM_APPLE || NF_PLATFORM == NF_PLATFORM_APPLE_IOS
#endif

#endif