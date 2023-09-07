#pragma once

#include <ntifs.h>
#include <ntddk.h>
#include <intrin.h>
#include <windef.h>
#include <bcrypt.h>
#include <ntimage.h>
#include <classpnp.h>
#include <ntstrsafe.h>
#include <minwindef.h>

#include "资源文件\NativeEnums.h"
#include "资源文件\NativeStructs.h"

#include "驱动文件.h"
#include "全局变量.h"
#include "导出函数.h"

#include "资源文件\\VMProtect\\VMProtectDDK.h"

extern "C" auto DriverEntry(PDRIVER_OBJECT, PUNICODE_STRING)->NTSTATUS;