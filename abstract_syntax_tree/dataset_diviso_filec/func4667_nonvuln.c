static int compareKeyIndex(void const* va, void const* vb)
{
    struct KeyIndex const* a = va;
    struct KeyIndex const* b = vb;

    return strcmp(a->keystr, b->keystr);
}