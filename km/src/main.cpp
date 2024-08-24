#include <ntifs.h>

extern "C" {
	NTKERNELAPI NTSTATUS IoCreateDriver(
		PUNICODE_STRING DriverName,
		PDRIVER_INITIALIZE InitializationFunction
	);

	NTKERNELAPI NTSTATUS MmCopyVirtualMemory(
		PEPROCESS SourceProcess, PVOID SourceAddress,
		PEPROCESS TargetProcess, PVOID TargetAddress,
		SIZE_T BufferSize, KPROCESSOR_MODE PreviousMode,
		PSIZE_T ReturnSize
	);
}

namespace driver {
	namespace codes {
		constexpr ULONG attach = CTL_CODE(
			FILE_DEVICE_UNKNOWN, 0x696,
			METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
		
		constexpr ULONG read = CTL_CODE(
			FILE_DEVICE_UNKNOWN, 0x697,
			METHOD_BUFFERED, FILE_SPECIAL_ACCESS);

		constexpr ULONG write = CTL_CODE(
			FILE_DEVICE_UNKNOWN, 0x698,
			METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
	}

	struct Requst {
		HANDLE process_id;
		PVOID trget;
		PVOID buffer;
		SIZE_T size;
		SIZE_T return_size;
	};
}

void debug_print(PCSTR text) {
#ifndef DEBUG
	UNREFERENCED_PARAMETER(text);
#else
	KdPrintEx(DPFLTR_IHVDRIVER_ID, DPELTR_INFO_LEVEL, text);
#endif
}

NTSTATUS driver_main(PDRIVER_OBJECT driver_object, PUNICODE_STRING registry_path) {
	return STATUS_SUCCESS;
}

NTSTATUS DriverEntry() {
	debug_print("[*] Hello from km");
	
	UNICODE_STRING driver_name = {};
	RtlInitUnicodeString(&driver_name, L"\\Driver\\SexyDriver");


	return IoCreateDriver(&driver_name, &driver_main);
}