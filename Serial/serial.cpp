#include <windows.h>
#include <cstring>
#include <atlstr.h>

bool WriteComPort(CString PortSpecifier, CString data)
{
    DCB dcb = { 0 };
    DWORD byteswritten;
    HANDLE hPort = CreateFile(
        PortSpecifier,
        GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );
    if (!GetCommState(hPort, &dcb))
        return false;
    dcb.BaudRate = CBR_9600; //9600 Baud
    dcb.ByteSize = 8; //8 data bits
    dcb.Parity = NOPARITY; //no parity
    dcb.StopBits = ONESTOPBIT; //1 stop
    if (!SetCommState(hPort, &dcb))
        return false;
    bool retVal = WriteFile(hPort, data, 1, &byteswritten, NULL);
    //ReadFile()
    CloseHandle(hPort); //close the handle
    return retVal;
}

int main() {
       
    CString data;
    data.Format(_T("%X"), 0xff);
    WriteComPort(L"\\\\.\\COM3", "teste");

    return 0;
}