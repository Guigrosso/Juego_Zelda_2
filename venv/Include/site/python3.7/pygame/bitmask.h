
#ifndef BITMASK_H
#define BITMASK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <limits.h>

#ifndef INLINE
# ifdef __GNUC__
#  define INLINE inline
# else
#  ifdef _MSC_VER
#   define INLINE __inline
#  else
#   define INLINE
#  endif
# endif
#endif

#define BITMASK_W unsigned long int
#define BITMASK_W_LEN (sizeof(BITMASK_W)*CHAR_BIT)
#define BITMASK_W_MASK (BITMASK_W_LEN - 1)
#define BITMASK_N(n) ((BITMASK_W)1 << (n))

typedef struct bitmask
{
  int w,h;
  BITMASK_W bits[1];
} bitmask_t;


bitmask_t *bitmask_create(int w, int h);


void bitmask_free(bitmask_t *m);


void bitmask_clear(bitmask_t *m);


void bitmask_fill(bitmask_t *m);


void bitmask_invert(bitmask_t *m);


unsigned int bitmask_count(bitmask_t *m);

static INLINE int bitmask_getbit(const bitmask_t *m, int x, int y)
{
  return (m->bits[x/BITMASK_W_LEN*m->h + y] & BITMASK_N(x & BITMASK_W_MASK)) != 0;
}

static INLINE void bitmask_setbit(bitmask_t *m, int x, int y)
{
  m->bits[x/BITMASK_W_LEN*m->h + y] |= BITMASK_N(x & BITMASK_W_MASK);
}

/* Clears the bit at (x,y) */
static INLINE void bitmask_clearbit(bitmask_t *m, int x, int y)
{
  m->bits[x/BITMASK_W_LEN*m->h + y] &= ~BITMASK_N(x & BITMASK_W_MASK);
}


int bitmask_overlap(const bitmask_t *a, const bitmask_t *b, int xoffset, int yoffset);

int bitmask_overlap_pos(const bitmask_t *a, const bitmask_t *b,
                        int xoffset, int yoffset, int *x, int *y);


int bitmask_overlap_area(const bitmask_t *a, const bitmask_t *b, int xoffset, int yoffset);


void bitmask_overlap_mask (const bitmask_t *a, const bitmask_t *b, bitmask_t *c, int xoffset, int yoffset);



void bitmask_draw(bitmask_t *a, const bitmask_t *b, int xoffset, int yoffset);

void bitmask_erase(bitmask_t *a, const bitmask_t *b, int xoffset, int yoffset);


bitmask_t *bitmask_scale(const bitmask_t *m, int w, int h);


void bitmask_convolve(const bitmask_t *a, const bitmask_t *b, bitmask_t *o, int xoffset, int yoffset);

#ifdef __cplusplus
} 
#endif

#endif
