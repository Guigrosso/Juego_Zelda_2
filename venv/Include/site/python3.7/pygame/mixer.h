
#include <Python.h>
#include <SDL_mixer.h>
#include <structmember.h>


#define MIXER_INIT_CHECK() \
    if(!SDL_WasInit(SDL_INIT_AUDIO)) \
        return RAISE(pgExc_SDLError, "mixer not initialized")


#define PYGAMEAPI_MIXER_FIRSTSLOT 0
#define PYGAMEAPI_MIXER_NUMSLOTS 7
typedef struct {
  PyObject_HEAD
  Mix_Chunk *chunk;
  Uint8 *mem;
  PyObject *weakreflist;
} pgSoundObject;
typedef struct {
  PyObject_HEAD
  int chan;
} pgChannelObject;
#define pgSound_AsChunk(x) (((pgSoundObject*)x)->chunk)
#define pgChannel_AsInt(x) (((pgChannelObject*)x)->chan)

#ifndef PYGAMEAPI_MIXER_INTERNAL
#define pgSound_Check(x) ((x)->ob_type == (PyTypeObject*)pgMIXER_C_API[0])
#define pgSound_Type (*(PyTypeObject*)pgMIXER_C_API[0])
#define pgSound_New (*(PyObject*(*)(Mix_Chunk*))pgMIXER_C_API[1])
#define pgSound_Play (*(PyObject*(*)(PyObject*, PyObject*))pgMIXER_C_API[2])
#define pgChannel_Check(x) ((x)->ob_type == (PyTypeObject*)pgMIXER_C_API[3])
#define pgChannel_Type (*(PyTypeObject*)pgMIXER_C_API[3])
#define pgChannel_New (*(PyObject*(*)(int))pgMIXER_C_API[4])
#define pgMixer_AutoInit (*(PyObject*(*)(PyObject*, PyObject*))pgMIXER_C_API[5])
#define pgMixer_AutoQuit (*(void(*)(void))pgMIXER_C_API[6])

#define import_pygame_mixer() \
    _IMPORT_PYGAME_MODULE(mixer, MIXER, pgMIXER_C_API)

static void* pgMIXER_C_API[PYGAMEAPI_MIXER_NUMSLOTS] = {NULL};
#endif

