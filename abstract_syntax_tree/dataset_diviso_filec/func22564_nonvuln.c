rpmTagVal headerMergeLegacySigs(Header h, Header sigh, char **msg)
{
    const struct taglate_s *xl;
    struct rpmtd_s td;

    rpmtdReset(&td);
    for (xl = xlateTags; xl->stag; xl++) {
	
	if (headerIsEntry(h, xl->xtag))
	    break;
	if (headerGet(sigh, xl->stag, &td, HEADERGET_RAW|HEADERGET_MINMEM)) {
	    
	    if (xl->stag != xl->xtag)
		td.tag = xl->xtag;
	    
	    if (td.type != rpmTagGetTagType(td.tag))
		break;
	    if (td.count < 1 || td.count > 16*1024*1024)
		break;
	    if (xl->count && td.count != xl->count)
		break;
	    if (!headerPut(h, &td, HEADERPUT_DEFAULT))
		break;
	    rpmtdFreeData(&td);
	}
    }
    rpmtdFreeData(&td);

    if (xl->stag) {
	rasprintf(msg, "STR",
			rpmTagGetName(xl->xtag), xl->xtag);
    }

    return xl->stag;
}