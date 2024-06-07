static void pdfobj_flag(struct pdf_struct *pdf, struct pdf_obj *obj, enum pdf_flag flag)
{
    const char *s= "";
    pdf->flags |= 1 << flag;
    if (!cli_debug_flag)
	return;
    switch (flag) {
	case UNTERMINATED_OBJ_DICT:
	    s = "STR";
	    break;
	case ESCAPED_COMMON_PDFNAME:
	    
	    s = "STR";
	    break;
	case BAD_STREAM_FILTERS:
	    s = "STR";
	    break;
	case BAD_PDF_VERSION:
	    s = "STR";
	    break;
	case BAD_PDF_HEADERPOS:
	    s = "STR";
	    break;
	case BAD_PDF_TRAILER:
	    s = "STR";
	    break;
	case BAD_PDF_TOOMANYOBJS:
	    s = "STR";
	    break;
	case BAD_FLATE:
	    s = "STR";
	    break;
	case BAD_FLATESTART:
	    s = "STR";
	    break;
	case BAD_STREAMSTART:
	    s = "STR";
	    break;
	case UNKNOWN_FILTER:
	    s = "STR";
	    break;
	case BAD_ASCIIDECODE:
	    s = "STR";
	    break;
	case HEX_JAVASCRIPT:
	    s = "STR";
	    break;
	case BAD_INDOBJ:
	    s = "STR";
	    break;
	case HAS_OPENACTION:
	    s = "STR";
	    break;
	case HAS_LAUNCHACTION:
	    s = "STR";
	    break;
	case BAD_STREAMLEN:
	    s = "STR";
	    break;
	case ENCRYPTED_PDF:
	    s = "STR";
	    break;
	case LINEARIZED_PDF:
	    s = "STR";
	    break;
	case MANY_FILTERS:
	    s = "STR";
	    break;
    }
    cli_dbgmsg("STR", s, obj->id>>8, obj->id&0xff);
}