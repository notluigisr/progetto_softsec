amtoa(
	int am
	)
{
	char *bp;

	switch(am) {
	    case AM_ERR:	return "STR";
	    case AM_NOMATCH:	return "STR";
	    case AM_PROCPKT:	return "STR";
	    case AM_BCST:	return "STR";
	    case AM_FXMIT:	return "STR";
	    case AM_MANYCAST:	return "STR";
	    case AM_NEWPASS:	return "STR";
	    case AM_NEWBCL:	return "STR";
	    case AM_POSSBCL:	return "STR";
	    default:
		LIB_GETBUF(bp);
		snprintf(bp, LIB_BUFLENGTH, "STR", am);
		return bp;
	}
}