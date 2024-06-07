static int FVSelCount(FontView *fv) {
    int i, cnt=0;

    for ( i=0; i<fv->b.map->enccount; ++i )
	if ( fv->b.selected[i] ) ++cnt;
    if ( cnt>10 ) {
	char *buts[3];
	buts[0] = _("STR");
	buts[1] = _("STR");
	buts[2] = NULL;
	if ( gwwv_ask(_("STR"))==1 )
return( false );
    }
return( true );
}