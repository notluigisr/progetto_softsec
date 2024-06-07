decode_range_needed(gx_image_enum *penum)
{
    bool scale = true;

    if (penum->map[0].decoding == sd_compute) {
        if (!(gs_color_space_is_ICC(penum->pcs) || 
            gs_color_space_is_PSCIE(penum->pcs))) {
            scale = false;
        } 
    } 
    return scale;
}