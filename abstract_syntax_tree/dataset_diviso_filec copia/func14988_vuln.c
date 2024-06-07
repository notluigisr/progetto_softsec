lldp_private_8023_print(netdissect_options *ndo,
                        const u_char *tptr, u_int tlv_len)
{
    int subtype, hexdump = FALSE;

    if (tlv_len < 4) {
        return hexdump;
    }
    subtype = *(tptr+3);

    ND_PRINT((ndo, "STR",
           tok2str(lldp_8023_subtype_values, "STR", subtype),
           subtype));

    switch (subtype) {
    case LLDP_PRIVATE_8023_SUBTYPE_MACPHY:
        if (tlv_len < 9) {
            return hexdump;
        }
        ND_PRINT((ndo, "STR",
               bittok2str(lldp_8023_autonegotiation_values, "STR", *(tptr+4)),
               *(tptr + 4)));
        ND_PRINT((ndo, "STR",
               bittok2str(lldp_pmd_capability_values,"STR", EXTRACT_16BITS(tptr+5)),
               EXTRACT_16BITS(tptr + 5)));
        ND_PRINT((ndo, "STR",
               tok2str(lldp_mau_types_values, "STR", EXTRACT_16BITS(tptr+7)),
               EXTRACT_16BITS(tptr + 7)));
        break;

    case LLDP_PRIVATE_8023_SUBTYPE_MDIPOWER:
        if (tlv_len < 7) {
            return hexdump;
        }
        ND_PRINT((ndo, "STR",
               bittok2str(lldp_mdi_values, "STR", *(tptr+4)),
               tok2str(lldp_mdi_power_pairs_values, "STR", *(tptr+5)),
               tok2str(lldp_mdi_power_class_values, "STR", *(tptr + 6))));
        break;

    case LLDP_PRIVATE_8023_SUBTYPE_LINKAGGR:
        if (tlv_len < 9) {
            return hexdump;
        }
        ND_PRINT((ndo, "STR",
               bittok2str(lldp_aggregation_values, "STR", *(tptr+4)),
               EXTRACT_32BITS(tptr + 5)));
        break;

    case LLDP_PRIVATE_8023_SUBTYPE_MTU:
        ND_PRINT((ndo, "STR", EXTRACT_16BITS(tptr + 4)));
        break;

    default:
        hexdump = TRUE;
        break;
    }

    return hexdump;
}