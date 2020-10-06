#include <windows.h>
#include <iostream>

HANDLE g_mutexCounter;
int g_count = 0;

DWORD WINAPI ThreadFunc(void* data) {
    for (int i = 0; i < 100000; i++)
    {
        WaitForSingleObject(g_mutexCounter, INFINITE); //LOCK
        g_count = g_count + 1;
        //ReleaseMutex(g_mutexCounter); // UNLOCK
    }
    return 0;
}

DWORD WINAPI ThreadFunc2(void* data) {
    for (int i = 0; i < 100000; i++)
    {
        WaitForSingleObject(g_mutexCounter, INFINITE);
        g_count = g_count + 1;
        //ReleaseMutex(g_mutexCounter);
    }
    return 0;
}

DWORD WINAPI ThreadFunc3(void* data) {
    for (int i = 0; i < 100000; i++)
    {
        WaitForSingleObject(g_mutexCounter, INFINITE);
        g_count = g_count + 1;
        ReleaseMutex(g_mutexCounter);
    }
    return 0;
}

int main() {
    g_mutexCounter = CreateMutex(NULL, FALSE, NULL);

    HANDLE thread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
    HANDLE thread2 = CreateThread(NULL, 0, ThreadFunc2, NULL, 0, NULL);
    HANDLE thread3 = CreateThread(NULL, 0, ThreadFunc3, NULL, 0, NULL);

    HANDLE lpHandles[3];
    lpHandles[0] = thread;
    lpHandles[1] = thread2;
    lpHandles[2] = thread3;
    WaitForMultipleObjects(3, lpHandles, TRUE, INFINITE);

    std::cout << "Contador: " << g_count << std::endl;
    std::cout << "saindo do main";
}