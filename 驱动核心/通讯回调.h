#pragma once

extern PHOOK_NOTIFY_BUFFER pRegisterNotifyHookBuffer;

auto OpenProcessEx(HANDLE, PEPROCESS*, HANDLE*)->NTSTATUS;

auto RegisterVerify(PCHAR)->NTSTATUS;

auto RegisterNotify(LPVOID, REG_NOTIFY_CLASS, PREG_SET_VALUE_KEY_INFORMATION)->NTSTATUS;

auto RegisterNotifyInit(BOOLEAN)->NTSTATUS;