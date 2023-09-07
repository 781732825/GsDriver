#pragma once

typedef struct _DYNDATA {
	ULONG UserVerify;
	ULONG WinVersion;
	ULONG BuildNumber;
	ULONG VadRoot;
	ULONG PrcessId;
	ULONG Protection;
	ULONG PspCidTable;
	ULONG ProcessLinks;
	ULONG PrcessIdOffset;
	ULONG ParentPrcessIdOffset;
	PBYTE KernelBase;
	PBYTE DriverBase;
	PBYTE ModuleList;
	PBYTE Decryption;
	PBYTE PageTables[4];
	PBYTE NtCreateThreadEx;
	PBYTE NtProtectVirtualMemory;
} DYNDATA, *PDYNDATA;

typedef struct _INJECT_DATA {
	INT32 InjectHash;
	INT32 InjectBits;
	INT32 InjectMode;
	INT32 InjectHide;
	PBYTE InjectData;
	INT64 InjectSize;
} INJECT_DATA, *PINJECT_DATA;

typedef struct _INJECT_CACHE {
	LPVOID hProcessId;
	PBYTE AllocCache[3];
	PBYTE SteamCache[6];
} INJECT_CACHE, *PINJECT_CACHE;

typedef struct _HIDE_MEMORY_BUFFER {
	PEPROCESS pProcess;
	UINT64 Address;
	SIZE_T Size;
} HIDE_MEMORY_BUFFER, *PHIDE_MEMORY_BUFFER;

typedef struct _HOOK_NOTIFY_BUFFER {
	ULONG Enable;
	PVOID HookPoint;
	UCHAR NewBytes[13];
	UCHAR OldBytes[13];
	PVOID NotifyHandle;
	LARGE_INTEGER Cookie;
} HOOK_NOTIFY_BUFFER, *PHOOK_NOTIFY_BUFFER;

typedef struct _SYSTEM_MODULE_INFORMATION_ENTRY {
	PBYTE Section;
	PBYTE MappedBase;
	PBYTE ImageBase;
	ULONG ImageSize;
	ULONG Flags;
	SHORT LoadOrderIndex;
	SHORT InitOrderIndex;
	SHORT LoadCount;
	SHORT PathLength;
	CHAR ImageName[256];
} SYSTEM_MODULE_INFORMATION_ENTRY, *PSYSTEM_MODULE_INFORMATION_ENTRY;

typedef struct _SYSTEM_MODULE_INFORMATION {
	ULONG NumberOfModules;
	SYSTEM_MODULE_INFORMATION_ENTRY Modules[1];
} SYSTEM_MODULE_INFORMATION, *PSYSTEM_MODULE_INFORMATION;

typedef struct _SYSTEM_THREAD_INFORMATION {
	LARGE_INTEGER KernelTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER CreateTime;
	ULONG WaitTime;
	LPVOID StartAddress;
	CLIENT_ID ClientId;
	KPRIORITY Priority;
	LONG BasePriority;
	ULONG ContextSwitches;
	ULONG ThreadState;
	ULONG WaitReason;
	ULONG PadPadAlignment;
} SYSTEM_THREAD_INFORMATION, *PSYSTEM_THREAD_INFORMATION;

