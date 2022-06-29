

#ifndef _PYGAME_H
#define _PYGAME_H


#if defined(HAVE_SNPRINTF) 
#undef HAVE_SNPRINTF       
#endif

// This must be before all else
#if defined(__SYMBIAN32__) && defined(OPENC)
#include <sys/types.h>

#if defined(__WINS__)
void *
_alloca(size_t size);
#define alloca _alloca
#endif
#endif

#define PG_STRINGIZE_HELPER(x) #x
#define PG_STRINGIZE(x) PG_STRINGIZE_HELPER(x)
#define PG_WARN(desc) message(__FILE__ "(" PG_STRINGIZE(__LINE__) "): WARNING: " #desc)

#if defined(_POSIX_C_SOURCE)
#undef _POSIX_C_SOURCE
#endif

#include <Python.h>

#define PG_MAJOR_VERSION 1
#define PG_MINOR_VERSION 9
#define PG_PATCH_VERSION 6
#define PG_VERSIONNUM(MAJOR, MINOR, PATCH) (1000*(MAJOR) + 100*(MINOR) + (PATCH))
#define PG_VERSION_ATLEAST(MAJOR, MINOR, PATCH)                             \
    (PG_VERSIONNUM(PG_MAJOR_VERSION, PG_MINOR_VERSION, PG_PATCH_VERSION) >= \
     PG_VERSIONNUM(MAJOR, MINOR, PATCH))

#if defined(Py_CAPSULE_H)
#define PG_HAVE_CAPSULE 1
#else
#define PG_HAVE_CAPSULE 0
#endif
#if defined(Py_COBJECT_H)
#define PG_HAVE_COBJECT 1
#else
#define PG_HAVE_COBJECT 0
#endif
#if !PG_HAVE_CAPSULE
#define PyCapsule_New(ptr, n, dfn) PyCObject_FromVoidPtr(ptr, dfn)
#define PyCapsule_GetPointer(obj, n) PyCObject_AsVoidPtr(obj)
#define PyCapsule_CheckExact(obj) PyCObject_Check(obj)
#endif

#if !defined(PyBUF_SIMPLE)
typedef struct bufferinfo {
    void *buf;
    PyObject *obj;
    Py_ssize_t len;
    Py_ssize_t itemsize;
    int readonly;
    int ndim;
    char *format;
    Py_ssize_t *shape;
    Py_ssize_t *strides;
    Py_ssize_t *suboffsets;
    void *internal;
} Py_buffer;

#define PyBUF_SIMPLE 0
#define PyBUF_WRITABLE 0x0001
#define PyBUF_WRITEABLE PyBUF_WRITABLE
#define PyBUF_FORMAT 0x0004
#define PyBUF_ND 0x0008
#define PyBUF_STRIDES (0x0010 | PyBUF_ND)
#define PyBUF_C_CONTIGUOUS (0x0020 | PyBUF_STRIDES)
#define PyBUF_F_CONTIGUOUS (0x0040 | PyBUF_STRIDES)
#define PyBUF_ANY_CONTIGUOUS (0x0080 | PyBUF_STRIDES)
#define PyBUF_INDIRECT (0x0100 | PyBUF_STRIDES)

#define PyBUF_CONTIG (PyBUF_ND | PyBUF_WRITABLE)
#define PyBUF_CONTIG_RO (PyBUF_ND)

#define PyBUF_STRIDED (PyBUF_STRIDES | PyBUF_WRITABLE)
#define PyBUF_STRIDED_RO (PyBUF_STRIDES)

#define PyBUF_RECORDS (PyBUF_STRIDES | PyBUF_WRITABLE | PyBUF_FORMAT)
#define PyBUF_RECORDS_RO (PyBUF_STRIDES | PyBUF_FORMAT)

#define PyBUF_FULL (PyBUF_INDIRECT | PyBUF_WRITABLE | PyBUF_FORMAT)
#define PyBUF_FULL_RO (PyBUF_INDIRECT | PyBUF_FORMAT)

#define PyBUF_READ 0x100
#define PyBUF_WRITE 0x200
#define PyBUF_SHADOW 0x400

typedef int (*getbufferproc)(PyObject *, Py_buffer *, int);
typedef void (*releasebufferproc)(Py_buffer *);
#endif 

#ifndef NDEBUG
#define PyBUF_PYGAME 0x4000
#endif

