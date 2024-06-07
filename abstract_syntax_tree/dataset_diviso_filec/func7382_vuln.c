GC_API GC_ATTR_MALLOC void * GC_CALL GC_malloc_explicitly_typed(size_t lb,
                                                                GC_descr d)
{
    word *op;
    size_t lg;

    GC_ASSERT(GC_explicit_typing_initialized);
    lb += TYPD_EXTRA_BYTES;
    op = GC_malloc_kind(lb, GC_explicit_kind);
    if (EXPECT(NULL == op, FALSE))
        return NULL;
    lg = SMALL_OBJ(lb) ? GC_size_map[lb] : BYTES_TO_GRANULES(GC_size(op));
    op[GRANULES_TO_WORDS(lg) - 1] = d;
    return op;
}