#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <algorithm>
#include <format>

// enumerate all processes and check the name
int find_process(const char* process_name) {
    PROCESSENTRY32 entry = { };
    entry.dwSize = sizeof(PROCESSENTRY32);

    // snap all processes currently runing
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (!Process32First(snapshot, &entry))
        throw std::exception("Failed to create PROCESSENTRY32W of first process in snapshot!");

    int pid = -1;

    do {
        if (strcmp(process_name, entry.szExeFile) == 0)
            pid = entry.th32ProcessID;

    } while (Process32Next(snapshot, &entry));

    CloseHandle(snapshot);

    if (pid == -1)
        throw std::exception("Failed to find process.");
    else
        return pid;
}

int main(int argc, char* argv[]) {
    try {
        const char* arg = argv[1];
        std::cout << std::format("[{}] \"{}\"", find_process(arg), arg);
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}