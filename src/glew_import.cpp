#include "os.h"
#if OnWindows || defined(ASSUME_ANDROID)
#define GLEW_STATIC
#include "../lib/glew.c.code"
#endif