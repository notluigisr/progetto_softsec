display_separation_get_color_comp_index(gx_device * dev,
    const char * pname, int name_size, int component_type)
{
    return devn_get_color_comp_index(dev,
                &(((gx_device_display *)dev)->devn_params),
                &(((gx_device_display *)dev)->equiv_cmyk_colors),
                pname, name_size, component_type, ENABLE_AUTO_SPOT_COLORS);
}