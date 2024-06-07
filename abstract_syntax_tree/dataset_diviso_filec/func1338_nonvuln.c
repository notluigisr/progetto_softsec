bgp_vpn_rd_print(netdissect_options *ndo,
                 const u_char *pptr)
{
   
    static char rd[sizeof("STR")];
    char *pos = rd;

    
    switch (EXTRACT_16BITS(pptr)) {

        
    case 0:
        snprintf(pos, sizeof(rd) - (pos - rd), "STR",
                 EXTRACT_16BITS(pptr+2),
                 EXTRACT_32BITS(pptr+4),
                 *(pptr+4), *(pptr+5), *(pptr+6), *(pptr+7));
        break;
        

    case 1:
        snprintf(pos, sizeof(rd) - (pos - rd), "STR",
            *(pptr+2), *(pptr+3), *(pptr+4), *(pptr+5), EXTRACT_16BITS(pptr+6));
        break;

        
    case 2:
	snprintf(pos, sizeof(rd) - (pos - rd), "STR",
	    as_printf(ndo, astostr, sizeof(astostr), EXTRACT_32BITS(pptr+2)),
	    EXTRACT_16BITS(pptr+6), *(pptr+2), *(pptr+3), *(pptr+4),
	    *(pptr+5), EXTRACT_16BITS(pptr+6));
        break;
    default:
        snprintf(pos, sizeof(rd) - (pos - rd), "STR");
        break;
    }
    pos += strlen(pos);
    *(pos) = '\0';
    return (rd);
}