#define PyBUF_HAS_FLAG(f, F) (((f) & (F)) == (F))


typedef void (*pybuffer_releaseproc)(Py_buffer *);

typedef struct pg_bufferinfo_s {
    Py_buffer view;
    PyObject *consumer; 
    pybuffer_releaseproc release_buffer;
} pg_buffer;


#if defined(__SYMBIAN32__) && defined(HAVE_SIGNAL_H)
#undef HAVE_SIGNAL_H
#endif

#if defined(HAVE_SNPRINTF)
#undef HAVE_SNPRINTF
#endif

#ifdef MS_WIN32 
#ifndef WIN32
#define WIN32
#endif
#endif


#define MODPREFIX ""
#define IMPPREFIX "pygame."

#ifdef __SYMBIAN32__
#undef MODPREFIX
#undef IMPPREFIX

#define MODPREFIX "pygame_"
#define IMPPREFIX "pygame_"
#endif

#include <SDL.h>


#if (SDL_VERSION_ATLEAST(2, 0, 0))
#define IS_SDLv1 0
#define IS_SDLv2 1
#else
#define IS_SDLv1 1
#define IS_SDLv2 0
#endif



#if IS_SDLv2

typedef enum {
    SDL_HWSURFACE = 0,
    SDL_RESIZABLE = SDL_WINDOW_RESIZABLE,
    SDL_ASYNCBLIT = 0,
    SDL_OPENGL = SDL_WINDOW_OPENGL,
    SDL_OPENGLBLIT = 0,
    SDL_ANYFORMAT = 0,
    SDL_HWPALETTE = 0,
    SDL_DOUBLEBUF = 0,
    SDL_FULLSCREEN = SDL_WINDOW_FULLSCREEN,
    SDL_HWACCEL = 0,
    SDL_SRCCOLORKEY = 0,
    SDL_RLEACCELOK = 0,
    SDL_SRCALPHA = 0,
    SDL_NOFRAME = SDL_WINDOW_BORDERLESS,
    SDL_GL_SWAP_CONTROL = 0,
    TIMER_RESOLUTION = 0
} PygameVideoFlags;

/
typedef enum {
    PGM_BUTTON_LEFT = SDL_BUTTON_LEFT,
    PGM_BUTTON_RIGHT = SDL_BUTTON_RIGHT,
    PGM_BUTTON_MIDDLE = SDL_BUTTON_MIDDLE,
    PGM_BUTTON_WHEELUP = 4,
    PGM_BUTTON_WHEELDOWN = 5,
    PGM_BUTTON_X1 = SDL_BUTTON_X1 + 2,
    PGM_BUTTON_X2 = SDL_BUTTON_X2 + 2,
    PGM_BUTTON_KEEP = 0x80
} PygameMouseFlags;

typedef enum {
    SDL_NOEVENT = 0,
    
    SDL_NUMEVENTS = SDL_USEREVENT + 8,
    SDL_ACTIVEEVENT = SDL_NUMEVENTS,
    PGE_EVENTBEGIN = SDL_NUMEVENTS,
    SDL_VIDEORESIZE,
    SDL_VIDEOEXPOSE,
    PGE_KEYREPEAT,
    PGE_EVENTEND
} PygameEventCode;

#define PGE_NUMEVENTS (PGE_EVENTEND - PGE_EVENTBEGIN)

typedef enum {
    SDL_APPFOCUSMOUSE,
    SDL_APPINPUTFOCUS,
    SDL_APPACTIVE
} PygameAppCode;


typedef enum {
    PGS_SWSURFACE = 0x00000000,
    PGS_HWSURFACE = 0x00000001,
    PGS_ASYNCBLIT = 0x00000004,

    PGS_ANYFORMAT = 0x10000000,
    PGS_HWPALETTE = 0x20000000,
    PGS_DOUBLEBUF = 0x40000000,
    PGS_FULLSCREEN = 0x80000000,
    PGS_OPENGL = 0x00000002,
    PGS_OPENGLBLIT = 0x0000000A,
    PGS_RESIZABLE = 0x00000010,
    PGS_NOFRAME = 0x00000020,
    PGS_SHOWN = 0x00000040, 
    PGS_HIDDEN = 0x00000080, 

    PGS_HWACCEL = 0x00000100,
    PGS_SRCCOLORKEY = 0x00001000,
    PGS_RLEACCELOK = 0x00002000,
    PGS_RLEACCEL = 0x00004000,
    PGS_SRCALPHA = 0x00010000,
    PGS_PREALLOC = 0x01000000
} PygameSurfaceFlags;

