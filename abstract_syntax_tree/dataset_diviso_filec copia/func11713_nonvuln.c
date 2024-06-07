S_get_invlist_iter_addr(SV* invlist)
{
    

    PERL_ARGS_ASSERT_GET_INVLIST_ITER_ADDR;

    assert(SvTYPE(invlist) == SVt_INVLIST);

    return &(((XINVLIST*) SvANY(invlist))->iterator);
}