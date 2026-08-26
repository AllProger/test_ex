#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>
#include "../strlib/strlib.h"

using namespace std;

int main() {
    cout << "Program2 started, waiting for data...\n";

    mkfifo("/tmp/DataPipe", 0666);

    while (true) {
        cout << "Waiting for connection...\n";

        int a = open("/tmp/DataPipe", O_RDONLY);
        if (a == -1) {
            cout << "Pipe opening failed" << endl;
            continue;
        }

        cout << "Client connected!\n";

        char b[1024] = {0};
        ssize_t c = read(a, b, sizeof(b) - 1);

        if (c > 0) {
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

        close(a);
        cout << "Disconnected, waiting for next...\n\n";
    }

    unlink("/tmp/DataPipe");
    return 0;
}