typedef struct {
    Uint32 hw_available:1;
    Uint32 wm_available:1;
    Uint32 blit_hw:1;
    Uint32 blit_hw_CC:1;
    Uint32 blit_hw_A:1;
    Uint32 blit_sw:1;
    Uint32 blit_sw_CC:1;
    Uint32 blit_sw_A:1;
    Uint32 blit_fill:1;
    Uint32 video_mem;
    SDL_PixelFormat *vfmt;
    SDL_PixelFormat vfmt_data;
    int current_w;
    int current_h;
} pg_VideoInfo;

#endif 

#define RAISE(x, y) (PyErr_SetString((x), (y)), (PyObject *)NULL)

#ifdef WITH_THREAD
#define PG_CHECK_THREADS() (1)
#else 
#define PG_CHECK_THREADS()                        \
    (RAISE(PyExc_NotImplementedError,             \
          "Python built without thread support"))
#endif 

#define PyType_Init(x) (((x).ob_type) = &PyType_Type)
#define PYGAMEAPI_LOCAL_ENTRY "_PYGAME_C_API"

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef ABS
#define ABS(a) (((a) < 0) ? -(a) : (a))
#endif


#define VIDEO_INIT_CHECK()            \
    if (!SDL_WasInit(SDL_INIT_VIDEO)) \
    return RAISE(pgExc_SDLError, "video system not initialized")

#define CDROM_INIT_CHECK()            \
    if (!SDL_WasInit(SDL_INIT_CDROM)) \
    return RAISE(pgExc_SDLError, "cdrom system not initialized")

#define JOYSTICK_INIT_CHECK()            \
    if (!SDL_WasInit(SDL_INIT_JOYSTICK)) \
    return RAISE(pgExc_SDLError, "joystick system not initialized")


#define VIEW_CONTIGUOUS 1
#define VIEW_C_ORDER 2
#define VIEW_F_ORDER 4

#define PYGAMEAPI_BASE_FIRSTSLOT 0
#if IS_SDLv1
#define PYGAMEAPI_BASE_NUMSLOTS 19
#else 
#define PYGAMEAPI_BASE_NUMSLOTS 23
#endif 
#ifndef PYGAMEAPI_BASE_INTERNAL
#define pgExc_SDLError ((PyObject *)PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT])

#define pg_RegisterQuit \
    (*(void (*)(void (*)(void)))PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 1])

#define pg_IntFromObj \
    (*(int (*)(PyObject *, int *))PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 2])

#define pg_IntFromObjIndex      \
    (*(int (*)(PyObject *, int, \
               int *))PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 3])

#define pg_TwoIntsFromObj         \
    (*(int (*)(PyObject *, int *, \
               int *))PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 4])

#define pg_FloatFromObj \
    (*(int (*)(PyObject *, float *))PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 5])

#define pg_FloatFromObjIndex    \
    (*(int (*)(PyObject *, int, \
               float *))PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 6])

#define pg_TwoFloatsFromObj         \
    (*(int (*)(PyObject *, float *, \
               float *))PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 7])

#define pg_UintFromObj     \
    (*(int (*)(PyObject *, \
               Uint32 *))PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 8])

#define pg_UintFromObjIndex     \
    (*(int (*)(PyObject *, int, \
               Uint32 *))PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 9])

#define pgVideo_AutoQuit \
    (*(void (*)(void))PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 10])

#define pgVideo_AutoInit \
    (*(int (*)(void))PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 11])

#define pg_RGBAFromObj     \
    (*(int (*)(PyObject *, \
               Uint8 *))PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 12])

#define pgBuffer_AsArrayInterface   \
    (*(PyObject * (*)(Py_buffer *)) \
         PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 13])

#define pgBuffer_AsArrayStruct      \
    (*(PyObject * (*)(Py_buffer *)) \
         PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 14])

#define pgObject_GetBuffer              \
    (*(int (*)(PyObject *, pg_buffer *, \
               int))PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 15])

#define pgBuffer_Release \
    (*(void (*)(pg_buffer *))PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 16])

