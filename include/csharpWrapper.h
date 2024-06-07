#pragma once
#ifdef YOURDLL_EXPORTS
#define YOURDLL_API __declspec(dllexport)
#else
#define YOURDLL_API __declspec(dllimport)
#endif

extern "C" {
    YOURDLL_API int YourMethodWrapper(int input);
}