typedef struct _SYSTEM_PROCESS_INFORMATION {
	ULONG NextEntryOffset;
	ULONG NumberOfThreads;
	LARGE_INTEGER WorkingSetPrivateSize;
	ULONG HardFaultCount;
	ULONG NumberOfThreadsHighWatermark;
	ULONGLONG CycleTime;
	LARGE_INTEGER CreateTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER KernelTime;
	UNICODE_STRING ImageName;
	KPRIORITY BasePriority;
	HANDLE hProcessId;
	HANDLE UniqueProcessId;
	ULONG HandleCount;
	ULONG SessionId;
	ULONG_PTR UniqueProcessKey;
	SIZE_T PeakVirtualSize;
	SIZE_T VirtualSize;
	ULONG PageFaultCount;
	SIZE_T PeakWorkingSetSize;
	SIZE_T WorkingSetSize;
	SIZE_T QuotaPeakPagedPoolUsage;
	SIZE_T QuotaPagedPoolUsage;
	SIZE_T QuotaPeakNonPagedPoolUsage;
	SIZE_T QuotaNonPagedPoolUsage;
	SIZE_T PagefileUsage;
	SIZE_T PeakPagefileUsage;
	SIZE_T PrivatePageCount;
	LARGE_INTEGER ReadOperationCount;
	LARGE_INTEGER WriteOperationCount;
	LARGE_INTEGER OtherOperationCount;
	LARGE_INTEGER ReadTransferCount;
	LARGE_INTEGER WriteTransferCount;
	LARGE_INTEGER OtherTransferCount;
	SYSTEM_THREAD_INFORMATION Threads[1];
} SYSTEM_PROCESS_INFORMATION, *PSYSTEM_PROCESS_INFORMATION;

typedef struct _KLDR_DATA_TABLE_ENTRY {
	LIST_ENTRY InLoadOrderLinks;
	PBYTE ExceptionTable;
	ULONG ExceptionTableSize;
	PBYTE GpValue;
	PNON_PAGED_DEBUG_INFO NonPagedDebugInfo;
	PBYTE DllBase;
	PBYTE EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
} KLDR_DATA_TABLE_ENTRY, *PKLDR_DATA_TABLE_ENTRY;

typedef struct _HANDLE_TABLE {
	ULONG_PTR TableCode;
	struct _EPROCESS *QuotaProcess;
	HANDLE UniqueProcessId;
	void* HandleLock;
	struct _LIST_ENTRY HandleTableList;
	EX_PUSH_LOCK HandleContentionEvent;
	struct _HANDLE_TRACE_DEBUG_INFO *DebugInfo;
	int ExtraInfoPages;
	ULONG Flags;
	ULONG FirstFreeHandle;
	struct _HANDLE_TABLE_ENTRY *LastFreeHandleEntry;
	ULONG HandleCount;
	ULONG NextHandleNeedingPool;
} HANDLE_TABLE, *PHANDLE_TABLE;

typedef struct _HANDLE_TABLE_ENTRY {
	union {
		ULONG_PTR VolatileLowValue;
		ULONG_PTR LowValue;
		struct _HANDLE_TABLE_ENTRY_INFO* InfoTable;
		struct {
			ULONG64 Unlocked : 1;
			ULONG64 RefCnt : 16;
			ULONG64 Attributes : 3;
			ULONG64 ObjectPointerBits : 44;
		};
	};
	union {
		ULONG_PTR HighValue;
		struct _HANDLE_TABLE_ENTRY* NextFreeHandleEntry;
		ULONG_PTR LeafHandleValue;
		struct {
			ULONG32 GrantedAccessBits : 25;
			ULONG32 NoRightsUpgrade : 1;
			ULONG32 Spare : 6;
		};
	};
	ULONG TypeInfo;
} HANDLE_TABLE_ENTRY, *PHANDLE_TABLE_ENTRY;

typedef struct _MMPTE_HARDWARE {
	UINT64 Valid : 1;
	UINT64 Dirty1 : 1;
	UINT64 Owner : 1;
	UINT64 WriteThrough : 1;
	UINT64 CacheDisable : 1;
	UINT64 Accessed : 1;
	UINT64 Dirty : 1;
	UINT64 LargePage : 1;
	UINT64 Global : 1;
	UINT64 CopyOnWrite : 1;
	UINT64 Unused : 1;
	UINT64 Write : 1;
	UINT64 PageFrameNumber : 36;
	UINT64 ReservedForHardware : 4;
	UINT64 ReservedForSoftware : 4;
	UINT64 WsleAge : 4;
	UINT64 WsleProtection : 3;
	UINT64 NoExecute : 1;
} MMPTE_HARDWARE, *PMMPTE_HARDWARE;

typedef struct _MMPTE {
	union {

		UINT64 Long;
		UINT64 VolatileLong;
		MMPTE_HARDWARE Hard;
	} u;
} MMPTE, *PMMPTE;

