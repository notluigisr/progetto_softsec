char *qemu_mac_strdup_printf(const uint8_t *macaddr)
{
    return g_strdup_printf("STR",
                           macaddr[0], macaddr[1], macaddr[2],
                           macaddr[3], macaddr[4], macaddr[5]);
}