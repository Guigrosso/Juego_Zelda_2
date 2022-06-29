
#if defined(_POSIX_C_SOURCE)
#undef _POSIX_C_SOURCE
#endif

#include <Python.h>


#define PYGAME_SCRAP_TEXT "text/plain"
#define PYGAME_SCRAP_BMP "image/bmp"
#define PYGAME_SCRAP_PPM "image/ppm"
#define PYGAME_SCRAP_PBM "image/pbm"


typedef enum
{
    SCRAP_CLIPBOARD,
    SCRAP_SELECTION 
} ScrapClipType;

#define PYGAME_SCRAP_INIT_CHECK() \
    if(!pygame_scrap_initialized()) \
        return (PyErr_SetString (pgExc_SDLError, \
                                 "scrap system not initialized."), NULL)


extern int
pygame_scrap_init (void);


extern int
pygame_scrap_lost (void);


extern int
pygame_scrap_put (char *type, int srclen, char *src);


extern char*
pygame_scrap_get (char *type, unsigned long *count);

extern char**
pygame_scrap_get_types (void);

extern int
pygame_scrap_contains (char *type);
