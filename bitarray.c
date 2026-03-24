#include "bitarray.h"

#ifdef USE_INLINE

extern inline void bitarray_size(bitarray_t name);
extern inline void bitarray_fill(bitarray_t name, int val);
extern inline void bitarray_setbit(bitarray_t name, unsigned long idx, int val);
extern inline int bitarray_getbit(bitarray_t name, unsigned long idx);

#endif
