static void esp_do_nodma(ESPState *s)
{
    int to_device = ((s->rregs[ESP_RSTAT] & 7) == STAT_DO);
    uint32_t cmdlen, n;
    int len;

    if (s->do_cmd) {
        cmdlen = fifo8_num_used(&s->cmdfifo);
        trace_esp_handle_ti_cmd(cmdlen);
        s->ti_size = 0;
        if ((s->rregs[ESP_RSTAT] & 7) == STAT_CD) {
            
            if (s->cmdfifo_cdb_offset == fifo8_num_used(&s->cmdfifo)) {
                return;
            }

            
            s->do_cmd = 0;
            do_cmd(s);
        } else {
            
            s->cmdfifo_cdb_offset = fifo8_num_used(&s->cmdfifo);
            s->rregs[ESP_RSTAT] = STAT_TC | STAT_CD;
            s->rregs[ESP_RSEQ] = SEQ_CD;
            s->rregs[ESP_RINTR] |= INTR_BS;
            esp_raise_irq(s);
        }
        return;
    }

    if (s->async_len == 0) {
        
        return;
    }

    if (to_device) {
        len = MIN(fifo8_num_used(&s->fifo), ESP_FIFO_SZ);
        memcpy(s->async_buf, fifo8_pop_buf(&s->fifo, len, &n), len);
        s->async_buf += len;
        s->async_len -= len;
        s->ti_size += len;
    } else {
        len = MIN(s->ti_size, s->async_len);
        len = MIN(len, fifo8_num_free(&s->fifo));
        fifo8_push_all(&s->fifo, s->async_buf, len);
        s->async_buf += len;
        s->async_len -= len;
        s->ti_size -= len;
    }

    if (s->async_len == 0) {
        scsi_req_continue(s->current_req);

        if (to_device || s->ti_size == 0) {
            return;
        }
    }

    s->rregs[ESP_RINTR] |= INTR_BS;
    esp_raise_irq(s);
}