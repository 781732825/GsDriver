#pragma once

typedef struct _MOUSE_INPUT_DATA {
	USHORT UnitId;
	USHORT Flags;
	union {
		ULONG Buttons;
		struct {
			USHORT  ButtonFlags;
			USHORT  ButtonData;
		};
	};
	ULONG RawButtons;
	LONG LastX;
	LONG LastY;
	ULONG ExtraInformation;
} MOUSE_INPUT_DATA, *PMOUSE_INPUT_DATA;

typedef struct _KEYBOARD_INPUT_DATA {
	USHORT UnitId;
	USHORT MakeCode;
	USHORT Flags;
	USHORT Reserved;
	ULONG ExtraInformation;
} KEYBOARD_INPUT_DATA, *PKEYBOARD_INPUT_DATA;

typedef VOID(*MY_KEYBOARDCALLBACK) (PDEVICE_OBJECT, PKEYBOARD_INPUT_DATA, PKEYBOARD_INPUT_DATA, PULONG);

typedef VOID(*MY_MOUSECALLBACK) (PDEVICE_OBJECT, PMOUSE_INPUT_DATA, PMOUSE_INPUT_DATA, PULONG);

extern "C" POBJECT_TYPE *IoDriverObjectType;

extern PDEVICE_OBJECT MouseDeviceObject;

extern PDEVICE_OBJECT KeyboardDeviceObject;

extern MY_MOUSECALLBACK MouseClassServiceCallback;

extern MY_KEYBOARDCALLBACK KeyboardClassServiceCallback;

auto SearchMouServiceCallBack()->NTSTATUS;

auto SearchServiceFromMouExt(PDRIVER_OBJECT, PDEVICE_OBJECT)->NTSTATUS;

auto SearchKdbServiceCallBack()->NTSTATUS;

auto SearchServiceFromKdbExt(PDRIVER_OBJECT, PDEVICE_OBJECT)->NTSTATUS;