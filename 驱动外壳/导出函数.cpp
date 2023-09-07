#include "Çý¶¯Íâ¿Ç.h"

auto ZwQuerySystemInformation(ULONG SystemInformationClass, LPVOID SystemInformation, ULONG SystemInformationLength, PULONG ReturnLength)->NTSTATUS {

	typedef NTSTATUS(NTAPI *fn_ZwQuerySystemInformation)(ULONG, LPVOID, ULONG, PULONG);

	static fn_ZwQuerySystemInformation _ZwQuerySystemInformation = NULL;

	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	if (_ZwQuerySystemInformation == NULL) {

		_ZwQuerySystemInformation = (fn_ZwQuerySystemInformation)(RtlGetSystemFun(L"ZwQuerySystemInformation"));
	}

	if (_ZwQuerySystemInformation != NULL) {

		Status = _ZwQuerySystemInformation(SystemInformationClass, SystemInformation, SystemInformationLength, ReturnLength);
	}

	return Status;
}

auto ZwReadFileEx(LPCWSTR FilePath, PVOID pBuffer, ULONG BufferSize)->NTSTATUS {

	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	HANDLE hFile = NULL;

	OBJECT_ATTRIBUTES ObjectAttributes;

	IO_STATUS_BLOCK IoStatusBlock;

	UNICODE_STRING usFileName;

	RtlInitUnicodeString(&usFileName, FilePath);

	InitializeObjectAttributes(&ObjectAttributes, &usFileName, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	Status = ZwCreateFile(&hFile, GENERIC_READ, &ObjectAttributes, &IoStatusBlock, NULL, FILE_ATTRIBUTE_NORMAL, FILE_SHARE_READ, FILE_OPEN, FILE_SYNCHRONOUS_IO_NONALERT, NULL, 0);

	if (NT_SUCCESS(Status)) {

		LARGE_INTEGER ByteOffset = { NULL };

		Status = ZwReadFile(hFile, NULL, NULL, NULL, &IoStatusBlock, pBuffer, BufferSize, &ByteOffset, NULL);

		if (NT_SUCCESS(Status)) {

			ZwClose(hFile);

			ZwDeleteFile(&ObjectAttributes);
		}
	}

	return Status;
}

auto ZwWriteFileEx(LPCWSTR FilePath, PVOID pBuffer, ULONG BufferSize)->NTSTATUS {

	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	HANDLE hFile = NULL;

	OBJECT_ATTRIBUTES ObjectAttributes;

	IO_STATUS_BLOCK IoStatusBlock;

	UNICODE_STRING usFileName;

	RtlInitUnicodeString(&usFileName, FilePath);

	InitializeObjectAttributes(&ObjectAttributes, &usFileName, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	Status = ZwCreateFile(&hFile, GENERIC_ALL, &ObjectAttributes, &IoStatusBlock, NULL, FILE_ATTRIBUTE_NORMAL, FILE_SHARE_READ | FILE_SHARE_WRITE, FILE_OPEN_IF, FILE_SYNCHRONOUS_IO_NONALERT, NULL, 0);

	if (NT_SUCCESS(Status)) {

		LARGE_INTEGER liFileOff = { NULL };

		Status = ZwWriteFile(hFile, NULL, NULL, NULL, &IoStatusBlock, pBuffer, BufferSize, &liFileOff, NULL);

		ZwClose(hFile);
	}

	return Status;
}

auto RtlImageNtHeader(LPBYTE ImageBase)->LPVOID {

	typedef LPVOID(NTAPI *fn_RtlImageNtHeader)(LPBYTE);

	static fn_RtlImageNtHeader _RtlImageNtHeader = NULL;

	LPVOID Result = NULL;

	if (_RtlImageNtHeader == NULL) {

		_RtlImageNtHeader = (fn_RtlImageNtHeader)(RtlGetSystemFun(L"RtlImageNtHeader"));
	}

	if (_RtlImageNtHeader != NULL) {

		Result = _RtlImageNtHeader(ImageBase);
	}

	return Result;
}

auto RtlImageDirectoryEntryToData(LPBYTE ImageBase, BOOLEAN MappedAsImage, USHORT DirectoryEntry, PULONG Size)->LPVOID {

	typedef LPVOID(NTAPI *fn_RtlImageDirectoryEntryToData)(LPBYTE, BOOLEAN, USHORT, PULONG);

	static fn_RtlImageDirectoryEntryToData _RtlImageDirectoryEntryToData = NULL;

	LPVOID Result = NULL;

	if (_RtlImageDirectoryEntryToData == NULL) {

		_RtlImageDirectoryEntryToData = (fn_RtlImageDirectoryEntryToData)(RtlGetSystemFun(L"RtlImageDirectoryEntryToData"));
	}

	if (_RtlImageDirectoryEntryToData != NULL) {

		Result = _RtlImageDirectoryEntryToData(ImageBase, MappedAsImage, DirectoryEntry, Size);
	}

	return Result;
}

auto RtlForceDeleteFile(PUNICODE_STRING pFilePath)->NTSTATUS {

	NTSTATUS Status = STATUS_SUCCESS;

	HANDLE hFile = NULL;

	LPBYTE pFileObject = NULL;

	IO_STATUS_BLOCK IoStatusBlock;

	OBJECT_ATTRIBUTES ObjectAttributes;

	InitializeObjectAttributes(&ObjectAttributes, pFilePath, OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE, 0, 0);

	Status = IoCreateFileEx(&hFile, SYNCHRONIZE | DELETE, &ObjectAttributes, &IoStatusBlock, NULL, FILE_ATTRIBUTE_NORMAL, FILE_SHARE_DELETE, FILE_OPEN, FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT, NULL, 0, CreateFileTypeNone, NULL, IO_NO_PARAMETER_CHECKING, NULL);

	if (NT_SUCCESS(Status)) {

		Status = ObReferenceObjectByHandleWithTag(hFile, SYNCHRONIZE | DELETE, *IoFileObjectType, KernelMode, 'ELIF', (LPVOID*)&pFileObject, NULL);

		if (NT_SUCCESS(Status)) {

			((PFILE_OBJECT)pFileObject)->SectionObjectPointer->ImageSectionObject = NULL;

			if (MmFlushImageSection(((PFILE_OBJECT)pFileObject)->SectionObjectPointer, MmFlushForDelete)) {

				Status = ZwDeleteFile(&ObjectAttributes);
			}

			ObfDereferenceObject(pFileObject);
		}

		ObCloseHandle(hFile, KernelMode);
	}

	return Status;
}

auto RtlZeroMemoryEx(PVOID pDst, SIZE_T Size)->VOID {

	for (SIZE_T i = 0; i < Size; i++) {

		((BYTE*)pDst)[i] = (BYTE)0;
	}
}

auto RtlCopyMemoryEx(PVOID pDst, PVOID pSrc, SIZE_T Size)->VOID {

	for (SIZE_T i = 0; i < Size; i++) {

		((BYTE*)pDst)[i] = ((BYTE*)pSrc)[i];
	}
}

auto RtlAllocateMemory(SIZE_T Size)->LPBYTE {

	LPBYTE Result = (LPBYTE)(ExAllocatePoolWithTag(NonPagedPool, Size, 'SG'));

	if (Result != NULL) {

		RtlZeroMemoryEx(Result, Size);
	}

	return Result;
}

auto RtlFreeMemoryEx(LPVOID pDst)->VOID {

	if (pDst != NULL) {

		ExFreePoolWithTag(pDst, 'SG');

		pDst = NULL;
	}
}

auto RtlFillMemoryEx(LPBYTE pDst, BYTE Value, SIZE_T Size)->VOID {

	for (SIZE_T i = NULL; i < Size; i++) {

		((BYTE*)pDst)[i] = Value;
	}
}

auto RtlAllocatePool(SIZE_T Size)->LPBYTE {

	return (LPBYTE)(ExAllocatePoolWithTag(NonPagedPoolExecute, Size, 'SG'));
}

auto RtlGetSystemFun(LPWSTR Name)->LPBYTE {

	UNICODE_STRING RoutineName;

	RtlInitUnicodeString(&RoutineName, Name);

	return (LPBYTE)(MmGetSystemRoutineAddress(&RoutineName));
}

auto GetTextHashA(PCSTR Str)->UINT32 {

	UINT32 Hash = 0;

	while (Str != NULL && *Str) {

		Hash = (UINT32)(65599 * (Hash + (*Str++) + (*Str > 64 && *Str < 91 ? 32 : 0)));
	}

	return Hash;
}

auto GetTextHashW(PCWSTR Str)->UINT {

	UINT32 Hash = 0;

	while (Str != NULL && *Str) {

		Hash = (UINT32)(65599 * (Hash + (*Str++) + (*Str > 64 && *Str < 91 ? 32 : 0)));
	}

	return Hash;
}

auto XorByte(LPBYTE Dst, LPBYTE Src, SIZE_T Size)->LPBYTE {

	for (ULONG i = 0; i < Size; i++) {

		Dst[i] = (BOOLEAN)(Src[i] != 0x00 && Src[i] != 0xFF) ? Src[i] ^ 0xFF : Src[i];
	}

	return Dst;
}

auto Decrypt(LPBYTE Dst, LPBYTE Src, SIZE_T Size, LPBYTE Decryption)->LPBYTE {

	BCRYPT_KEY_HANDLE BcryptKeyHandle = NULL;

	BCRYPT_ALG_HANDLE BcryptAlgHandle = NULL;

	if (NT_SUCCESS(BCryptOpenAlgorithmProvider(&BcryptAlgHandle, BCRYPT_AES_ALGORITHM, MS_PRIMITIVE_PROVIDER, BCRYPT_PROV_DISPATCH))) {

		if (NT_SUCCESS(BCryptSetProperty(BcryptAlgHandle, BCRYPT_CHAINING_MODE, (LPBYTE)(BCRYPT_CHAIN_MODE_ECB), sizeof(BCRYPT_CHAIN_MODE_ECB), NULL))) {

			if (NT_SUCCESS(BCryptGenerateSymmetricKey(BcryptAlgHandle, &BcryptKeyHandle, NULL, NULL, Decryption, 16, NULL))) {

				ULONG pResult = NULL;

				BCryptDecrypt(BcryptKeyHandle, (LPBYTE)(Src), (ULONG)(Size), NULL, NULL, NULL, (LPBYTE)(Dst), (ULONG)(Size), &pResult, BCRYPT_PAD_PKCS1);

				BCryptDestroyKey(BcryptKeyHandle);

				XorByte(Dst, Dst, Size);
			}
		}

		BCryptCloseAlgorithmProvider(BcryptAlgHandle, NULL);
	}

	return Dst;
}

auto Compare(PCHAR pAddress, PCHAR Pattern, PCHAR Mask)->BOOL {

	for (; *Mask; ++pAddress, ++Pattern, ++Mask) {

		if ('x' == *Mask && *pAddress != *Pattern) {

			return FALSE;
		}
	}

	return TRUE;
}

auto SearchSignForImage(LPBYTE ImageBase, PCHAR Pattern, PCHAR Mask)->LPBYTE {

	LPBYTE Result = NULL;

	if (ImageBase != NULL) {

		PIMAGE_NT_HEADERS Headers = (PIMAGE_NT_HEADERS)(ImageBase + ((PIMAGE_DOS_HEADER)ImageBase)->e_lfanew);;

		PIMAGE_SECTION_HEADER Sections = IMAGE_FIRST_SECTION(Headers);

		for (DWORD Index = 0; Index < Headers->FileHeader.NumberOfSections; ++Index) {

			PIMAGE_SECTION_HEADER pSection = &Sections[Index];

			if (RtlEqualMemory(pSection->Name, ".text", 5) || RtlEqualMemory(pSection->Name, "PAGE", 4)) {

				Result = SearchSignForMemory(ImageBase + pSection->VirtualAddress, pSection->Misc.VirtualSize, Pattern, Mask);
				
				if (Result != NULL) {

					break;
				}
			}
		}
	}

	return Result;
}

auto SearchSignForMemory(LPBYTE MemoryBase, DWORD Length, PCHAR Pattern, PCHAR Mask)->LPBYTE {

	DWORD SignSize = (DWORD)(Length - (DWORD)(strlen(Mask)));

	for (DWORD Index = NULL; Index < SignSize; Index++) {

		PCHAR pTempAddress = (PCHAR)(&MemoryBase[Index]);

		if (Compare(pTempAddress, Pattern, Mask)) {

			return (LPBYTE)(pTempAddress);
		}
	}

	return NULL;
}

auto ResolveRelativeAddress(LPBYTE pAddress, ULONG Index)->LPBYTE {

	LPBYTE Result = NULL;

	if (pAddress != NULL) {

		Result = (LPBYTE)(pAddress + *(INT*)(pAddress + Index) + Index + 4);
	}

	return Result;
}

auto RvaToOffset(PIMAGE_NT_HEADERS64 ImageHead, ULONG RVA, ULONG FileSize)->ULONG {

	ULONG Result = NULL;

	PIMAGE_SECTION_HEADER ImageSection = IMAGE_FIRST_SECTION(ImageHead);

	USHORT NumberOfSections = ImageHead->FileHeader.NumberOfSections;

	for (USHORT i = NULL; i < NumberOfSections; i++) {

		if (ImageSection->VirtualAddress <= RVA && (ImageSection->VirtualAddress + ImageSection->Misc.VirtualSize) > RVA) {

			RVA -= ImageSection->VirtualAddress;

			RVA += ImageSection->PointerToRawData;

			Result = RVA < FileSize ? RVA : 0;

			break;
		}
		else
			ImageSection++;
	}

	return Result;
}

auto GetExportOffset(LPBYTE FileData, ULONG FileSize, LPCSTR ExportName)->ULONG {

	ULONG Result = NULL;

	PIMAGE_DOS_HEADER DosHeader = (PIMAGE_DOS_HEADER)FileData;

	PIMAGE_NT_HEADERS64 NtHeaders = (PIMAGE_NT_HEADERS64)(FileData + DosHeader->e_lfanew);

	PIMAGE_DATA_DIRECTORY ImageDataDirectory = NtHeaders->OptionalHeader.DataDirectory;

	ULONG ExportDirectoryRva = ImageDataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;

	ULONG ExportDirectorySize = ImageDataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;

	ULONG ExportDirectoryOffset = RvaToOffset(NtHeaders, ExportDirectoryRva, FileSize);

	if (ExportDirectoryOffset != NULL) {

		PIMAGE_EXPORT_DIRECTORY ExportDirectory = (PIMAGE_EXPORT_DIRECTORY)(FileData + ExportDirectoryOffset);

		ULONG NumberOfNames = ExportDirectory->NumberOfNames;

		ULONG AddressOfFunctionsOffset = RvaToOffset(NtHeaders, ExportDirectory->AddressOfFunctions, FileSize);

		if (AddressOfFunctionsOffset != NULL) {

			ULONG AddressOfNameOrdinalsOffset = RvaToOffset(NtHeaders, ExportDirectory->AddressOfNameOrdinals, FileSize);

			if (AddressOfNameOrdinalsOffset != NULL) {

				ULONG AddressOfNamesOffset = RvaToOffset(NtHeaders, ExportDirectory->AddressOfNames, FileSize);

				if (AddressOfNamesOffset != NULL) {

					PULONG AddressOfNames = (PULONG)(FileData + AddressOfNamesOffset);

					PULONG AddressOfFunctions = (PULONG)(FileData + AddressOfFunctionsOffset);

					PUSHORT AddressOfNameOrdinals = (PUSHORT)(FileData + AddressOfNameOrdinalsOffset);

					for (ULONG i = NULL; i < NumberOfNames; i++) {

						ULONG CurrentNameOffset = RvaToOffset(NtHeaders, AddressOfNames[i], FileSize);

						if (CurrentNameOffset != NULL) {

							LPCSTR CurrentName = (LPCSTR)(FileData + CurrentNameOffset);

							ULONG CurrentFunctionRva = AddressOfFunctions[AddressOfNameOrdinals[i]];

							if (CurrentFunctionRva >= ExportDirectoryRva && CurrentFunctionRva < ExportDirectoryRva + ExportDirectorySize) {

								continue;
							}
							else {

								if (!strcmp(CurrentName, ExportName)) {

									Result = RvaToOffset(NtHeaders, CurrentFunctionRva, FileSize);

									break;
								}
							}
						}
					}
				}
			}
		}
	}

	return Result;
}

auto GetTableFunByName(PSYSTEM_SERVICE_DESCRIPTOR_TABLE pServiceTableBase, LPBYTE FileData, ULONG FileSize, LPCSTR ExportName)->LPBYTE {

	LPBYTE Result = NULL;

	ULONG ExportOffset = GetExportOffset(FileData, FileSize, ExportName);

	if (ExportOffset != NULL) {

		INT32 SSDTIndex = -1;

		LPBYTE RoutineData = FileData + ExportOffset;

		for (ULONG i = NULL; i < 32 && ExportOffset + i < FileSize; i++) {

			if (RoutineData[i] == 0xB8) {

				SSDTIndex = *(INT32*)(RoutineData + i + 1);

				break;
			}
		}

		if (SSDTIndex > -1 && SSDTIndex < pServiceTableBase->NumberOfServices) {

			Result = (LPBYTE)((LPBYTE)pServiceTableBase->ServiceTableBase + (((PLONG)pServiceTableBase->ServiceTableBase)[SSDTIndex] >> 4));
		}
	}

	return Result;
}

auto GetServiceTableBase(LPBYTE pKernelBase)->LPBYTE {

	LPBYTE Result = NULL;

	if (pKernelBase != NULL) {

		LPBYTE pFound = SearchSignForImage(pKernelBase, "\x4C\x8D\x15\x00\x00\x00\x00\x4C\x8D\x1D\x00\x00\x00\x00\xF7", "xxx????xxx????x");

		if (pFound != NULL) {

			Result = ResolveRelativeAddress(pFound, 3);

		}
	}

	return Result;
}

auto GetModuleBaseForHash(UINT32 szLibHash)->LPBYTE {

	LPBYTE Result = NULL;

	if (szLibHash == 0xFF2A308D) {

		Result = DynamicData->KernelBase;
	}
	else {

		for (PLIST_ENTRY pListEntry = ((PLIST_ENTRY)(DynamicData->ModuleList))->Flink; pListEntry != (PLIST_ENTRY)(DynamicData->ModuleList); pListEntry = pListEntry->Flink) {

			PKLDR_DATA_TABLE_ENTRY pEntry = CONTAINING_RECORD(pListEntry, KLDR_DATA_TABLE_ENTRY, InLoadOrderLinks);

			if (MmIsAddressValid(pEntry->DllBase) && GetTextHashW(pEntry->BaseDllName.Buffer) == szLibHash) {

				Result = pEntry->DllBase;

				break;
			}
		}
	}

	return Result;
}

auto GetRoutineAddressForHash(LPBYTE pImageBuffer, UINT32 NameHash)->LPBYTE {

	LPBYTE Result = NULL;

	ULONG DirSize = 0;

	PIMAGE_EXPORT_DIRECTORY pExportDir = (PIMAGE_EXPORT_DIRECTORY)(RtlImageDirectoryEntryToData(pImageBuffer, TRUE, IMAGE_DIRECTORY_ENTRY_EXPORT, &DirSize));

	for (ULONG i = 0; i < pExportDir->NumberOfNames; ++i) {

		if (GetTextHashA((PCSTR)(pImageBuffer + ((PULONG)(pImageBuffer + pExportDir->AddressOfNames))[i])) == NameHash) {

			Result = (LPBYTE)(pImageBuffer + ((PULONG)(pImageBuffer + pExportDir->AddressOfFunctions))[((PUSHORT)(pImageBuffer + pExportDir->AddressOfNameOrdinals))[i]]);

			break;
		}
	}

	return Result;
}

auto LdrProcessRelocationBlock(ULONGLONG VA, ULONG SizeOfBlock, PUSHORT NextOffset, LONGLONG Difference)->LPBYTE {

	LONG Temp;

	USHORT Offset;

	PUCHAR FixupVA;

	ULONGLONG Value64;

	while (SizeOfBlock--) {

		Offset = *NextOffset & (USHORT)(0xFFF);

		FixupVA = (PUCHAR)(VA + Offset);

		switch ((*NextOffset) >> 12) {
		case 0:
		case 6:
		case 7:
		case 8: {

			break;
		}
		case 1: {

			Temp = *(PUSHORT)FixupVA << 16;

			Temp += (ULONG)Difference;

			*(PUSHORT)FixupVA = (USHORT)(Temp >> 16);

			break;
		}
		case 2: {

			Temp = *(PSHORT)FixupVA;

			Temp += (ULONG)Difference;

			*(PUSHORT)FixupVA = (USHORT)Temp;

			break;
		}
		case 3: {

			*(LONG UNALIGNED *)FixupVA += (ULONG)Difference;

			break;
		}
		case 4: {

			if (Offset & 0x2) {

				++NextOffset;

				--SizeOfBlock;

				break;
			}

			Temp = *(PUSHORT)FixupVA << 16;

			++NextOffset;

			--SizeOfBlock;

			Temp += (LONG)(*(PSHORT)NextOffset);

			Temp += (ULONG)Difference;

			Temp += 0x8000;

			*(PUSHORT)FixupVA = (USHORT)(Temp >> 16);

			break;
		}
		case 5: {

			Temp = (*(PULONG)FixupVA & 0x3FFFFFF) << 2;

			Temp += (ULONG)Difference;

			*(PULONG)FixupVA = (*(PULONG)FixupVA & ~0x3FFFFFF) | ((Temp >> 2) & 0x3FFFFFF);

			break;
		}
		case 9: {

			FixupVA = (PUCHAR)((ULONG_PTR)FixupVA & ~(15));

			Value64 = (ULONGLONG)0;

			break;
		}
		case 10: {

			*(ULONGLONG UNALIGNED *)FixupVA += Difference;

			break;
		}
		default: {

			return NULL;
		}
		}

		++NextOffset;
	}

	return (LPBYTE)(NextOffset);
}

auto LdrRelocateImageWithBias(LPBYTE pImageBuffer)->NTSTATUS {

	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)(RtlImageNtHeader(pImageBuffer));

	if (pNtHeaders != NULL) {

		ULONG Size = 0;

		PIMAGE_BASE_RELOCATION NextBlock = (PIMAGE_BASE_RELOCATION)(RtlImageDirectoryEntryToData(pImageBuffer, TRUE, IMAGE_DIRECTORY_ENTRY_BASERELOC, &Size));

		if (Size != 0) {

			ULONG SizeOfBlock = 0;

			PUSHORT NextOffset = NULL;

			while (Size) {

				SizeOfBlock = NextBlock->SizeOfBlock;

				if (SizeOfBlock != 0) {

					Size -= SizeOfBlock;

					SizeOfBlock -= sizeof(IMAGE_BASE_RELOCATION);

					SizeOfBlock /= sizeof(USHORT);

					NextOffset = (PUSHORT)((LPBYTE)NextBlock + sizeof(IMAGE_BASE_RELOCATION));

					NextBlock = (PIMAGE_BASE_RELOCATION)(LdrProcessRelocationBlock((ULONGLONG)(pImageBuffer + NextBlock->VirtualAddress), SizeOfBlock, NextOffset, (ULONGLONG)(pImageBuffer - ((PIMAGE_NT_HEADERS64)pNtHeaders)->OptionalHeader.ImageBase)));

					if (NextBlock == NULL) {

						Status = STATUS_INVALID_HANDLE;

						break;
					}
				}
				else {

					Status = STATUS_INVALID_HANDLE;

					break;
				}
			}

			Status = Status != STATUS_INVALID_HANDLE ? STATUS_SUCCESS : STATUS_UNSUCCESSFUL;
		}
	}

	return Status;
}

auto ResolveImageRefs(LPBYTE pImageBase)->NTSTATUS {

	NTSTATUS Status = STATUS_SUCCESS;

	ULONG Size = 0;

	PIMAGE_IMPORT_DESCRIPTOR pImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(RtlImageDirectoryEntryToData(pImageBase, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &Size));

	while (pImportDescriptor->Characteristics != 0) {

		LPBYTE pModule = GetModuleBaseForHash(GetTextHashA((LPCSTR)(pImageBase + pImportDescriptor->Name)));

		if (pModule != NULL) {

			PIMAGE_THUNK_DATA pNameData = ((PIMAGE_THUNK_DATA)(pImageBase + (ULONG)pImportDescriptor->OriginalFirstThunk));

			PIMAGE_THUNK_DATA pFuncData = ((PIMAGE_THUNK_DATA)(pImageBase + (ULONG)pImportDescriptor->FirstThunk));

			for (; pNameData->u1.ForwarderString; ++pNameData, ++pFuncData) {

				PIMAGE_IMPORT_BY_NAME pName = (PIMAGE_IMPORT_BY_NAME)(pImageBase + (ULONG)pNameData->u1.AddressOfData);

				LPBYTE pFunc = GetRoutineAddressForHash(pModule, GetTextHashA(pName->Name));

				if (pFunc) {

					pFuncData->u1.Function = (ULONGLONG)pFunc;
				}
			}
		}
		else
			break;

		pImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)((ULONGLONG)pImportDescriptor + sizeof(IMAGE_IMPORT_DESCRIPTOR));
	}

	return Status;
}

