debug_indent(const gs_memory_t *mem, int indent)
{
    int i;

    for (i = indent; i > 0; --i)
        dmputc(mem, ' ');
}