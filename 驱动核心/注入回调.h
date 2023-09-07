#pragma once

extern INJECT_DATA InjectData;

extern INJECT_CACHE InjectCache;

extern PHOOK_NOTIFY_BUFFER pInjectNotifyHookBuffer;

auto SetPhysicalPage(UINT64, SIZE_T, BOOL, BOOL)->BOOLEAN;

auto ValidInjectEx(PUNICODE_STRING, UINT32, LPWSTR)->BOOLEAN;

auto ValidHashName(UINT32, PUNICODE_STRING)->BOOLEAN;

auto GetProcFun_x86(PBYTE, LPCTSTR)->UINT32;

auto GetProcFun_x64(PBYTE, LPCTSTR)->UINT64;

auto GetMapSize_x86(PBYTE)->ULONG;

auto GetMapSize_x64(PBYTE)->ULONG;

auto AllocMemory_x86(PSIZE_T, ULONG)->PBYTE;

auto AllocMemory_x64(PSIZE_T, ULONG)->PBYTE;

auto StartInject_x86(PUNICODE_STRING, HANDLE, PIMAGE_INFO)->NTSTATUS;

auto StartInject_x64(PUNICODE_STRING, HANDLE, PIMAGE_INFO)->NTSTATUS;

auto InjectNotifyInit(ULONG)->NTSTATUS;