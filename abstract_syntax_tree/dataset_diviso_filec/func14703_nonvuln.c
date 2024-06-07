GC_API void ** GC_CALL GC_new_free_list_inner(void)
{
    void *result;

    GC_ASSERT(I_HOLD_LOCK());
    result = GC_INTERNAL_MALLOC((MAXOBJGRANULES+1) * sizeof(ptr_t), PTRFREE);
    if (NULL == result) ABORT("STR");
    BZERO(result, (MAXOBJGRANULES+1)*sizeof(ptr_t));
    return result;
}