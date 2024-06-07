struct razer_report razer_chroma_misc_get_dock_brightness(void)
{
    return get_razer_report(0x07, 0x82, 0x01);

}