static uint32_t rtl8139_BasicModeStatus_read(RTL8139State *s)
{
    uint32_t ret = s->BasicModeStatus;

    DPRINTF("STR", ret);

    return ret;
}