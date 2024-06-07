GC_API GC_ATTR_MALLOC void * GC_CALL GC_malloc_many(size_t lb)
{
    void *result;

    GC_generic_malloc_many(ROUNDUP_GRANULE_SIZE(lb + EXTRA_BYTES),
                           NORMAL, &result);
    return result;
}