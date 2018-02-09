#ifndef __MAIN_H__
#define __MAIN_H__

#pragma pack(push,1)

#include <windows.h>

typedef void(*pPluginFUNC)(int nCount, float *pfOut, float *pfIn1, float *pfIn2, float *pfIn3);

typedef struct tagPluginTCalcFuncInfo
{
  unsigned short nFuncMark;
  pPluginFUNC    pCallFunc;
} PluginTCalcFuncInfo;

#ifdef __cplusplus
extern "C"
{
#endif

BOOL __declspec(dllexport) RegisterTdxFunc(PluginTCalcFuncInfo **pInfo);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // __MAIN_H__
