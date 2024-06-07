mldv2_report_print(netdissect_options *ndo, const u_char *bp, u_int len)
{
    const struct icmp6_hdr *icp = (const struct icmp6_hdr *) bp;
    u_int group, nsrcs, ngroups;
    u_int i, j;

    
    if (len < 8) {
            ND_PRINT((ndo,"STR", len));
            return;
    }

    ND_TCHECK(icp->icmp6_data16[1]);
    ngroups = EXTRACT_16BITS(&icp->icmp6_data16[1]);
    ND_PRINT((ndo,"STR", ngroups));
    if (ndo->ndo_vflag > 0) {
	
	group = 8;
        for (i = 0; i < ngroups; i++) {
	    
	    if (len < group + 20) {
                    ND_PRINT((ndo,"STR"));
                    return;
	    }
            ND_TCHECK2(bp[group + 4], sizeof(struct in6_addr));
            ND_PRINT((ndo,"STR", ip6addr_string(ndo, &bp[group + 4])));
	    ND_PRINT((ndo,"STR",
                                         bp[group])));
            nsrcs = (bp[group + 2] << 8) + bp[group + 3];
	    
	    if (len < group + 20 + (nsrcs * sizeof(struct in6_addr))) {
                    ND_PRINT((ndo,"STR", nsrcs));
                    return;
	    }
            if (ndo->ndo_vflag == 1)
                    ND_PRINT((ndo,"STR", nsrcs));
            else {
		
                    ND_PRINT((ndo,"STR"));
                for (j = 0; j < nsrcs; j++) {
                    ND_TCHECK2(bp[group + 20 + j * sizeof(struct in6_addr)],
                            sizeof(struct in6_addr));
		    ND_PRINT((ndo,"STR", ip6addr_string(ndo, &bp[group + 20 + j * sizeof(struct in6_addr)])));
		}
                ND_PRINT((ndo,"STR"));
            }
	    
            group += 20 + nsrcs * sizeof(struct in6_addr);
	    ND_PRINT((ndo,"STR"));
        }
    }
    return;
trunc:
    ND_PRINT((ndo,"STR"));
    return;
}