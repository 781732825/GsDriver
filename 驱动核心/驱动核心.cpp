#include "驱动核心.h"

auto VariateInit()->NTSTATUS {

	/*内核发包*/ {

		RtlZeroMemoryEx(&WSKProviderNpi, sizeof(WSKProviderNpi));

		RtlZeroMemoryEx(&WSKSocketsState, sizeof(WSKSocketsState));

		RtlZeroMemoryEx(&WSKRegistration, sizeof(WSKRegistration));

		RtlZeroMemoryEx(&WSKClientDispatch, sizeof(WSKClientDispatch));
	}

	/*键鼠模拟*/ {

		RtlZeroMemoryEx(&MouseDeviceObject, sizeof(MouseDeviceObject));

		RtlZeroMemoryEx(&MouseClassServiceCallback, sizeof(MouseClassServiceCallback));

		RtlZeroMemoryEx(&KeyboardDeviceObject, sizeof(KeyboardDeviceObject));

		RtlZeroMemoryEx(&KeyboardClassServiceCallback, sizeof(KeyboardClassServiceCallback));
	}

	return STATUS_SUCCESS;
}

auto DriverStart()->NTSTATUS {

	NTSTATUS Status = STATUS_SUCCESS;

	Status = ZwReadFileEx(L"\\SystemRoot\\System32\\GSDrv.bin", &DynamicData, sizeof(PDYNDATA));

	if (NT_SUCCESS(Status) && DynamicData != NULL) {

		RtlZeroMemoryEx(&pHideMemoryList, sizeof(pHideMemoryList));

		RtlZeroMemoryEx(DynamicData->DriverBase, PAGE_SIZE);

		RtlZeroMemoryEx(&InjectCache, sizeof(InjectCache));

		RtlZeroMemoryEx(&InjectData, sizeof(InjectData));

		pHideMemoryList = (PHIDE_MEMORY_BUFFER)(RtlAllocateMemory(sizeof(HIDE_MEMORY_BUFFER)));

		pInjectNotifyHookBuffer = (PHOOK_NOTIFY_BUFFER)(RtlAllocateMemory(sizeof(HIDE_MEMORY_BUFFER)));

		pProcessNotifyHookBuffer = (PHOOK_NOTIFY_BUFFER)(RtlAllocateMemory(sizeof(HOOK_NOTIFY_BUFFER)));

		pRegisterNotifyHookBuffer = (PHOOK_NOTIFY_BUFFER)(RtlAllocateMemory(sizeof(HOOK_NOTIFY_BUFFER)));
	}

	return Status;
}

auto DriverEntry()->VOID {

	if (NT_SUCCESS(VariateInit())) {

		if (NT_SUCCESS(DriverStart())) {

			RegisterNotifyInit(TRUE);

			PsTerminateSystemThread(NULL);
		}
	}
}