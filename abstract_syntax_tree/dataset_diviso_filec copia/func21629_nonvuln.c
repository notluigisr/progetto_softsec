static void rtl8139_io_writeb(void *opaque, uint8_t addr, uint32_t val)
{
    RTL8139State *s = opaque;

    switch (addr)
    {
        case MAC0 ... MAC0+4:
            s->phys[addr - MAC0] = val;
            break;
        case MAC0+5:
            s->phys[addr - MAC0] = val;
            qemu_format_nic_info_str(qemu_get_queue(s->nic), s->phys);
            break;
        case MAC0+6 ... MAC0+7:
            
            break;
        case MAR0 ... MAR0+7:
            s->mult[addr - MAR0] = val;
            break;
        case ChipCmd:
            rtl8139_ChipCmd_write(s, val);
            break;
        case Cfg9346:
            rtl8139_Cfg9346_write(s, val);
            break;
        case TxConfig: 
            rtl8139_TxConfig_writeb(s, val);
            break;
        case Config0:
            rtl8139_Config0_write(s, val);
            break;
        case Config1:
            rtl8139_Config1_write(s, val);
            break;
        case Config3:
            rtl8139_Config3_write(s, val);
            break;
        case Config4:
            rtl8139_Config4_write(s, val);
            break;
        case Config5:
            rtl8139_Config5_write(s, val);
            break;
        case MediaStatus:
            
            DPRINTF("STR",
                val);
            break;

        case HltClk:
            DPRINTF("STR", val);
            if (val == 'R')
            {
                s->clock_enabled = 1;
            }
            else if (val == 'H')
            {
                s->clock_enabled = 0;
            }
            break;

        case TxThresh:
            DPRINTF("STR", val);
            s->TxThresh = val;
            break;

        case TxPoll:
            DPRINTF("STR", val);
            if (val & (1 << 7))
            {
                DPRINTF("STR"
                    "STR");
                
            }
            if (val & (1 << 6))
            {
                DPRINTF("STR");
                rtl8139_cplus_transmit(s);
            }

            break;

        default:
            DPRINTF("STR", addr,
                val);
            break;
    }
}