#define pgDict_AsBuffer                 \
    (*(int (*)(pg_buffer *, PyObject *, \
               int))PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 17])

#define pgExc_BufferError \
    ((PyObject *)PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 18])

#if IS_SDLv2
#define pg_GetDefaultWindow \
    (*(SDL_Window * (*)(void)) PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 19])

#define pg_SetDefaultWindow \
    (*(void (*)(SDL_Window *))PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 20])

#define pg_GetDefaultWindowSurface \
    (*(PyObject * (*)(void)) PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 21])

#define pg_SetDefaultWindowSurface \
    (*(void (*)(PyObject *))PyGAME_C_API[PYGAMEAPI_BASE_FIRSTSLOT + 22])

#endif 

#define import_pygame_base() IMPORT_PYGAME_MODULE(base, BASE)
#endif


#define PYGAMEAPI_RECT_FIRSTSLOT \
    (PYGAMEAPI_BASE_FIRSTSLOT + PYGAMEAPI_BASE_NUMSLOTS)
#define PYGAMEAPI_RECT_NUMSLOTS 4

#if IS_SDLv1
typedef struct {
    int x, y;
    int w, h;
} GAME_Rect;
#else
typedef SDL_Rect GAME_Rect;
#endif

typedef struct {
    PyObject_HEAD GAME_Rect r;
    PyObject *weakreflist;
} pgRectObject;

#define pgRect_AsRect(x) (((pgRectObject *)x)->r)
#ifndef PYGAMEAPI_RECT_INTERNAL
#define pgRect_Check(x) \
    ((x)->ob_type ==    \
     (PyTypeObject *)PyGAME_C_API[PYGAMEAPI_RECT_FIRSTSLOT + 0])
#define pgRect_Type \
    (*(PyTypeObject *)PyGAME_C_API[PYGAMEAPI_RECT_FIRSTSLOT + 0])
#define pgRect_New \
    (*(PyObject * (*)(SDL_Rect *)) PyGAME_C_API[PYGAMEAPI_RECT_FIRSTSLOT + 1])
#define pgRect_New4                        \
    (*(PyObject * (*)(int, int, int, int)) \
         PyGAME_C_API[PYGAMEAPI_RECT_FIRSTSLOT + 2])
#define pgRect_FromObject                        \
    (*(GAME_Rect * (*)(PyObject *, GAME_Rect *)) \
         PyGAME_C_API[PYGAMEAPI_RECT_FIRSTSLOT + 3])

#define import_pygame_rect() IMPORT_PYGAME_MODULE(rect, RECT)
#endif

/* CDROM */
#define PYGAMEAPI_CDROM_FIRSTSLOT \
    (PYGAMEAPI_RECT_FIRSTSLOT + PYGAMEAPI_RECT_NUMSLOTS)
#define PYGAMEAPI_CDROM_NUMSLOTS 2

typedef struct {
    PyObject_HEAD int id;
} pgCDObject;

#define pgCD_AsID(x) (((pgCDObject *)x)->id)
#ifndef PYGAMEAPI_CDROM_INTERNAL
#define pgCD_Check(x) \
    ((x)->ob_type ==  \
     (PyTypeObject *)PyGAME_C_API[PYGAMEAPI_CDROM_FIRSTSLOT + 0])
#define pgCD_Type \
    (*(PyTypeObject *)PyGAME_C_API[PYGAMEAPI_CDROM_FIRSTSLOT + 0])
#define pgCD_New \
    (*(PyObject * (*)(int)) PyGAME_C_API[PYGAMEAPI_CDROM_FIRSTSLOT + 1])

#define import_pygame_cd() IMPORT_PYGAME_MODULE(cdrom, CDROM)
#endif

/* JOYSTICK */
#define PYGAMEAPI_JOYSTICK_FIRSTSLOT \
    (PYGAMEAPI_CDROM_FIRSTSLOT + PYGAMEAPI_CDROM_NUMSLOTS)
#define PYGAMEAPI_JOYSTICK_NUMSLOTS 2

typedef struct {
    PyObject_HEAD int id;
} pgJoystickObject;

#define pgJoystick_AsID(x) (((pgJoystickObject *)x)->id)

