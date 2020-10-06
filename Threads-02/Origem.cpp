#include <windows.h>
#include <iostream>

int g_i = 0;
MUTEX g;

DWORD WINAPI ThreadFunc1(void* data) {
   
    for (int i = 0; i < 100; i++)
    {
        g.reservo()
        serial-read_status()
        g.libera()
    }
    return 0;
}

DWORD WINAPI ThreadFunc2(void* data) {

    for (int i = 0; i < 100; i++)
    {
        g.reservo()
        serial->envia_comando()
        //g.libera()
    }
    return 0;
}

int main() {
    int count = 0;
    HANDLE thread1 = CreateThread(NULL, 0, ThreadFunc1, NULL, 0, NULL);
    HANDLE thread2 = CreateThread(NULL, 0, ThreadFunc2, NULL, 0, NULL);
    WaitForSingleObject(thread1, -1);
    WaitForSingleObject(thread2, -1);
    std::cout << count;
    std::cout << "saindo do main";
}