typedef struct _WIN7_MM_AVL_NODE {
	/*+0x000*/    union
	{
		/*+0x000*/        INT64 Balance;
		/*+0x000*/        struct _MMADDRESS_NODE* Parent;
	};
	/*+0x008*/    struct _WIN7_MM_AVL_NODE* LeftChild;
	/*+0x010*/    struct _WIN7_MM_AVL_NODE* RightChild;
	/*+0x018*/    UINT64 StartingVpn;
	/*+0x020*/    UINT64 EndingVpn;
} WIN7_MM_AVL_NODE, *WIN7_PMM_AVL_NODE;

typedef struct _WIN7_MM_AVL_TABLE {
	/*+0x000*/    struct _WIN7_MM_AVL_NODE BalancedRoot;
	/*+0x028*/    union
	{
		/*+0x028*/    UINT64 DepthOfTree : 5;
		/*+0x028*/    UINT64 Unused : 3;
		/*+0x028*/    UINT64 NumberGenericTableElements : 56;
	};
	/*+0x030*/    LPVOID NodeHint;
	/*+0x038*/    LPVOID NodeFreeHint;
} WIN7_MM_AVL_TABLE, *WIN7_PMM_AVL_TABLE;

typedef struct _WIN7_MMVAD_SHORT {
	/*+0x000*/    union
	{
		/*+0x000*/        INT64 Balance;
		/*+0x000*/        struct _MMVAD* Parent;
	};
	/*+0x008*/    struct _MMVAD* LeftChild;
	/*+0x010*/    struct _MMVAD* RightChild;
	/*+0x018*/    UINT64 StartingVpn;
	/*+0x020*/    UINT64 EndingVpn;
	/*+0x028*/    UINT64 VadFlags;
	/*+0x030*/    struct _EX_PUSH_LOCK* PushLock;
	/*+0x038*/    UINT64 VadFlags3;
} WIN7_MMVAD_SHORT, *WIN7_PMMVAD_SHORT;

typedef struct _WIN8_MM_AVL_NODE {
	/*+0x000*/    union
	{
		/*+0x000*/        INT64 Balance;
		/*+0x000*/        struct _WIN8_MM_AVL_NODE* Parent;
	};
	/*+0x008*/    struct _WIN8_MM_AVL_NODE* LeftChild;
	/*+0x010*/    struct _WIN8_MM_AVL_NODE* RightChild;
} WIN8_MM_AVL_NODE, *WIN8_PMM_AVL_NODE;

typedef struct _WIN8_MM_AVL_TABLE {
	/*+0x000*/    struct _WIN8_MM_AVL_NODE BalancedRoot;
	/*+0x018*/    UINT64 DepthOfTree : 5;
	/*+0x018*/    UINT64 TableType : 3;
	/*+0x018*/    UINT64 NumberGenericTableElements : 56;
	/*+0x020*/    LPVOID NodeHint;
	/*+0x028*/    LPVOID NodeFreeHint;
} WIN8_MM_AVL_TABLE, *WIN8_PMM_AVL_TABLE;

typedef struct _WIN8_MMVAD_SHORT {
	/*+0x000*/    struct _WIN8_MM_AVL_NODE VadNode;
	/*+0x018*/    ULONG StartingVpn;
	/*+0x01C*/    ULONG EndingVpn;
	/*+0x020*/    struct _EX_PUSH_LOCK* PushLock;
	/*+0x028*/    ULONG VadFlags;
	/*+0x02C*/    ULONG VadFlags1;
	/*+0x030*/    struct _WIN8_MI_VAD_EVENT_BLOCK* EventList;
	/*+0x038*/    LONG ReferenceCount;
} WIN8_MMVAD_SHORT, *WIN8_PMMVAD_SHORT;

