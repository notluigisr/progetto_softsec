static ssize_t vnc_client_write_plain(VncState *vs)
{
    ssize_t ret;

#ifdef CONFIG_VNC_SASL
    VNC_DEBUG("STR",
              vs->output.buffer, vs->output.capacity, vs->output.offset,
              vs->sasl.waitWriteSSF);

    if (vs->sasl.conn &&
        vs->sasl.runSSF &&
        vs->sasl.waitWriteSSF) {
        ret = vnc_client_write_buf(vs, vs->output.buffer, vs->sasl.waitWriteSSF);
        if (ret)
            vs->sasl.waitWriteSSF -= ret;
    } else
#endif 
        ret = vnc_client_write_buf(vs, vs->output.buffer, vs->output.offset);
    if (!ret)
        return 0;

    buffer_advance(&vs->output, ret);

    if (vs->output.offset == 0) {
        qemu_set_fd_handler(vs->csock, vnc_client_read, NULL, vs);
    }

    return ret;
}