#ifndef PYGAMEAPI_JOYSTICK_INTERNAL
#define pgJoystick_Check(x) \
    ((x)->ob_type ==        \
     (PyTypeObject *)PyGAME_C_API[PYGAMEAPI_JOYSTICK_FIRSTSLOT + 0])

#define pgJoystick_Type \
    (*(PyTypeObject *)PyGAME_C_API[PYGAMEAPI_JOYSTICK_FIRSTSLOT + 0])
#define pgJoystick_New \
    (*(PyObject * (*)(int)) PyGAME_C_API[PYGAMEAPI_JOYSTICK_FIRSTSLOT + 1])

#define import_pygame_joystick() IMPORT_PYGAME_MODULE(joystick, JOYSTICK)
#endif

/* DISPLAY */
#define PYGAMEAPI_DISPLAY_FIRSTSLOT \
    (PYGAMEAPI_JOYSTICK_FIRSTSLOT + PYGAMEAPI_JOYSTICK_NUMSLOTS)
#define PYGAMEAPI_DISPLAY_NUMSLOTS 2

typedef struct {
#if IS_SDLv1
    PyObject_HEAD SDL_VideoInfo info;
#else
    PyObject_HEAD pg_VideoInfo info;
#endif
} pgVidInfoObject;

#define pgVidInfo_AsVidInfo(x) (((pgVidInfoObject *)x)->info)
#ifndef PYGAMEAPI_DISPLAY_INTERNAL
#define pgVidInfo_Check(x) \
    ((x)->ob_type ==       \
     (PyTypeObject *)PyGAME_C_API[PYGAMEAPI_DISPLAY_FIRSTSLOT + 0])

#define pgVidInfo_Type \
    (*(PyTypeObject *)PyGAME_C_API[PYGAMEAPI_DISPLAY_FIRSTSLOT + 0])

#if IS_SDLv1
#define pgVidInfo_New                   \
    (*(PyObject * (*)(SDL_VideoInfo *)) \
         PyGAME_C_API[PYGAMEAPI_DISPLAY_FIRSTSLOT + 1])
#else
#define pgVidInfo_New                   \
    (*(PyObject * (*)(pg_VideoInfo *)) \
         PyGAME_C_API[PYGAMEAPI_DISPLAY_FIRSTSLOT + 1])
#endif

#define import_pygame_display() IMPORT_PYGAME_MODULE(display, DISPLAY)
#endif

/* SURFACE */
#define PYGAMEAPI_SURFACE_FIRSTSLOT \
    (PYGAMEAPI_DISPLAY_FIRSTSLOT + PYGAMEAPI_DISPLAY_NUMSLOTS)
#define PYGAMEAPI_SURFACE_NUMSLOTS 3
typedef struct {
    PyObject_HEAD SDL_Surface *surf;
#if IS_SDLv2
    int owner;
#endif                                    /* IS_SDLv2 */
    struct pgSubSurface_Data *subsurface; /*ptr to subsurface data (if a
                                           * subsurface)*/
    PyObject *weakreflist;
    PyObject *locklist;
    PyObject *dependency;
} pgSurfaceObject;
#define pgSurface_AsSurface(x) (((pgSurfaceObject *)x)->surf)
#ifndef PYGAMEAPI_SURFACE_INTERNAL
#define pgSurface_Check(x)    \
    (PyObject_IsInstance((x), \
        (PyObject *)PyGAME_C_API[PYGAMEAPI_SURFACE_FIRSTSLOT + 0]))
#define pgSurface_Type \
    (*(PyTypeObject *)PyGAME_C_API[PYGAMEAPI_SURFACE_FIRSTSLOT + 0])
#if IS_SDLv1
#define pgSurface_New                 \
    (*(PyObject * (*)(SDL_Surface *)) \
         PyGAME_C_API[PYGAMEAPI_SURFACE_FIRSTSLOT + 1])
#else /* IS_SDLv2 */
#define pgSurface_New2                     \
    (*(PyObject * (*)(SDL_Surface *, int)) \
         PyGAME_C_API[PYGAMEAPI_SURFACE_FIRSTSLOT + 1])
#endif /* IS_SDLv2 */
#define pgSurface_Blit                                         \
    (*(int (*)(PyObject *, PyObject *, SDL_Rect *, SDL_Rect *, \
               int))PyGAME_C_API[PYGAMEAPI_SURFACE_FIRSTSLOT + 2])

