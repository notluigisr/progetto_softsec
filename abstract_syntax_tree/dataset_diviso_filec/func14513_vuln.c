static int esp_select(ESPState *s)
{
    int target;

    target = s->wregs[ESP_WBUSID] & BUSID_DID;

    s->ti_size = 0;
    fifo8_reset(&s->fifo);

    if (s->current_req) {
        
        scsi_req_cancel(s->current_req);
        s->async_len = 0;
    }

    s->current_dev = scsi_device_find(&s->bus, 0, target, 0);
    if (!s->current_dev) {
        
        s->rregs[ESP_RSTAT] = 0;
        s->rregs[ESP_RINTR] |= INTR_DC;
        s->rregs[ESP_RSEQ] = SEQ_0;
        esp_raise_irq(s);
        return -1;
    }

    
    s->rregs[ESP_RINTR] |= INTR_FC;
    s->rregs[ESP_RSEQ] = SEQ_CD;
    return 0;
}