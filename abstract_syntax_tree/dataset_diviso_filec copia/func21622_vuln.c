void json_object_seed(size_t seed) {
    uint32_t new_seed = (uint32_t)seed;

    if (hashtable_seed == 0) {
        if (new_seed == 0) {
            
            new_seed = generate_seed();
        }

        do {
            if (__sync_bool_compare_and_swap(&hashtable_seed, 0, new_seed)) {
                
                break;
            } else {
                
#ifdef HAVE_SCHED_YIELD
                sched_yield();
#endif
            }
        } while(hashtable_seed == 0);
    }
}