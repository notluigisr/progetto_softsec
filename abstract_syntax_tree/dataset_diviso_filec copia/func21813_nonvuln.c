void tr_variantFree(tr_variant* v)
{
    if (tr_variantIsSomething(v))
    {
        tr_variantWalk(v, &freeWalkFuncs, NULL, false);
    }
}