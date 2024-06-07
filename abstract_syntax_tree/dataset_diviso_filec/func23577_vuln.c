mp_join_print(netdissect_options *ndo,
              const u_char *opt, u_int opt_len, u_char flags)
{
        const struct mp_join *mpj = (const struct mp_join *) opt;

        if (!(opt_len == 12 && flags & TH_SYN) &&
            !(opt_len == 16 && (flags & (TH_SYN | TH_ACK)) == (TH_SYN | TH_ACK)) &&
            !(opt_len == 24 && flags & TH_ACK))
                return 0;

        if (opt_len != 24) {
                if (mpj->sub_b & MP_JOIN_B)
                        ND_PRINT((ndo, "STR"));
                ND_PRINT((ndo, "STR", mpj->addr_id));
        }

        switch (opt_len) {
        case 12: 
                ND_PRINT((ndo, "STR",
                        EXTRACT_32BITS(mpj->u.syn.token),
                        EXTRACT_32BITS(mpj->u.syn.nonce)));
                break;
        case 16: 
                ND_PRINT((ndo, "STR",
                        EXTRACT_64BITS(mpj->u.synack.mac),
                        EXTRACT_32BITS(mpj->u.synack.nonce)));
                break;
        case 24: {
                size_t i;
                ND_PRINT((ndo, "STR"));
                for (i = 0; i < sizeof(mpj->u.ack.mac); ++i)
                        ND_PRINT((ndo, "STR", mpj->u.ack.mac[i]));
        }
        default:
                break;
        }
        return 1;
}