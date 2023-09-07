#pragma once

auto ZwQuerySystemInformation(ULONG, LPVOID, ULONG, PULONG)->NTSTATUS;

auto ZwReadFileEx(LPCWSTR, PVOID, ULONG)->NTSTATUS;

auto ZwWriteFileEx(LPCWSTR, PVOID, ULONG)->NTSTATUS;

auto RtlImageNtHeader(LPBYTE)->LPVOID;

auto RtlImageDirectoryEntryToData(LPBYTE, BOOLEAN, USHORT, PULONG)->LPVOID;

auto RtlForceDeleteFile(PUNICODE_STRING)->NTSTATUS;

auto RtlZeroMemoryEx(PVOID, SIZE_T)->VOID;

auto RtlCopyMemoryEx(PVOID, PVOID, SIZE_T)->VOID;

auto RtlAllocateMemory(SIZE_T)->LPBYTE;

auto RtlFreeMemoryEx(LPVOID)->VOID;

auto RtlFillMemoryEx(LPBYTE, BYTE, SIZE_T)->VOID;

auto RtlAllocatePool(SIZE_T)->LPBYTE;

auto RtlGetSystemFun(LPWSTR)->LPBYTE;

auto GetTextHashA(PCSTR)->UINT32;

auto GetTextHashW(PCWSTR)->UINT32;

auto XorByte(LPBYTE, LPBYTE, SIZE_T)->LPBYTE;

auto Decrypt(LPBYTE, LPBYTE, SIZE_T, LPBYTE)->LPBYTE;

auto Compare(PCHAR, PCHAR, PCHAR)->BOOL;

auto SearchSignForImage(LPBYTE, PCHAR, PCHAR)->LPBYTE;

auto SearchSignForMemory(LPBYTE, DWORD, PCHAR, PCHAR)->LPBYTE;

auto ResolveRelativeAddress(LPBYTE, ULONG)->LPBYTE;

auto RvaToOffset(PIMAGE_NT_HEADERS64, ULONG, ULONG)->ULONG;

auto GetExportOffset(LPBYTE, ULONG, LPCSTR)->ULONG;

auto GetTableFunByName(PSYSTEM_SERVICE_DESCRIPTOR_TABLE, LPBYTE, ULONG, LPCSTR)->LPBYTE;

auto GetServiceTableBase(LPBYTE)->LPBYTE;

auto GetModuleBaseForHash(UINT32)->LPBYTE;

auto GetRoutineAddressForHash(LPBYTE, UINT32)->LPBYTE;

auto LdrProcessRelocationBlock(ULONGLONG, ULONG, PUSHORT, LONGLONG)->LPBYTE;

auto LdrRelocateImageWithBias(LPBYTE)->NTSTATUS;

auto ResolveImageRefs(LPBYTE)->NTSTATUS;

auto MmMapLoadDriver(LPBYTE)->NTSTATUS;