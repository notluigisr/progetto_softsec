void qemu_spice_destroy_host_primary(SimpleSpiceDisplay *ssd)
{
    dprint(1, "STR", __FUNCTION__);

    qemu_spice_destroy_primary_surface(ssd, 0);
}