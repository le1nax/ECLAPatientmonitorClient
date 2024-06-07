#include "include/DisplayApplication.h"
#pragma managed
#include <memory>
#include <iostream>
#include <windows.h>
#include <iostream>
#include "ParseECLA/IdManager.h"
#include "ParseECLA/LRUCache.hpp"


int main() {
    std::unique_ptr<DisplayApplication> application = std::make_unique<DisplayApplication>();
	application->run();
    return 0;
}

//typedef void(__stdcall *OtherMethodFunction)();
//	typedef void(__stdcall *MainFunction)(const char* arg);

// int main() {
//     HMODULE hModule = LoadLibrary(TEXT("C:/Repositories/C#/ClassLibrary1/bin/Release/net8.0/ClassLibrary1.dll")); 
//     if (hModule != NULL) {
//         OtherMethodFunction otherMethod = (OtherMethodFunction)GetProcAddress(hModule, "ClassLibrary1.MyClass.MyMethod");
//         //MainFunction mainFunc = (MainFunction)GetProcAddress(hModule, "MyCSharpLibrary.Example.OtherMethod");
        
//         if (otherMethod != NULL && mainFunc != NULL) {
//             otherMethod();
//             mainFunc("World");
//         }
//         else {
// 			DWORD dwError = GetLastError();
// 			LPVOID lpMsgBuf;
// 			FormatMessage(
//             FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
//             NULL,
//             dwError,
//             MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//             (LPTSTR)&lpMsgBuf,
//             0,
//             NULL
// 			);
//             std::cout << "Failed to get function pointers. Error: " << (LPCTSTR)lpMsgBuf << std::endl;
//         }
//         FreeLibrary(hModule);
// 	}
//     else{
//      DWORD dwError = GetLastError();
//         LPVOID lpMsgBuf;
//         FormatMessage(
//             FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
//             NULL,
//             dwError,
//             MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//             (LPTSTR)&lpMsgBuf,
//             0,
//             NULL
//         );
//         std::cout << "Failed to load library. Error: " << (LPCTSTR)lpMsgBuf << std::endl;
//         LocalFree(lpMsgBuf);
    
// 	}
// 	// if (hModule != NULL) {
//     //     // Get DOS header
//     //     IMAGE_DOS_HEADER dosHeader;
//     //     if (ReadProcessMemory(hModule, NULL, &dosHeader, sizeof(dosHeader), NULL)) {
//     //         // Check if DOS signature is valid
//     //         if (dosHeader.e_magic == IMAGE_DOS_SIGNATURE) {
//     //             // Calculate the address of the IMAGE_NT_HEADERS
//     //             DWORD ntHeaderOffset = dosHeader.e_lfanew;
//     //             IMAGE_NT_HEADERS ntHeaders;
//     //             if (ReadProcessMemory(hModule, (LPVOID)(hModule + ntHeaderOffset), &ntHeaders, sizeof(ntHeaders), NULL)) {
//     //                 // Check if NT signature is valid
//     //                 if (ntHeaders.Signature == IMAGE_NT_SIGNATURE) {
//     //                     // Get the address of the export directory
//     //                     PIMAGE_DATA_DIRECTORY pExportDir = &ntHeaders.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
//     //                     if (pExportDir->Size > 0) {
//     //                         PIMAGE_EXPORT_DIRECTORY pExportDirectory = (PIMAGE_EXPORT_DIRECTORY)((DWORD_PTR)hModule + pExportDir->VirtualAddress);

//     //                         // Get the addresses of the exported functions
//     //                         DWORD* pFunctions = (DWORD*)((DWORD_PTR)hModule + pExportDirectory->AddressOfFunctions);
//     //                         WORD* pOrdinals = (WORD*)((DWORD_PTR)hModule + pExportDirectory->AddressOfNameOrdinals);
//     //                         DWORD* pNames = (DWORD*)((DWORD_PTR)hModule + pExportDirectory->AddressOfNames);

//     //                         // Print the exported function names
//     //                         std::cout << "Exported Functions:" << std::endl;
//     //                         for (DWORD i = 0; i < pExportDirectory->NumberOfNames; ++i) {
//     //                             // Get the name of the exported function
//     //                             char* functionName = (char*)((DWORD_PTR)hModule + pNames[i]);

//     //                             // Print the function name
//     //                             std::cout << functionName << std::endl;
//     //                         }
//     //                     }
//     //                 } else {
//     //                     std::cout << "Invalid NT signature." << std::endl;
//     //                 }
//     //             } else {
//     //                 std::cout << "Failed to read NT headers." << std::endl;
//     //             }
//     //         } else {
//     //             std::cout << "Invalid DOS signature." << std::endl;
//     //         }
//     //     } else {
//     //         std::cout << "Failed to read DOS header." << std::endl;
//     //     }

//     //     FreeLibrary(hModule);
//     // } else {
//     //     DWORD dwError = GetLastError();
//     //     LPVOID lpMsgBuf;
//     //     FormatMessage(
//     //         FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
//     //         NULL,
//     //         dwError,
//     //         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//     //         (LPTSTR)&lpMsgBuf,
//     //         0,
//     //         NULL
//     //     );
//     //     std::cout << "Failed to load library. Error: " << (LPCTSTR)lpMsgBuf << std::endl;
//     //     LocalFree(lpMsgBuf);
//     // }
// 	return 0;
// }
