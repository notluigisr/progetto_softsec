rpl_print(netdissect_options *ndo,
          const struct icmp6_hdr *hdr,
          const u_char *bp, u_int length)
{
        int secured = hdr->icmp6_code & 0x80;
        int basecode= hdr->icmp6_code & 0x7f;

        if(secured) {
                ND_PRINT((ndo, "STR"));
                
                return;
        } else {
                ND_PRINT((ndo, "STR"));
        }

        switch(basecode) {
        case ND_RPL_DAG_IS:
                ND_PRINT((ndo, "STR"));
                if(ndo->ndo_vflag) {
                }
                break;
        case ND_RPL_DAG_IO:
                ND_PRINT((ndo, "STR"));
                if(ndo->ndo_vflag) {
                        rpl_dio_print(ndo, bp, length);
                }
                break;
        case ND_RPL_DAO:
                ND_PRINT((ndo, "STR"));
                if(ndo->ndo_vflag) {
                        rpl_dao_print(ndo, bp, length);
                }
                break;
        case ND_RPL_DAO_ACK:
                ND_PRINT((ndo, "STR"));
                if(ndo->ndo_vflag) {
                        rpl_daoack_print(ndo, bp, length);
                }
                break;
        default:
                ND_PRINT((ndo, "STR",hdr->icmp6_code));
                break;
        }
	return;

#if 0
trunc:
	ND_PRINT((ndo,"STR"));
	return;
#endif

}