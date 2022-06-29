

#include <Python.h>
#if defined(HAVE_SNPRINTF)  
#undef HAVE_SNPRINTF        
#endif
#include <SDL_ttf.h>



#define FONT_INIT_CHECK() \
    if(!(*(int*)PyFONT_C_API[2])) \
        return RAISE(pgExc_SDLError, "font system not initialized")



#define PYGAMEAPI_FONT_FIRSTSLOT 0
#define PYGAMEAPI_FONT_NUMSLOTS 3
typedef struct {
  PyObject_HEAD
  TTF_Font* font;
  PyObject* weakreflist;
} PyFontObject;
#define PyFont_AsFont(x) (((PyFontObject*)x)->font)

#ifndef PYGAMEAPI_FONT_INTERNAL
#define PyFont_Check(x) ((x)->ob_type == (PyTypeObject*)PyFONT_C_API[0])
#define PyFont_Type (*(PyTypeObject*)PyFONT_C_API[0])
#define PyFont_New (*(PyObject*(*)(TTF_Font*))PyFONT_C_API[1])


#define import_pygame_font() \
    _IMPORT_PYGAME_MODULE(font, FONT, PyFONT_C_API)

static void* PyFONT_C_API[PYGAMEAPI_FONT_NUMSLOTS] = {NULL};
#endif

