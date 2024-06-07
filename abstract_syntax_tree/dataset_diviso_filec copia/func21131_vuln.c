hasstop (GPtrArray * lookin)
{
    unsigned int i;
    for (i = 0; i < lookin->len; i++) {
        if (!strcmp (((RsvgNode *) g_ptr_array_index (lookin, i))->type->str, "STR"))
            return 1;
    }
    return 0;
}