#pragma once

auto PsGetProcessImageFileName(PEPROCESS)->LPSTR;

auto PsGetProcessSectionBaseAddress(PEPROCESS)->LPVOID;

auto ZwQuerySystemInformation(ULONG, LPVOID, ULONG, PULONG)->NTSTATUS;

auto ZwQueryInformationProcess(HANDLE, PROCESSINFOCLASS, LPVOID, ULONG, PULONG)->NTSTATUS;

auto ZwSetInformationProcess(HANDLE, PROCESSINFOCLASS, LPVOID, ULONG)->NTSTATUS;

auto ZwReferenceObjectByName(PUNICODE_STRING, ULONG, PACCESS_STATE, ACCESS_MASK, POBJECT_TYPE, KPROCESSOR_MODE, LPVOID, PDRIVER_OBJECT*)->NTSTATUS;

auto ZwGetProcessIdForHash(UINT32, PHANDLE)->NTSTATUS;

auto ZwGetProcessFullName(HANDLE, PUNICODE_STRING*)->NTSTATUS;

auto ZwCopyVirtualMemory(PEPROCESS, LPVOID, PEPROCESS, LPVOID, SIZE_T, KPROCESSOR_MODE)->NTSTATUS;

auto ZwMmCopyMemory(LPVOID, LPVOID, SIZE_T)->NTSTATUS;

auto ZwProtectVirtualMemory(HANDLE, LPVOID)->NTSTATUS;

auto ZwProtectWindow(HWND, UINT)->BOOL;

auto ZwCreateThreadEx(HANDLE, LPVOID)->NTSTATUS;

auto ZwQueryKeyValue(LPCWSTR, LPCWSTR, PKEY_VALUE_PARTIAL_INFORMATION*)->NTSTATUS;

auto ZwEnumDeviceObj(PDRIVER_OBJECT, PDEVICE_OBJECT**, PULONG)->NTSTATUS;

auto ZwQueryNameStr(LPVOID, POBJECT_NAME_INFORMATION*, PULONG)->NTSTATUS;

auto ZwQueryFileEx(LPCWSTR)->NTSTATUS;

auto ZwDeleteFileEx(LPCWSTR)->NTSTATUS;

auto ZwReadFileEx(LPCWSTR, LPVOID, ULONG)->NTSTATUS;

auto ZwWriteFileEx(LPCWSTR, LPVOID, ULONG)->NTSTATUS;

auto ZwKillProcess(LPCWSTR)->NTSTATUS;

auto ZwProtectProcess(PEPROCESS, BOOLEAN)->NTSTATUS;

auto RtlImageNtHeader(LPBYTE)->LPVOID;

auto RtlImageDirectoryEntryToData(LPBYTE, BOOLEAN, USHORT, PULONG)->LPVOID;

auto RtlForceDeleteFile(PUNICODE_STRING)->NTSTATUS;

auto RtlSuperCopyMemory(LPVOID, LPVOID, ULONG)->NTSTATUS;

auto RtlAllocateMemory(SIZE_T)->LPBYTE;

auto RtlFreeMemoryEx(LPVOID)->VOID;

auto RtlFillMemoryEx(LPBYTE, BYTE, SIZE_T)->VOID;

auto RtlZeroMemoryEx(PVOID, SIZE_T)->VOID;

auto RtlCopyMemoryEx(PVOID, PVOID, SIZE_T)->VOID;

auto RtlRandMemoryEx(PVOID, SIZE_T)->VOID;

auto RtlAllocatePool(SIZE_T)->LPBYTE;

auto RtlGetSystemFun(LPWSTR)->LPBYTE;

auto SetPreviousMode(BYTE)->BYTE;

auto GetTextHashA(PCSTR)->UINT32;

auto GetTextHashW(PCWSTR)->UINT32;

auto StripPath(PUNICODE_STRING, PUNICODE_STRING)->NTSTATUS;

auto SearchStr(PUNICODE_STRING, PUNICODE_STRING, BOOLEAN)->NTSTATUS;

auto XorByte(LPBYTE, LPBYTE, SIZE_T)->LPBYTE;

auto Decrypt(LPBYTE, LPBYTE, SIZE_T, LPBYTE)->LPBYTE;

auto Compare(LPBYTE, PCHAR, PCHAR, DWORD)->BOOL;

auto SearchHookForImage(LPBYTE, PCHAR, PCHAR)->LPBYTE;

auto SearchSignForImage(LPBYTE, PCHAR, PCHAR, DWORD)->LPBYTE;

auto SearchSignForMemory(LPBYTE, DWORD, PCHAR, PCHAR, DWORD)->LPBYTE;

auto ResolveRelativeAddress(LPBYTE, ULONG)->LPBYTE;

auto GetSystemDrvJumpHook(PVOID, PHOOK_NOTIFY_BUFFER)->LPBYTE;

auto GetModuleBaseForHash(UINT32)->LPBYTE;

auto GetSystemModuleSection(LPVOID)->LPVOID;