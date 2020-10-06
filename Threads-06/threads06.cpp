#include <windows.h>
#include <iostream>
#include <queue>

int g_saldo = 0;
std::queue<int> g_queue;
HANDLE g_mutexCounter;

DWORD WINAPI Produtor(void* data) {
    int* valor = (int*)data;

    RegOpenKeyEx(HKEY_CURRENT_USER, L"Control Panel\Desktop", KEY_READ,NULL,NULL);
    RegQueryValueExW()
    for (int i = 0; i < 100; i++)
    {
        WaitForSingleObject(g_mutexCounter, INFINITE);
        
        std::cout << "Inserindo " << *valor << " na fila" << std::endl;
        g_queue.push(*valor);
        ReleaseMutex(g_mutexCounter);
        Sleep(1000);
    }
    return 0;
}

DWORD WINAPI Consumidor(void* data) {
    while (true)
    {
        WaitForSingleObject(g_mutexCounter, INFINITE);
        if (!g_queue.empty())
        {
            g_saldo = g_saldo + g_queue.front();
            std::cout << "Removendo " << g_queue.front() << " da fila" << std::endl;
            g_queue.pop();
        }
        Sleep(100);
        ReleaseMutex(g_mutexCounter);
    }
    return 0;
}

DWORD WINAPI Imprimir(void* data) {
    while (true)
    {
        WaitForSingleObject(g_mutexCounter, INFINITE);
        std::cout << "Imprimir Saldo: " << g_saldo << std::endl;
        Sleep(1000);
        ReleaseMutex(g_mutexCounter);
    }
    return 0;
}

int main() {
    int soma = 10;
    int subtrai = -10;
    g_mutexCounter = CreateMutex(NULL, FALSE, NULL);

    HANDLE thread = CreateThread(NULL, 0, Produtor, &soma, 0, NULL);
    HANDLE thread2 = CreateThread(NULL, 0, Produtor, &soma, 0, NULL);
    HANDLE thread3 = CreateThread(NULL, 0, Produtor, &subtrai, 0, NULL);
    HANDLE thread4 = CreateThread(NULL, 0, Produtor, &subtrai, 0, NULL);

    HANDLE thread5 = CreateThread(NULL, 0, Consumidor, NULL, 0, NULL);
    HANDLE thread6 = CreateThread(NULL, 0, Consumidor, NULL, 0, NULL);

    HANDLE thread7 = CreateThread(NULL, 0, Imprimir, NULL, 0, NULL);

    HANDLE lpHandles[7];
    lpHandles[0] = thread;
    lpHandles[1] = thread2;
    lpHandles[2] = thread3;
    lpHandles[3] = thread4;

    lpHandles[4] = thread5;
    lpHandles[5] = thread6;
    lpHandles[6] = thread7;

    WaitForMultipleObjects(7, lpHandles, TRUE, INFINITE);

    std::cout << "Saldo Final: " << g_saldo << std::endl;
    std::cout << "saindo do main";
}