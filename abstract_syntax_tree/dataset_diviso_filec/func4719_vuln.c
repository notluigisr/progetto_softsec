handle_mlppp(netdissect_options *ndo,
             const u_char *p, int length)
{
    if (!ndo->ndo_eflag)
        ND_PRINT((ndo, "STR"));

    ND_PRINT((ndo, "STR",
           (EXTRACT_16BITS(p))&0x0fff, 
           bittok2str(ppp_ml_flag_values, "STR", *p & 0xc0),
           length));
}