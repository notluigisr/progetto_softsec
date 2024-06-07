static void rtl8139_BasicModeCtrl_write(RTL8139State *s, uint32_t val)
{
    val &= 0xffff;

    DPRINTF("STR", val);

    
    uint32_t mask = 0xccff;

    if (1 || !rtl8139_config_writable(s))
    {
        
        mask |= 0x3000;
        
        mask |= 0x0100;
    }

    if (val & 0x8000) {
        
        rtl8139_reset_phy(s);
    }

    val = SET_MASKED(val, mask, s->BasicModeCtrl);

    s->BasicModeCtrl = val;
}