static void kbd_send_chars(void *opaque)
{
    QemuConsole *s = opaque;
    int len;
    uint8_t buf[16];

    len = qemu_chr_be_can_write(s->chr);
    if (len > s->out_fifo.count)
        len = s->out_fifo.count;
    if (len > 0) {
        if (len > sizeof(buf))
            len = sizeof(buf);
        qemu_fifo_read(&s->out_fifo, buf, len);
        qemu_chr_be_write(s->chr, buf, len);
    }
    
    if (s->out_fifo.count > 0) {
        timer_mod(s->kbd_timer, qemu_clock_get_ms(QEMU_CLOCK_REALTIME) + 1);
    }
}