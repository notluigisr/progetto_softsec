static int GTForePos(GTextField *gt,int pos, int ismeta) {
    int newpos=pos;

    if ( ismeta )
	newpos = GTextFieldSelForeword(gt->text,pos);
    else {
	if ( gt->text[pos]!=0 )
	    newpos = pos+1;
    }
return( newpos );
}