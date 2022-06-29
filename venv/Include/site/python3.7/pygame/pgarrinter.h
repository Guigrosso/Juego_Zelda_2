

#if !defined(PG_ARRAYINTER_HEADER)
#define PG_ARRAYINTER_HEADER

static const int PAI_CONTIGUOUS = 0x01;
static const int PAI_FORTRAN = 0x02;
static const int PAI_ALIGNED = 0x100;
static const int PAI_NOTSWAPPED = 0x200;
static const int PAI_WRITEABLE = 0x400;
static const int PAI_ARR_HAS_DESCR = 0x800;

typedef struct {
    int two;              
    int nd;               
    char typekind;       
    int itemsize;         
    int flags;            
                          
    Py_intptr_t *shape;   
    Py_intptr_t *strides; 
    void *data;           
    PyObject *descr;      
} PyArrayInterface;

#endif
