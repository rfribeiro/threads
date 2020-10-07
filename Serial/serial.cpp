#include <windows.h>
#include <cstring>
#include <atlstr.h>
#include <iostream>

#define PRINTER_PORT "\\\\.\\COM6"

bool WriteComPort(const char* PortSpecifier, char* data, int len)
{
    DCB dcb = { 0 };
    DWORD byteswritten;
    HANDLE hPort = CreateFileA(
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
    dcb.BaudRate = CBR_9600;     //9600 Baud
    dcb.ByteSize = 8;            //8 data bits
    dcb.Parity = NOPARITY;      //no parity
    dcb.StopBits = ONESTOPBIT;  //1 stop
    if (!SetCommState(hPort, &dcb))
        return false;

    bool retVal = WriteFile(hPort, data, len, &byteswritten, NULL);

    if (len == byteswritten)
    {
        std::cout << "command write with success" << std::endl;
    }
    //ReadFile()
    CloseHandle(hPort); //close the handle
    return retVal;
}


int main() {
       
    char data[20];

    // init default
    data[0] = 0x1B;
    data[1] = '@';

    // set mode (BEMA)
    data[2] = 0x1D;
    data[3] = 0xf9;
    data[4] = 0x35;
    data[5] = 0x00;
    WriteComPort(PRINTER_PORT, data, 6);

    // send data
    strcpy_s(data, "teste impressão");
    WriteComPort(PRINTER_PORT, data, 15);

    // cut paper
    data[0] = 0x1B;
    data[1] = 0x69;
    WriteComPort(PRINTER_PORT, data, 2);

    return 0;
}