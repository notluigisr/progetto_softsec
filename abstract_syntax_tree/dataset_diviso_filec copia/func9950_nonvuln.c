STATIC void
S_put_charclass_bitmap_innards_invlist(pTHX_ SV *sv, SV* invlist)
{
    

    UV start, end;
    bool allow_literals = TRUE;

    PERL_ARGS_ASSERT_PUT_CHARCLASS_BITMAP_INNARDS_INVLIST;

    
    invlist_iterinit(invlist);
    while (invlist_iternext(invlist, &start, &end)) {

        
        if (start > MAX_PRINT_A) {
            break;
        }

        
        if (start < ' ' + 2 && end > MAX_PRINT_A - 2) {
            if (end > MAX_PRINT_A) {
                end = MAX_PRINT_A;
            }
            if (start < ' ') {
                start = ' ';
            }
            if (end - start >= MAX_PRINT_A - ' ' - 2) {
                allow_literals = FALSE;
            }
            break;
        }
    }
    invlist_iterfinish(invlist);

    
    invlist_iterinit(invlist);
    while (invlist_iternext(invlist, &start, &end)) {
        if (start >= NUM_ANYOF_CODE_POINTS) {
            break;
        }
        put_range(sv, start, end, allow_literals);
    }
    invlist_iterfinish(invlist);

    return;