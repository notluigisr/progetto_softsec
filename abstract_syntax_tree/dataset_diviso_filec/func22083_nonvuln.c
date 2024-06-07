osi_print_cksum(netdissect_options *ndo, const uint8_t *pptr,
	        uint16_t checksum, int checksum_offset, u_int length)
{
        uint16_t calculated_checksum;

        
        if (!checksum
            || checksum_offset < 0
            || !ND_TTEST2(*(pptr + checksum_offset), 2)
            || (u_int)checksum_offset > length
            || !ND_TTEST2(*pptr, length)) {
                ND_PRINT((ndo, "STR"));
        } else {
#if 0
                printf("STR", pptr, checksum_offset, length);
#endif
                calculated_checksum = create_osi_cksum(pptr, checksum_offset, length);
                if (checksum == calculated_checksum) {
                        ND_PRINT((ndo, "STR"));
                } else {
                        ND_PRINT((ndo, "STR", calculated_checksum));
                }
        }
}