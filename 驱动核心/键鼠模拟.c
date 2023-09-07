#include "Çý¶¯ºËÐÄ.h"

PDEVICE_OBJECT MouseDeviceObject = NULL;

PDEVICE_OBJECT KeyDeviceObject = NULL;

MY_MOUSECALLBACK MouseClassServiceCallback = NULL;

MY_KEYBOARDCALLBACK KeyboardClassServiceCallback = NULL;

NTSTATUS SearchMouServiceCallBack() {

	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	PDRIVER_OBJECT ClassObject = NULL;

	PDRIVER_OBJECT DriverObject = NULL;

	PDEVICE_OBJECT DeviceObject = NULL;

	UNICODE_STRING DeviceName[] = { RTL_CONSTANT_STRING(L"\\Driver\\mouhid"), RTL_CONSTANT_STRING(L"\\Driver\\i8042prt") };

	VMProtectBeginMutation(__FUNCDNAME__);

	for (size_t i = 0; i < ARRAYSIZE(DeviceName); i++) {

		Status = ZwReferenceObjectByName(&DeviceName[i], OBJ_CASE_INSENSITIVE, NULL, 0, *IoDriverObjectType, KernelMode, NULL, (PVOID*)&DriverObject);

		if (NT_SUCCESS(Status)) {

			ObfDereferenceObject(DriverObject);

			break;
		}
	}

	if (DriverObject != NULL) {

		UNICODE_STRING ClassName = RTL_CONSTANT_STRING(L"\\Driver\\mouclass");

		Status = ZwReferenceObjectByName(&ClassName, OBJ_CASE_INSENSITIVE, NULL, 0, *IoDriverObjectType, KernelMode, NULL, (PVOID*)&ClassObject);

		if (NT_SUCCESS(Status)) {

			DeviceObject = DriverObject->DeviceObject;

			while (DeviceObject) {

				Status = SearchServiceFromMouExt(ClassObject, DeviceObject);

				if (!NT_SUCCESS(Status)) {

					DeviceObject = DeviceObject->NextDevice;
				}
				else
					break;
			}

			ObfDereferenceObject(ClassObject);
		}
	}

	VMProtectEnd();

	return Status;
}

NTSTATUS SearchServiceFromMouExt(PDRIVER_OBJECT MouDriverObject, PDEVICE_OBJECT pPortDev) {

	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	PDEVICE_OBJECT pTargetDeviceObject = NULL;

	UCHAR *DeviceExt = NULL;

	PVOID KbdDriverStart = NULL;

	ULONG KbdDriverSize = 0;

	PDEVICE_OBJECT pTmpDev = NULL;

	UNICODE_STRING kbdDriName = { 0 };

	VMProtectBeginMutation(__FUNCDNAME__);

	KbdDriverStart = MouDriverObject->DriverStart;

	KbdDriverSize = MouDriverObject->DriverSize;

	RtlInitUnicodeString(&kbdDriName, L"\\Driver\\mouclass");

	pTmpDev = pPortDev;

	while (pTmpDev->AttachedDevice != NULL) {

		if (RtlCompareUnicodeString(&pTmpDev->AttachedDevice->DriverObject->DriverName, &kbdDriName, TRUE)) {

			pTmpDev = pTmpDev->AttachedDevice;
		}
		else
			break;
	}

	if (pTmpDev->AttachedDevice != NULL) {

		pTargetDeviceObject = MouDriverObject->DeviceObject;

		while (pTargetDeviceObject) {

			if (pTmpDev->AttachedDevice != pTargetDeviceObject) {

				pTargetDeviceObject = pTargetDeviceObject->NextDevice;

				continue;
			}

			DeviceExt = (UCHAR *)pTmpDev->DeviceExtension;

			MouseDeviceObject = NULL;

			for (ULONG i = 0; i < PAGE_SIZE; i++, DeviceExt++) {

				if (MmIsAddressValid(DeviceExt)) {

					PVOID pTemp = *(PVOID*)DeviceExt;

					if (MouseDeviceObject && MouseClassServiceCallback) {

						Status = STATUS_SUCCESS;

						break;
					}

					if (pTemp == pTargetDeviceObject) {

						MouseDeviceObject = pTargetDeviceObject;

						continue;
					}

					if (pTemp > KbdDriverStart && pTemp < (PVOID)((UCHAR*)KbdDriverStart + KbdDriverSize) && MmIsAddressValid(pTemp)) {

						MouseClassServiceCallback = (MY_MOUSECALLBACK)pTemp;

						Status = STATUS_SUCCESS;
					}
				}
				else
					break;
			}

			if (Status == STATUS_SUCCESS) {

				break;
			}

			pTargetDeviceObject = pTargetDeviceObject->NextDevice;
		}
	}

	VMProtectEnd();

	return Status;
}

