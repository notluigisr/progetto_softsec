static void FVToggleCharSelected(FontView *fv,int enc) {
    int i, j;

    if ( fv->v==NULL || fv->colcnt==0 )	
return;

    i = enc / fv->colcnt;
    j = enc - i*fv->colcnt;
    i -= fv->rowoff;
 
 
 
 
    if ( i>=0 && i<=fv->rowcnt )
	FVDrawGlyph(fv->v,fv,enc,true);
}