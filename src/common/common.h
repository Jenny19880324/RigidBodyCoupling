#pragma once

#ifdef DLL_EXPORT
#define GL_API __declspec(dllexport)
#endif

#ifdef DLL_IMPORT
#define GL_API __declspec(dllimport)
#endif

#ifdef STATIC_LIB
#define GL_API
#endif


// STL
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <iomanip>
#include <stdio.h>
