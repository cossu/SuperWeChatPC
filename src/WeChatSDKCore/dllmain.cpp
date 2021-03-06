// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi")
#include "dllhijack.h"
#include "hook.h"
#include "config.h"

#include "sdk.h"

WxFuncConfig g_WxFuncConfig;

VOID DllHijack(HMODULE hMod)
{
	TCHAR tszDllPath[MAX_PATH] = { 0 };

	GetModuleFileName(hMod, tszDllPath, MAX_PATH);
	PathRemoveFileSpec(tszDllPath);
	PathAppend(tszDllPath, TEXT("WeChatResource.dll.1"));

	SuperDllHijack(L"WeChatResource.dll", tszDllPath);
}

VOID Init()
{
    /*if (g_WxFuncConfig.IsRevokeMsg()) {
        FakeRevokeMsg();
    }*/
    InitHook();

    InitSDK();
}

VOID Uninit()
{
    UnInitSDK();

    UninitHook();
    /*if (g_WxFuncConfig.IsRevokeMsg()) {
        RestoreRevokeMsg();
    }*/
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		//DllHijack(hModule);
        Init();
		break;
    case DLL_PROCESS_DETACH:
        Uninit();
        break;
    default:
        break;
    }
    return TRUE;
}

