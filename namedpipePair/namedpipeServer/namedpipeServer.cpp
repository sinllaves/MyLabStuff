
#include <Windows.h>
#include <iostream>

int main() {
    LPCWSTR pipeName = L"\\\\.\\pipe\\test-this-pipe";  // Define the named pipe path
    LPVOID pipeBuffer = NULL;  // Initialize a buffer pointer
    HANDLE serverPipe;  // Declare a handle for the server pipe
    DWORD readBytes = 0;  // Initialize a variable to store the number of bytes read
    DWORD readBuffer = 0;  // Initialize a read buffer variable
    int err = 0;  // Initialize an error variable
    BOOL isPipeConnected;  // Initialize a flag for pipe connection
    BOOL isPipeOpen;  // Initialize a flag for pipe openness
    wchar_t message[] = L" ! Important Data from pipeServer: User:Cat Password:crunchies";  // Define a message to send to the client
    DWORD messageLength = lstrlen(message) * sizeof(wchar_t);  // Calculate the message length in bytes
    DWORD bytesWritten = 0;  // Initialize a variable to store the number of bytes written

    std::wcout << " Created named pipe: " << pipeName << std::endl;  // Print a message indicating named pipe creation
    serverPipe = CreateNamedPipe(pipeName, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE, 1, 2048, 2048, 0, NULL);  // Create the named pipe

    std::wcout << "Waiting for PipeClient..." << std::endl;

    isPipeConnected = ConnectNamedPipe(serverPipe, NULL);  // Wait for a client to connect to the named pipe
    if (isPipeConnected) {
        std::wcout << "PipeClient has connected to: " << pipeName << std::endl;  // Print a message when a client connects
    }
    
    std::wcout << "Sending message to PipeClient: " << message << std::endl;
    WriteFile(serverPipe, message, messageLength, &bytesWritten, NULL);
    
    std::wcout << "Press Enter to exit...";
    std::wcin.get();

    return 0;  // Return 0 to indicate successful execution
}