with_gvl_gc_for_fd(void *ptr)
{
    int *e = ptr;

    return (void *)(rb_gc_for_fd(*e) ? Qtrue : Qfalse);
}