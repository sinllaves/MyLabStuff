
#include <iostream>
#include <Windows.h>

const int MESSAGE_SIZE = 512;  // Define a constant for message size

int main()
{
    LPCWSTR pipeName = L"\\\\192.168.1.28\\pipe\\test-this-pipe";  // Define a wide string for the pipe name
    HANDLE clientPipe = NULL;  // Declare a handle for the client pipe
    BOOL isPipeRead = true;  // Initialize a boolean for pipe reading
    wchar_t message[MESSAGE_SIZE] = { 0 };  // Declare a character array to store the received message
    DWORD bytesRead = 0;  // Declare a variable to store the number of bytes read

    std::wcout << "PipeClient is connecting to pipe: " << pipeName << std::endl;  // Print a message indicating connection attempt
    clientPipe = CreateFile(pipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);  // Create a file handle for the named pipe

    while (isPipeRead) {  // Enter a loop for reading from the pipe
        isPipeRead = ReadFile(clientPipe, &message, MESSAGE_SIZE, &bytesRead, NULL);  // Read data from the pipe into the 'message' array
        std::wcout << "Received message from PipeServer: " << message;  // Print the received message
     }

    std::wcout << "Press Enter to exit...";
    std::wcin.get();

        return 0;  // Return 0 to indicate successful execution
 }