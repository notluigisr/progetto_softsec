_nc_use_tracef(unsigned mask)
{
    bool result = FALSE;

    _nc_lock_global(tst_tracef);
    if (!MyNested++) {
	if ((result = (_nc_tracing & (mask))) != 0
	    && _nc_try_global(tracef) == 0) {
	    
	} else {
	    
	    MyNested = 0;
	}
    } else {
	
	result = (_nc_tracing & (mask));
    }
    _nc_unlock_global(tst_tracef);
    return result;
}