static uint32_t rtl8139_BasicModeCtrl_read(RTL8139State *s)
{
    uint32_t ret = s->BasicModeCtrl;

    DPRINTF("STR", ret);

    return ret;
}