typedef struct _WIN8X_MM_AVL_NODE {
	/*+0x000*/    union
	{
		struct _WIN8X_MM_AVL_NODE *Children[2];
		struct
		{
			struct _WIN8X_MM_AVL_NODE *LeftChild;
			struct _WIN8X_MM_AVL_NODE *RightChild;
		};
	};
	/*+0x010*/    union
	{
		UCHAR Red : 1;
		UCHAR Balance : 2;
		ULONG_PTR ParentValue;
	};
} WIN8X_MM_AVL_NODE, *WIN8X_PMM_AVL_NODE;

typedef struct _WIN8X_MM_AVL_TABLE {
	/*+0x000*/    union
	{
		/*+0x000*/    struct _WIN1X_MM_AVL_NODE* BalancedRoot;
		/*+0x000*/    void* NodeHint;
		/*+0x000*/    unsigned __int64 NumberGenericTableElements;
	};
} WIN8X_MM_AVL_TABLE, *WIN8X_PMM_AVL_TABLE;

typedef struct _WIN8X_MMVAD_SHORT {
	/*+0x000*/    union
	{
		/*+0x000*/    struct _WIN8X_MM_AVL_NODE VadNode;
		/*+0x000*/    struct _WIN8X_MMVAD_SHORT* NextVad;
	};
	/*+0x018*/    ULONG StartingVpn;
	/*+0x01C*/    ULONG EndingVpn;
	/*+0x020*/    UCHAR StartingVpnHigh;
	/*+0x021*/    UCHAR EndingVpnHigh;
	/*+0x022*/    UCHAR CommitChargeHigh;
	/*+0x023*/    UCHAR LargeImageBias;
	/*+0x024*/    LONG ReferenceCount;
	/*+0x028*/    struct _EX_PUSH_LOCK* PushLock;
	/*+0x030*/    ULONG VadFlags;
	/*+0x034*/    ULONG VadFlags1;
	/*+0x038*/    struct _MI_VAD_EVENT_BLOCK* EventList;
} WIN8X_MMVAD_SHORT, *WIN8X_PMMVAD_SHORT;

typedef struct _WIN1X_MM_AVL_NODE {
	/*+0x000*/    union
	{
		struct _WIN1X_MM_AVL_NODE *Children[2];
		struct
		{
			struct _WIN1X_MM_AVL_NODE *LeftChild;
			struct _WIN1X_MM_AVL_NODE *RightChild;
		};
	};
	/*+0x010*/    union
	{
		UCHAR Red : 1;
		UCHAR Balance : 2;
		ULONG_PTR ParentValue;
	};
} WIN1X_MM_AVL_NODE, *WIN1X_PMM_AVL_NODE;

typedef struct _WIN1X_MM_AVL_TABLE {
	/*+0x000*/    union
	{
		/*+0x000*/    struct _WIN1X_MM_AVL_NODE* BalancedRoot;
		/*+0x000*/    void* NodeHint;
		/*+0x000*/    unsigned __int64 NumberGenericTableElements;
	};
} WIN1X_MM_AVL_TABLE, *WIN1X_PMM_AVL_TABLE;

typedef struct _WIN1X_MMVAD_SHORT {
	/*+0x000*/    union
	{
		/*+0x000*/    struct _WIN1X_MM_AVL_NODE VadNode;
		/*+0x000*/    struct _WIN1X_MMVAD_SHORT* NextVad;
	};
	/*+0x018*/    ULONG StartingVpn;
	/*+0x01C*/    ULONG EndingVpn;
	/*+0x020*/    UCHAR StartingVpnHigh;
	/*+0x021*/    UCHAR EndingVpnHigh;
	/*+0x022*/    UCHAR CommitChargeHigh;
	/*+0x023*/    UCHAR SpareNT64VadUChar;
	/*+0x024*/    ULONG ReferenceCount;
	/*+0x028*/    LPVOID PushLock;
	/*+0x030*/    ULONG VadFlags;
	/*+0x034*/    ULONG LongFlags;
	/*+0x038*/    struct _MI_VAD_EVENT_BLOCK* EventList;
} WIN1X_MMVAD_SHORT, *WIN1X_PMMVAD_SHORT;