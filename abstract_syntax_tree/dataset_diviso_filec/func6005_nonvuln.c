mp_fast_close_print(netdissect_options *ndo,
                    const u_char *opt, u_int opt_len, u_char flags _U_)
{
        if (opt_len != 12)
                return 0;

        ND_PRINT((ndo, "STR" PRIx64, EXTRACT_64BITS(opt + 4)));
        return 1;
}