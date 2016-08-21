#include "os.h"
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#ifdef ASSUME_ANDROID
#include <GL/glew.h>
#else
#include ForWindows(<GL/glew.h>) ForMac(<OpenGL/gl3.h>) ForMobile(<GLES2/gl2.h>)
#endif