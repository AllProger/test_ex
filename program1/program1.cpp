#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <cctype>
#include <algorithm>
#include <windows.h>
#include "../strlib/strlib.h"

using namespace std;

queue<string> a;
mutex b;
condition_variable c;
bool d = true;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    thread e([&]() {
        string f;
        while (d) {
            cout << "Vvedite stroku iz cifr (do 64): ";
            getline(cin, f);
            if (f == "exit") {
                d = false;
                c.notify_one();
                break;
            }
            if (f.length() > 64 || !all_of(f.begin(), f.end(), ::isdigit)) {
                cout << "Oshibka!\n";
                continue;
            }
            char* g = new char[65];
            strcpy_s(g, 65, f.c_str());
            sortStr(g);
            lock_guard<mutex> h(b);
            a.push(g);
            c.notify_one();
            delete[] g;
        }
    });

    thread i([&]() {
        while (d) {
            unique_lock<mutex> h(b);
            c.wait(h, [] { return !a.empty() || !d; });
            if (!d && a.empty()) break;

            string j = a.front();
            a.pop();
            h.unlock();

            cout << "Obrabotano: " << j << endl;
            int k = calculateSum(j.c_str());
            cout << "Summa: " << k << endl;

            HANDLE l = CreateFile(
                "\\\\.\\pipe\\DataPipe",
                GENERIC_WRITE,
                0,
                NULL,
                OPEN_EXISTING,
                0,
                NULL
            );

            if (l != INVALID_HANDLE_VALUE) {
                string m = j + "|" + to_string(k);
                DWORD n;
                WriteFile(l, m.c_str(), m.length() + 1, &n, NULL);
                CloseHandle(l);
            }
        }
    });

    e.join();
    i.join();

    return 0;
}
