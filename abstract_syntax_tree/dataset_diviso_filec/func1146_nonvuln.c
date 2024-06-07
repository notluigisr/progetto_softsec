GC_API GC_ATTR_MALLOC void * GC_CALL GC_malloc_atomic(size_t lb)
{
    return GC_malloc_kind(lb, PTRFREE);
}