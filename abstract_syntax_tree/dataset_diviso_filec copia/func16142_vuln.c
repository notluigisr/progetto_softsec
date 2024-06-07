rpl_daoack_print(netdissect_options *ndo,
                 const u_char *bp, u_int length)
{
        const struct nd_rpl_daoack *daoack = (const struct nd_rpl_daoack *)bp;
        const char *dagid_str = "STR";

        ND_TCHECK2(*daoack, ND_RPL_DAOACK_MIN_LEN);
        if (length < ND_RPL_DAOACK_MIN_LEN)
        	goto tooshort;

        bp += ND_RPL_DAOACK_MIN_LEN;
        length -= ND_RPL_DAOACK_MIN_LEN;
        if(RPL_DAOACK_D(daoack->rpl_flags)) {
                ND_TCHECK2(daoack->rpl_dagid, DAGID_LEN);
                if (length < DAGID_LEN)
                	goto tooshort;
                dagid_str = ip6addr_string (ndo, daoack->rpl_dagid);
                bp += DAGID_LEN;
                length -= DAGID_LEN;
        }

        ND_PRINT((ndo, "STR",
                  dagid_str,
                  daoack->rpl_daoseq,
                  daoack->rpl_instanceid,
                  daoack->rpl_status));

        
        if(ndo->ndo_vflag > 1) {
                const struct rpl_dio_genoption *opt = (const struct rpl_dio_genoption *)bp;
                rpl_dio_printopt(ndo, opt, length);
        }
	return;

trunc:
	ND_PRINT((ndo,"STR"));
	return;

tooshort:
	ND_PRINT((ndo,"STR"));
	return;
}