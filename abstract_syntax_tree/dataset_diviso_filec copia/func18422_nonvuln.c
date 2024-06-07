dp_packet_delete(struct dp_packet *b)
{
    if (b) {
        if (b->source == DPBUF_DPDK) {
            
            free_dpdk_buf((struct dp_packet*) b);
            return;
        }

        if (b->source == DPBUF_AFXDP) {
            free_afxdp_buf(b);
            return;
        }

        dp_packet_uninit(b);
        free(b);
    }
}