GC_API unsigned GC_CALL GC_new_proc(GC_mark_proc proc)
{
    unsigned result;
    DCL_LOCK_STATE;
    LOCK();
    result = GC_new_proc_inner(proc);
    UNLOCK();
    return result;
}