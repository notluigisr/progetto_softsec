dp_packet_get_icmp_payload(const struct dp_packet *b)
{
    return OVS_LIKELY(dp_packet_l4_size(b) >= ICMP_HEADER_LEN)
        ? (const char *)dp_packet_l4(b) + ICMP_HEADER_LEN : NULL;
}