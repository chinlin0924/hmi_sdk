#ifndef UILIB_H
#define UILIB_H



#if defined(WIN32)

#if defined(HMIUI_LIBRARY)
#define UISHARED_EXPORT __declspec(dllexport)
#else
#define UISHARED_EXPORT __declspec(dllimport)
#endif

#else
#define UISHARED_EXPORT
#endif

#include "AppListInterface.h"
#include "UIInterface.h"


extern "C" UISHARED_EXPORT UIInterface *UILib_Init(AppListInterface *pList);

extern "C" UISHARED_EXPORT void UILib_Close();


#endif // UILIB_H