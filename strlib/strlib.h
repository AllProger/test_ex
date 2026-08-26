#ifndef __STRLIB_H__
#define __STRLIB_H__

#ifdef BUILD_DLL
    #define DLL_EXPORT __attribute__((visibility("default")))
#else
    #define DLL_EXPORT
#endif

#ifdef __cplusplus
extern "C"
{
#endif

void DLL_EXPORT sortStr(char* a);
int DLL_EXPORT calculateSum(const char* a);
bool DLL_EXPORT analyzeLength(const char* a);

#ifdef __cplusplus
}
#endif

#endif
