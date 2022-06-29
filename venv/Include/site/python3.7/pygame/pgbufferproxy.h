
#if !defined(PG_BUFPROXY_HEADER)

#define PYGAMEAPI_BUFPROXY_NUMSLOTS 4
#define PYGAMEAPI_BUFPROXY_FIRSTSLOT 0

#if !(defined(PYGAMEAPI_BUFPROXY_INTERNAL) || defined(NO_PYGAME_C_API))
static void *PgBUFPROXY_C_API[PYGAMEAPI_BUFPROXY_NUMSLOTS];

typedef PyObject *(*_pgbufproxy_new_t)(PyObject *, getbufferproc);
typedef PyObject *(*_pgbufproxy_get_obj_t)(PyObject *);
typedef int (*_pgbufproxy_trip_t)(PyObject *);

#define pgBufproxy_Type (*(PyTypeObject*)PgBUFPROXY_C_API[0])
#define pgBufproxy_New (*(_pgbufproxy_new_t)PgBUFPROXY_C_API[1])
#define pgBufproxy_GetParent \
    (*(_pgbufproxy_get_obj_t)PgBUFPROXY_C_API[2])
#define pgBufproxy_Trip (*(_pgbufproxy_trip_t)PgBUFPROXY_C_API[3])
#define pgBufproxy_Check(x) ((x)->ob_type == (pgBufproxy_Type))
#define import_pygame_bufferproxy() \
    _IMPORT_PYGAME_MODULE(bufferproxy, BUFPROXY, PgBUFPROXY_C_API)

#endif 

#define PG_BUFPROXY_HEADER

#endif 
