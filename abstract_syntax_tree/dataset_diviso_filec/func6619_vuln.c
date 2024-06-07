STATIC void GC_init_size_map(void)
{
    int i;

    
    
      GC_size_map[0] = 1;
    for (i = 1; i <= GRANULES_TO_BYTES(TINY_FREELISTS-1) - EXTRA_BYTES; i++) {
        GC_size_map[i] = (unsigned)ROUNDED_UP_GRANULES(i);
#       ifndef _MSC_VER
          GC_ASSERT(GC_size_map[i] < TINY_FREELISTS);
          
#       endif
    }
    
}