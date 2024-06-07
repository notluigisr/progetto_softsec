static void xgmac_enet_send(XgmacState *s)
{
    struct desc bd;
    int frame_size;
    int len;
    uint8_t frame[8192];
    uint8_t *ptr;

    ptr = frame;
    frame_size = 0;
    while (1) {
        xgmac_read_desc(s, &bd, 0);
        if ((bd.ctl_stat & 0x80000000) == 0) {
            
            break;
        }
        len = (bd.buffer1_size & 0xfff) + (bd.buffer2_size & 0xfff);

        if ((bd.buffer1_size & 0xfff) > 2048) {
            DEBUGF_BRK("STR"
                        "STR",
                         __func__, bd.buffer1_size & 0xfff);
        }
        if ((bd.buffer2_size & 0xfff) != 0) {
            DEBUGF_BRK("STR"
                        "STR",
                        __func__, bd.buffer2_size & 0xfff);
        }
        if (len >= sizeof(frame)) {
            DEBUGF_BRK("STR"
                        "STR" , __func__, len, sizeof(frame));
            DEBUGF_BRK("STR",
                        __func__, bd.buffer1_size, bd.buffer2_size);
        }

        cpu_physical_memory_read(bd.buffer1_addr, ptr, len);
        ptr += len;
        frame_size += len;
        if (bd.ctl_stat & 0x20000000) {
            
            qemu_send_packet(qemu_get_queue(s->nic), frame, len);
            ptr = frame;
            frame_size = 0;
            s->regs[DMA_STATUS] |= DMA_STATUS_TI | DMA_STATUS_NIS;
        }
        bd.ctl_stat &= ~0x80000000;
        
        xgmac_write_desc(s, &bd, 0);
    }
}