#define import_pygame_surface()                   \
    do {                                          \
        IMPORT_PYGAME_MODULE(surface, SURFACE);   \
        if (PyErr_Occurred() != NULL)             \
            break;                                \
        IMPORT_PYGAME_MODULE(surflock, SURFLOCK); \
    } while (0)

#if IS_SDLv2
#define pgSurface_New(surface) pgSurface_New2((surface), 1)
#define pgSurface_NewNoOwn(surface) pgSurface_New2((surface), 0)
#endif /* IS_SDLv2 */

#endif

/* SURFLOCK */ /*auto import/init by surface*/
#define PYGAMEAPI_SURFLOCK_FIRSTSLOT \
    (PYGAMEAPI_SURFACE_FIRSTSLOT + PYGAMEAPI_SURFACE_NUMSLOTS)
#define PYGAMEAPI_SURFLOCK_NUMSLOTS 8
struct pgSubSurface_Data {
    PyObject *owner;
    int pixeloffset;
    int offsetx, offsety;
};

typedef struct {
    PyObject_HEAD PyObject *surface;
    PyObject *lockobj;
    PyObject *weakrefs;
} pgLifetimeLockObject;

#ifndef PYGAMEAPI_SURFLOCK_INTERNAL
#define pgLifetimeLock_Check(x) \
    ((x)->ob_type ==            \
     (PyTypeObject *)PyGAME_C_API[PYGAMEAPI_SURFLOCK_FIRSTSLOT + 0])
#define pgSurface_Prep(x)                   \
    if (((pgSurfaceObject *)x)->subsurface) \
    (*(*(void (*)(                          \
        PyObject *))PyGAME_C_API[PYGAMEAPI_SURFLOCK_FIRSTSLOT + 1]))(x)

#define pgSurface_Unprep(x)                 \
    if (((pgSurfaceObject *)x)->subsurface) \
    (*(*(void (*)(                          \
        PyObject *))PyGAME_C_API[PYGAMEAPI_SURFLOCK_FIRSTSLOT + 2]))(x)

#define pgSurface_Lock \
    (*(int (*)(PyObject *))PyGAME_C_API[PYGAMEAPI_SURFLOCK_FIRSTSLOT + 3])
#define pgSurface_Unlock \
    (*(int (*)(PyObject *))PyGAME_C_API[PYGAMEAPI_SURFLOCK_FIRSTSLOT + 4])
#define pgSurface_LockBy   \
    (*(int (*)(PyObject *, \
               PyObject *))PyGAME_C_API[PYGAMEAPI_SURFLOCK_FIRSTSLOT + 5])
#define pgSurface_UnlockBy \
    (*(int (*)(PyObject *, \
               PyObject *))PyGAME_C_API[PYGAMEAPI_SURFLOCK_FIRSTSLOT + 6])
#define pgSurface_LockLifetime                 \
    (*(PyObject * (*)(PyObject *, PyObject *)) \
         PyGAME_C_API[PYGAMEAPI_SURFLOCK_FIRSTSLOT + 7])
#endif

/* EVENT */
#define PYGAMEAPI_EVENT_FIRSTSLOT \
    (PYGAMEAPI_SURFLOCK_FIRSTSLOT + PYGAMEAPI_SURFLOCK_NUMSLOTS)
#if IS_SDLv1
#define PYGAMEAPI_EVENT_NUMSLOTS 4
#else /* IS_SDLv2 */
#define PYGAMEAPI_EVENT_NUMSLOTS 6
#endif /* IS_SDLv2 */

typedef struct {
    PyObject_HEAD int type;
    PyObject *dict;
} pgEventObject;

#ifndef PYGAMEAPI_EVENT_INTERNAL
#define pgEvent_Check(x) \
    ((x)->ob_type ==     \
     (PyTypeObject *)PyGAME_C_API[PYGAMEAPI_EVENT_FIRSTSLOT + 0])
#define pgEvent_Type \
    (*(PyTypeObject *)PyGAME_C_API[PYGAMEAPI_EVENT_FIRSTSLOT + 0])
#define pgEvent_New                 \
    (*(PyObject * (*)(SDL_Event *)) \
         PyGAME_C_API[PYGAMEAPI_EVENT_FIRSTSLOT + 1])
