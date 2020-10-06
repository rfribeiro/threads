#include <windows.h>
#include <iostream>

DWORD WINAPI ThreadFunc(void* data) {
    for (int i = 0; i < 100; i++)
    {
        std::cout << i << std::endl;
    }
    return 0;
}

DWORD WINAPI ThreadFunc2(void* data) {
    for (int i = 100; i < 200; i++)
    {
        std::cout << i << std::endl;
    }
    return 0;
}

DWORD WINAPI ThreadFunc3(void* data) {
    for (int i = 200; i < 300; i++)
    {
        std::cout << i << std::endl;
    }
    return 0;
}
int main() {
    HANDLE thread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
    
    HANDLE thread2 = CreateThread(NULL, 0, ThreadFunc2, NULL, 0, NULL);
    
    HANDLE thread3 = CreateThread(NULL, 0, ThreadFunc3, NULL, 0, NULL);
    
    //WaitForSingleObject(thread, INFINITE);
    //WaitForSingleObject(thread2, INFINITE);
    //WaitForSingleObject(thread3, INFINITE);
    HANDLE lpHandles[3];
    lpHandles[0] = thread;
    lpHandles[1] = thread2;
    lpHandles[2] = thread3;
    WaitForMultipleObjects(3, lpHandles, TRUE, INFINITE);
    
    std::cout << "saindo do main";
}