#include <iostream>
#include <cstring>
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <cctype>
#include <algorithm>
#include <condition_variable>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../strlib/strlib.h"

using namespace std;

queue<string> a;
mutex b;
condition_variable c;
bool d = true;

int main() {
    mkfifo("/tmp/DataPipe", 0666);

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
            strcpy(g, f.c_str());
            sortStr(g);
            {
                lock_guard<mutex> h(b);
                a.push(g);
            }
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

            int l = open("/tmp/DataPipe", O_WRONLY);
            if (l != -1) {
                string m = j + "|" + to_string(k) + "\n";
                write(l, m.c_str(), m.length());
                close(l);
            }
        }
    });

    e.join();
    i.join();

    unlink("/tmp/DataPipe");

    return 0;
}