auto MmMapLoadDriver(LPBYTE pFileBuffer)->NTSTATUS {

	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	if (pFileBuffer != NULL) {

		PIMAGE_NT_HEADERS pImageNtHeaders = (PIMAGE_NT_HEADERS)(RtlImageNtHeader(pFileBuffer));

		if (pImageNtHeaders != NULL) {

			DynamicData->DriverBase = RtlAllocatePool(pImageNtHeaders->OptionalHeader.SizeOfImage);

			if (DynamicData->DriverBase != NULL) {

				RtlZeroMemoryEx(DynamicData->DriverBase, pImageNtHeaders->OptionalHeader.SizeOfImage);

				RtlCopyMemoryEx(DynamicData->DriverBase, pFileBuffer, pImageNtHeaders->OptionalHeader.SizeOfHeaders);

				PIMAGE_SECTION_HEADER pImageSectionHeader = (PIMAGE_SECTION_HEADER)(((PIMAGE_DOS_HEADER)pFileBuffer)->e_lfanew + sizeof(IMAGE_NT_HEADERS) + pFileBuffer);

				for (ULONG Index = 0; Index < pImageNtHeaders->FileHeader.NumberOfSections; Index++) {

					RtlCopyMemoryEx(DynamicData->DriverBase + pImageSectionHeader[Index].VirtualAddress, (LPBYTE)(pFileBuffer + pImageSectionHeader[Index].PointerToRawData), pImageSectionHeader[Index].SizeOfRawData);
				}

				if (NT_SUCCESS(LdrRelocateImageWithBias(DynamicData->DriverBase))) {
		
					if (NT_SUCCESS(ResolveImageRefs(DynamicData->DriverBase))) {

						Status = ZwWriteFileEx(L"\\SystemRoot\\System32\\GSDrv.bin", &DynamicData, sizeof(DynamicData));

						if (NT_SUCCESS(Status)) {

							HANDLE ThreadHandle = NULL;

							Status = PsCreateSystemThread(&ThreadHandle, THREAD_ALL_ACCESS, NULL, NtCurrentProcess(), NULL, (PKSTART_ROUTINE)(DynamicData->DriverBase + pImageNtHeaders->OptionalHeader.AddressOfEntryPoint), NULL);

							if (NT_SUCCESS(Status)) {

								PVOID ThreadObject = NULL;

								if (NT_SUCCESS(ObReferenceObjectByHandle(ThreadHandle, THREAD_ALL_ACCESS, NULL, KernelMode, &ThreadObject, NULL))) {

									KeWaitForSingleObject(ThreadObject, Executive, KernelMode, FALSE, NULL);

									ObfDereferenceObject(ThreadObject);
								}

								ObCloseHandle(ThreadHandle, KernelMode);
							}
						}
					}
				}
			}
		}
	}

	return Status;
}