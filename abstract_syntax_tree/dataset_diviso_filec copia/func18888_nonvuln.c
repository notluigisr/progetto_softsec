static void rtl8139_Config5_write(RTL8139State *s, uint32_t val)
{
    val &= 0xff;

    DPRINTF("STR", val);

    
    val = SET_MASKED(val, 0x80, s->Config5);

    s->Config5 = val;
}