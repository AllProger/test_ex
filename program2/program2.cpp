#include <iostream>
#include <string>
#include <windows.h>
#include "../strlib/strlib.h"

using namespace std;

int main() {
    cout << "Program2 started, waiting for data...\n";

    HANDLE a = CreateNamedPipe(
        "\\\\.\\pipe\\DataPipe",
        PIPE_ACCESS_INBOUND,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1,
        1024,
        1024,
        0,
        NULL
    );

    if (a == INVALID_HANDLE_VALUE) {
        cout << "Pipe creation failed: " << GetLastError() << endl;
        return 1;
    }

    while (true) {
        cout << "Waiting for connection...\n";

        BOOL connected = ConnectNamedPipe(a, NULL);
        if (!connected && GetLastError() != ERROR_PIPE_CONNECTED) {
            cout << "Connection error: " << GetLastError() << endl;
            continue;
        }

        cout << "Client connected!\n";

        char b[1024] = {0};
        DWORD c;

        if (ReadFile(a, b, sizeof(b) - 1, &c, NULL) && c > 0) {
            string d(b);
            cout << "Received raw: " << d << endl;

            size_t e = d.find('|');

            if (e != string::npos) {
                string f = d.substr(0, e);
                int g = stoi(d.substr(e + 1));

                cout << "String: " << f << endl;
                cout << "Sum: " << g << endl;

                bool h = analyzeLength(f.c_str());
                cout << "Analysis: " << (h ? "TRUE" : "FALSE") << endl;
                cout << endl;
            }
        } else {
            cout << "Read error or no data\n";
        }

        DisconnectNamedPipe(a);
        cout << "Disconnected, waiting for next...\n\n";
    }

    CloseHandle(a);
    return 0;
}
