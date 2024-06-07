static void rtl8139_TxStatus_write(RTL8139State *s, uint32_t txRegOffset, uint32_t val)
{

    int descriptor = txRegOffset/4;

    

    if (s->cplus_enabled)
    {
        DPRINTF("STR"
            "STR", txRegOffset, val, descriptor);

        
        s->TxStatus[descriptor] = val;

        if (descriptor == 0 && (val & 0x8))
        {
            hwaddr tc_addr = rtl8139_addr64(s->TxStatus[0] & ~0x3f, s->TxStatus[1]);

            
            RTL8139TallyCounters_dma_write(s, tc_addr);

            
            s->TxStatus[0] &= ~0x8;
        }

        return;
    }

    DPRINTF("STR",
        txRegOffset, val, descriptor);

    
    val &= ~0xff00c000; 
    val = SET_MASKED(val, 0x00c00000, s->TxStatus[descriptor]);

    s->TxStatus[descriptor] = val;

    
    rtl8139_transmit(s);
}