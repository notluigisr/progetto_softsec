static int32_t virtio_net_rsc_handle_ack(VirtioNetRscChain *chain,
                                         VirtioNetRscSeg *seg,
                                         const uint8_t *buf,
                                         struct tcp_header *n_tcp,
                                         struct tcp_header *o_tcp)
{
    uint32_t nack, oack;
    uint16_t nwin, owin;

    nack = htonl(n_tcp->th_ack);
    nwin = htons(n_tcp->th_win);
    oack = htonl(o_tcp->th_ack);
    owin = htons(o_tcp->th_win);

    if ((nack - oack) >= VIRTIO_NET_MAX_TCP_PAYLOAD) {
        chain->stat.ack_out_of_win++;
        return RSC_FINAL;
    } else if (nack == oack) {
        
        if (nwin == owin) {
            
            chain->stat.dup_ack++;
            return RSC_FINAL;
        } else {
            
            o_tcp->th_win = n_tcp->th_win;
            chain->stat.win_update++;
            return RSC_COALESCE;
        }
    } else {
        
        chain->stat.pure_ack++;
        return RSC_FINAL;
    }
}