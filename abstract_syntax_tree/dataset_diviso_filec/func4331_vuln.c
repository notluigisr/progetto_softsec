uint64_t esp_reg_read(ESPState *s, uint32_t saddr)
{
    uint32_t val;

    switch (saddr) {
    case ESP_FIFO:
        if (s->dma_memory_read && s->dma_memory_write &&
                (s->rregs[ESP_RSTAT] & STAT_PIO_MASK) == 0) {
            
            qemu_log_mask(LOG_UNIMP, "STR");
            s->rregs[ESP_FIFO] = 0;
        } else {
            s->rregs[ESP_FIFO] = esp_fifo_pop(s);
        }
        val = s->rregs[ESP_FIFO];
        break;
    case ESP_RINTR:
        
        val = s->rregs[ESP_RINTR];
        s->rregs[ESP_RINTR] = 0;
        s->rregs[ESP_RSTAT] &= ~STAT_TC;
        s->rregs[ESP_RSEQ] = SEQ_0;
        esp_lower_irq(s);
        break;
    case ESP_TCHI:
        
        if (!s->tchi_written) {
            val = s->chip_id;
        } else {
            val = s->rregs[saddr];
        }
        break;
     case ESP_RFLAGS:
        
        val = fifo8_num_used(&s->fifo);
        break;
    default:
        val = s->rregs[saddr];
        break;
    }

    trace_esp_mem_readb(saddr, val);
    return val;
}