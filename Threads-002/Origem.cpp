#include <windows.h>
#include <iostream>

DWORD WINAPI ThreadFunc(void* data) {
    int valor = *((int*)data);
    for (int i = 0; i < valor; i++)
    {
        std::cout << i << std::endl;
    }
    return 0;
}

int main() {
    int* pDataArray = (int*)malloc(sizeof(int));
    std::cout << "enter value: ";
    std::cin >> *pDataArray;
    HANDLE thread = CreateThread(NULL, 0, ThreadFunc, (void*)pDataArray, 0, NULL);
    if (thread) {
        // Optionally do stuff, such as wait on the thread.
    }
    WaitForSingleObject(thread, -1);
    free(pDataArray);
    std::cout << "saindo do main";
}