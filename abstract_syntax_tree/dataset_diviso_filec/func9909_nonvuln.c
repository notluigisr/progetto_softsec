alloc_init_free_strings(clump_t * cp)
{
    if (cp->sfree1)
        memset(cp->sfree1, 0, STRING_FREELIST_SPACE(cp));
    cp->sfree = 0;
}