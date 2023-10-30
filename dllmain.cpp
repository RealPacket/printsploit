// dllmain.cpp : Defines the entry point for the DLL application.

#include <Windows.h>
#include <string>
#include <thread>
#include "offsets.h"
#undef ERROR


enum class ELogType {
    PRINT,
    INFO,
    WARN,
    ERROR
};

#define offset(x) x - 0x400000 + (DWORD)GetModuleHandleA(NULL)

using print = void(ELogType logType, const char* message);
const ELogType messageLogType = ELogType::INFO;
const auto printFunc = reinterpret_cast<print*>(offset(Offsets::rPrint));
const char* messageToPrint = R"(Holy moly new print exploit real 2023 download!
(also no it's not fake)
(I love print exploits)
)";

void entry() {
    const auto printFunc = reinterpret_cast<print*>(offset(Offsets::rPrint));

    printFunc(ELogType::INFO, messageToPrint);

}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        std::thread(entry).detach();
    }

    return TRUE;
}

// old code not working lol
/*
#include <Windows.h>
#include <string>
#include <thread>
#include "offsets.h"
#include <chrono>
// macro moment
#undef ERROR

#define offset(x) (x - 0x400000 + (DWORD)GetModuleHandle(NULL))

enum class ELogType {
    PRINT,
    INFO,
    WARN,
    ERROR
};

using print = void(ELogType logType, const char* message);
const ELogType messageLogType = ELogType::INFO;
const auto printFunc = reinterpret_cast<print*>(offset(Offsets::rPrint));
const char* messageToPrint = R"(holy moly new print exploit real 2023 download)";
HMODULE mod;
FILE* stdoutFile;
// FILE* stdinFile;

void entry() {
    printf_s("Entry thread called! Will print %s in console.\n", messageToPrint);
    printFunc(messageLogType, messageToPrint);
    printf_s("Printed %s to the console!\n", messageToPrint);
    printf_s("Will exit in 10 seconds.\n");
    std::this_thread::sleep_for(std::chrono::seconds(10));
    FreeLibraryAndExitThread(mod, FALSE);
}

BOOL APIENTRY DllMain(HMODULE m, DWORD reasonForCall)
{
    mod = m;
    AllocConsole();
    freopen_s(&stdoutFile, "CONOUT$", "w", stdout);
    std::thread(entry).detach();
    printf_s("Created entry thread!\n");
    // freopen_s(&stdinFile, "CONIN", "w", stdin);
    return TRUE;
}
*/