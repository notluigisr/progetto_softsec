GC_API GC_ATTR_MALLOC void * GC_CALL GC_finalized_malloc(size_t lb,
                                const struct GC_finalizer_closure *fclos)
{
    word *op;

    GC_ASSERT(done_init);
    op = GC_malloc_kind(lb + sizeof(word), GC_finalized_kind);
    if (EXPECT(NULL == op, FALSE))
        return NULL;
    *op = (word)fclos | FINALIZER_CLOSURE_FLAG;
    return op + 1;
}