NTSTATUS SearchKdbServiceCallBack() {

	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	PDRIVER_OBJECT ClassObject = NULL;

	PDRIVER_OBJECT DriverObject = NULL;

	PDEVICE_OBJECT DeviceObject = NULL;

	UNICODE_STRING DeviceName[] = { RTL_CONSTANT_STRING(L"\\Driver\\kbdhid"), RTL_CONSTANT_STRING(L"\\Driver\\i8042prt") };

	VMProtectBeginMutation(__FUNCDNAME__);

	for (size_t i = 0; i < ARRAYSIZE(DeviceName); i++) {

		Status = ZwReferenceObjectByName(&DeviceName[i], OBJ_CASE_INSENSITIVE, NULL, 0, *IoDriverObjectType, KernelMode, NULL, (PVOID*)&DriverObject);

		if (NT_SUCCESS(Status)) {

			ObfDereferenceObject(DriverObject);

			break;
		}
	}

	if (DriverObject != NULL) {

		UNICODE_STRING ClassName = RTL_CONSTANT_STRING(L"\\Driver\\kbdclass");

		Status = ZwReferenceObjectByName(&ClassName, OBJ_CASE_INSENSITIVE, NULL, 0, *IoDriverObjectType, KernelMode, NULL, (PVOID*)&ClassObject);

		if (NT_SUCCESS(Status)) {

			DeviceObject = DriverObject->DeviceObject;

			while (DeviceObject) {

				Status = SearchServiceFromKdbExt(ClassObject, DeviceObject);

				if (!NT_SUCCESS(Status)) {

					DeviceObject = DeviceObject->NextDevice;
				}
				else
					break;
			}

			ObfDereferenceObject(ClassObject);
		}
	}

	VMProtectEnd();

	return Status;
}

NTSTATUS SearchServiceFromKdbExt(PDRIVER_OBJECT KbdDriverObject, PDEVICE_OBJECT pPortDev) {

	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	PDEVICE_OBJECT pTargetDeviceObject = NULL;

	UCHAR *DeviceExt = NULL;

	PVOID KbdDriverStart = NULL;

	ULONG KbdDriverSize = 0;

	PDEVICE_OBJECT pTmpDev = NULL;

	UNICODE_STRING kbdDriName = { 0 };

	VMProtectBeginMutation(__FUNCDNAME__);

	KbdDriverStart = KbdDriverObject->DriverStart;

	KbdDriverSize = KbdDriverObject->DriverSize;

	RtlInitUnicodeString(&kbdDriName, L"\\Driver\\kbdclass");

	pTmpDev = pPortDev;

	while (pTmpDev->AttachedDevice != NULL) {

		if (RtlCompareUnicodeString(&pTmpDev->AttachedDevice->DriverObject->DriverName, &kbdDriName, TRUE)) {

			pTmpDev = pTmpDev->AttachedDevice;
		}
		else
			break;
	}

	if (pTmpDev->AttachedDevice != NULL) {

		pTargetDeviceObject = KbdDriverObject->DeviceObject;

		while (pTargetDeviceObject) {

			if (pTmpDev->AttachedDevice != pTargetDeviceObject) {

				pTargetDeviceObject = pTargetDeviceObject->NextDevice;

				continue;
			}

			DeviceExt = (UCHAR *)pTmpDev->DeviceExtension;

			KeyDeviceObject = NULL;

			for (ULONG i = 0; i < PAGE_SIZE; i++, DeviceExt++) {

				if (MmIsAddressValid(DeviceExt)) {

					PVOID pTemp = *(PVOID*)DeviceExt;

					if (KeyDeviceObject && KeyboardClassServiceCallback) {

						Status = STATUS_SUCCESS;

						break;
					}

					if (pTemp == pTargetDeviceObject) {

						KeyDeviceObject = pTargetDeviceObject;

						continue;
					}

					if (pTemp > KbdDriverStart && pTemp < (PVOID)((UCHAR*)KbdDriverStart + KbdDriverSize) && MmIsAddressValid(pTemp)) {

						KeyboardClassServiceCallback = (MY_KEYBOARDCALLBACK)pTemp;
					}
				}
				else
					break;
			}

			if (Status == STATUS_SUCCESS) {

				break;
			}

			pTargetDeviceObject = pTargetDeviceObject->NextDevice;
		}
	}

	VMProtectEnd();

	return Status;
}