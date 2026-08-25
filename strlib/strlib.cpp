#include "strlib.h"
#include <algorithm>
#include <string>
#include <cctype>

using namespace std;

void DLL_EXPORT sortStr(char* a)
{
    if (!a) return;

    string b(a);
    sort(b.begin(), b.end(), greater<char>());

    string c;
    for (char d : b) {
        if (isdigit(d) && ((d - '0') % 2 == 0)) {
            c += "KB";
        } else {
            c += d;
        }
    }

    strcpy_s(a, c.length() + 1, c.c_str());
}

int DLL_EXPORT calculateSum(const char* a)
{
    if (!a) return 0;

    int b = 0;
    for (int c = 0; a[c] != '\0'; c++) {
        if (isdigit(a[c])) {
            b += (a[c] - '0');
        }
    }
    return b;
}

bool DLL_EXPORT analyzeLength(const char* a)
{
    if (!a) return false;

    int b = strlen(a);
    return (b > 2 && b % 32 == 0);
}

BOOL APIENTRY DllMain(HINSTANCE a, DWORD b, LPVOID c)
{
    switch (b)
    {
        case DLL_PROCESS_ATTACH:
            break;
        case DLL_PROCESS_DETACH:
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
    }
    return TRUE;
}