#define pgEvent_New2                    \
    (*(PyObject * (*)(int, PyObject *)) \
         PyGAME_C_API[PYGAMEAPI_EVENT_FIRSTSLOT + 2])
#define pgEvent_FillUserEvent   \
    (*(int (*)(pgEventObject *, \
               SDL_Event *))PyGAME_C_API[PYGAMEAPI_EVENT_FIRSTSLOT + 3])
#if IS_SDLv2
#define pg_EnableKeyRepeat \
    (*(int (*)(int, int))PyGAME_C_API[PYGAMEAPI_EVENT_FIRSTSLOT + 4])
#define pg_GetKeyRepeat \
    (*(void (*)(int *, int *))PyGAME_C_API[PYGAMEAPI_EVENT_FIRSTSLOT + 5])
#endif /* IS_SDLv2 */
#define import_pygame_event() IMPORT_PYGAME_MODULE(event, EVENT)
#endif


#define PYGAMEAPI_RWOBJECT_FIRSTSLOT \
    (PYGAMEAPI_EVENT_FIRSTSLOT + PYGAMEAPI_EVENT_NUMSLOTS)
#define PYGAMEAPI_RWOBJECT_NUMSLOTS 6
#ifndef PYGAMEAPI_RWOBJECT_INTERNAL
#define pgRWops_FromObject           \
    (*(SDL_RWops * (*)(PyObject *))  \
         PyGAME_C_API[PYGAMEAPI_RWOBJECT_FIRSTSLOT + 0])
#define pgRWops_IsFileObject \
    (*(int (*)(SDL_RWops *))PyGAME_C_API[PYGAMEAPI_RWOBJECT_FIRSTSLOT + 1])
#define pg_EncodeFilePath                       \
    (*(PyObject * (*)(PyObject *, PyObject *))  \
         PyGAME_C_API[PYGAMEAPI_RWOBJECT_FIRSTSLOT + 2])
#define pg_EncodeString                                                     \
    (*(PyObject * (*)(PyObject *, const char *, const char *, PyObject *))  \
         PyGAME_C_API[PYGAMEAPI_RWOBJECT_FIRSTSLOT + 3])
#define pgRWops_FromFileObject       \
    (*(SDL_RWops * (*)(PyObject *))  \
         PyGAME_C_API[PYGAMEAPI_RWOBJECT_FIRSTSLOT + 4])
#define pgRWops_ReleaseObject       \
    (*(int (*)(SDL_RWops *))        \
         PyGAME_C_API[PYGAMEAPI_RWOBJECT_FIRSTSLOT + 5])
#define import_pygame_rwobject() IMPORT_PYGAME_MODULE(rwobject, RWOBJECT)

#endif

/* PixelArray */
#define PYGAMEAPI_PIXELARRAY_FIRSTSLOT \
    (PYGAMEAPI_RWOBJECT_FIRSTSLOT + PYGAMEAPI_RWOBJECT_NUMSLOTS)
#define PYGAMEAPI_PIXELARRAY_NUMSLOTS 2
#ifndef PYGAMEAPI_PIXELARRAY_INTERNAL
#define PyPixelArray_Check(x) \
    ((x)->ob_type ==          \
     (PyTypeObject *)PyGAME_C_API[PYGAMEAPI_PIXELARRAY_FIRSTSLOT + 0])
#define PyPixelArray_New \
    (*(PyObject * (*)) PyGAME_C_API[PYGAMEAPI_PIXELARRAY_FIRSTSLOT + 1])
#define import_pygame_pixelarray() IMPORT_PYGAME_MODULE(pixelarray, PIXELARRAY)
#endif /* PYGAMEAPI_PIXELARRAY_INTERNAL */

/* Color */
#define PYGAMEAPI_COLOR_FIRSTSLOT \
    (PYGAMEAPI_PIXELARRAY_FIRSTSLOT + PYGAMEAPI_PIXELARRAY_NUMSLOTS)
#define PYGAMEAPI_COLOR_NUMSLOTS 4
#ifndef PYGAMEAPI_COLOR_INTERNAL
#define pgColor_Check(x) \
    ((x)->ob_type ==     \
     (PyTypeObject *)PyGAME_C_API[PYGAMEAPI_COLOR_FIRSTSLOT + 0])
