static int _FVMenuClose(FontView *fv) {
    int i;
    SplineFont *sf = fv->b.cidmaster?fv->b.cidmaster:fv->b.sf;

    if ( !SFCloseAllInstrs(fv->b.sf) )
return( false );

    if ( fv->b.nextsame!=NULL || fv->b.sf->fv!=&fv->b ) {
	
    } else if ( SFAnyChanged(sf) ) {
	i = AskChanged(fv->b.sf);
	if ( i==2 )	
return( false );
	if ( i==0 && !_FVMenuSave(fv))		
return(false);
	else
	    SFClearAutoSave(sf);		
    }
    _FVCloseWindows(fv);
    if ( sf->filename!=NULL )
	RecentFilesRemember(sf->filename);
    else if ( sf->origname!=NULL )
	RecentFilesRemember(sf->origname);
    GDrawDestroyWindow(fv->gw);
return( true );
}