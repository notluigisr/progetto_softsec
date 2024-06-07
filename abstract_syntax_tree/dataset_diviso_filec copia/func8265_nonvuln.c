bgp_vpn_sg_print(netdissect_options *ndo,
                 const u_char *pptr, char *buf, u_int buflen)
{
    uint8_t addr_length;
    u_int total_length, offset;

    total_length = 0;

    
    ND_TCHECK2(pptr[0], 1);
    addr_length =  *pptr++;

    
    ND_TCHECK2(pptr[0], (addr_length >> 3));
    total_length += (addr_length >> 3) + 1;
    offset = strlen(buf);
    if (addr_length) {
        snprintf(buf + offset, buflen - offset, "STR",
                 bgp_vpn_ip_print(ndo, pptr, addr_length));
        pptr += (addr_length >> 3);
    }

    
    ND_TCHECK2(pptr[0], 1);
    addr_length =  *pptr++;

    
    ND_TCHECK2(pptr[0], (addr_length >> 3));
    total_length += (addr_length >> 3) + 1;
    offset = strlen(buf);
    if (addr_length) {
        snprintf(buf + offset, buflen - offset, "STR",
                 bgp_vpn_ip_print(ndo, pptr, addr_length));
        pptr += (addr_length >> 3);
    }

trunc:
    return (total_length);
}