#define pgColor_Type (*(PyObject *)PyGAME_C_API[PYGAMEAPI_COLOR_FIRSTSLOT])
#define pgColor_New \
    (*(PyObject * (*)(Uint8 *)) PyGAME_C_API[PYGAMEAPI_COLOR_FIRSTSLOT + 1])
#define pgColor_NewLength              \
    (*(PyObject * (*)(Uint8 *, Uint8)) \
         PyGAME_C_API[PYGAMEAPI_COLOR_FIRSTSLOT + 3])

#define pg_RGBAFromColorObj \
    (*(int (*)(PyObject *,  \
               Uint8 *))PyGAME_C_API[PYGAMEAPI_COLOR_FIRSTSLOT + 2])
#define import_pygame_color() IMPORT_PYGAME_MODULE(color, COLOR)
#endif 

/* Math */
#define PYGAMEAPI_MATH_FIRSTSLOT \
    (PYGAMEAPI_COLOR_FIRSTSLOT + PYGAMEAPI_COLOR_NUMSLOTS)
#define PYGAMEAPI_MATH_NUMSLOTS 2
#ifndef PYGAMEAPI_MATH_INTERNAL
#define pgVector2_Check(x) \
    ((x)->ob_type ==       \
     (PyTypeObject *)PyGAME_C_API[PYGAMEAPI_MATH_FIRSTSLOT + 0])
#define pgVector3_Check(x) \
    ((x)->ob_type ==       \
     (PyTypeObject *)PyGAME_C_API[PYGAMEAPI_MATH_FIRSTSLOT + 1])

#define import_pygame_math() IMPORT_PYGAME_MODULE(math, MATH)
#endif /* PYGAMEAPI_MATH_INTERNAL */

#define PG_CAPSULE_NAME(m) (IMPPREFIX m "." PYGAMEAPI_LOCAL_ENTRY)

#define _IMPORT_PYGAME_MODULE(module, MODULE, api_root)                      \
    {                                                                        \
        PyObject *_module = PyImport_ImportModule(IMPPREFIX #module);        \
                                                                             \
        if (_module != NULL) {                                               \
            PyObject *_c_api =                                               \
                PyObject_GetAttrString(_module, PYGAMEAPI_LOCAL_ENTRY);      \
                                                                             \
            Py_DECREF(_module);                                              \
            if (_c_api != NULL && PyCapsule_CheckExact(_c_api)) {            \
                void **localptr = (void **)PyCapsule_GetPointer(             \
                    _c_api, PG_CAPSULE_NAME(#module));                       \
                                                                             \
                if (localptr != NULL) {                                      \
                    memcpy(api_root + PYGAMEAPI_##MODULE##_FIRSTSLOT,        \
                           localptr,                                         \
                           sizeof(void **) * PYGAMEAPI_##MODULE##_NUMSLOTS); \
                }                                                            \
            }                                                                \
            Py_XDECREF(_c_api);                                              \
        }                                                                    \
    }

#ifndef NO_PYGAME_C_API
#define IMPORT_PYGAME_MODULE(module, MODULE) \
    _IMPORT_PYGAME_MODULE(module, MODULE, PyGAME_C_API)
#define PYGAMEAPI_TOTALSLOTS \
    (PYGAMEAPI_MATH_FIRSTSLOT + PYGAMEAPI_MATH_NUMSLOTS)

#ifdef PYGAME_H
void *PyGAME_C_API[PYGAMEAPI_TOTALSLOTS] = {NULL};
#else
extern void *PyGAME_C_API[PYGAMEAPI_TOTALSLOTS];
#endif
#endif

#if PG_HAVE_CAPSULE
#define encapsulate_api(ptr, module) \
    PyCapsule_New(ptr, PG_CAPSULE_NAME(module), NULL)
#else
#define encapsulate_api(ptr, module) PyCObject_FromVoidPtr(ptr, NULL)
#endif

#ifndef PG_INLINE
#if defined(__clang__)
#define PG_INLINE __inline__ __attribute__((__unused__))
#elif defined(__GNUC__)
#define PG_INLINE __inline__
#elif defined(_MSC_VER)
#define PG_INLINE __inline
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define PG_INLINE inline
#else
#define PG_INLINE
#endif
#endif

#if defined(macintosh) && defined(__MWERKS__) || defined(__SYMBIAN32__)
#define PYGAME_EXPORT __declspec(export)
#else
#define PYGAME_EXPORT
#endif


#endif 
