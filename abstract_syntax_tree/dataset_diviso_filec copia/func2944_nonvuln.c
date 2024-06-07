static ssize_t qemu_send_packet_async_with_flags(NetClientState *sender,
                                                 unsigned flags,
                                                 const uint8_t *buf, int size,
                                                 NetPacketSent *sent_cb)
{
    NetQueue *queue;
    int ret;

#ifdef DEBUG_NET
    printf("STR");
    qemu_hexdump((const char *)buf, stdout, "STR", size);
#endif

    if (sender->link_down || !sender->peer) {
        return size;
    }

    
    ret = filter_receive(sender, NET_FILTER_DIRECTION_TX,
                         sender, flags, buf, size, sent_cb);
    if (ret) {
        return ret;
    }

    ret = filter_receive(sender->peer, NET_FILTER_DIRECTION_RX,
                         sender, flags, buf, size, sent_cb);
    if (ret) {
        return ret;
    }

    queue = sender->peer->incoming_queue;

    return qemu_net_queue_send(queue, sender, flags, buf, size, sent_cb);
}