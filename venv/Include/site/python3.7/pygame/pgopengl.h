#if !defined(PGOPENGL_H)
#define PGOPENGL_H



#if defined(_WIN32)
#define GL_APIENTRY __stdcall
#else
#define GL_APIENTRY
#endif

typedef void (GL_APIENTRY *GL_glReadPixels_Func)(int, int, int, int, unsigned int, unsigned int, void*);

#endif
