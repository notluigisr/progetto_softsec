xps_image_end_image(gx_image_enum_common_t * info, bool draw_last)
{
    xps_image_enum_t *pie = (xps_image_enum_t *)info;
    int code = 0;

    

    code = TIFFWriteDirectory(pie->tif);
    TIFFCleanup(pie->tif);

    
    code = xps_add_tiff_image(pie);
    if (code < 0)
        goto exit;

    
    xps_setstrokebrush((gx_device_xps *) (pie->dev), xps_solidbrush);
    xps_setfillbrush((gx_device_xps *) (pie->dev), xps_solidbrush);

    
    code = xps_add_image_relationship(pie);

exit:
    if (pie->pcs != NULL)
        rc_decrement(pie->pcs, "STR");
    if (pie->buffer != NULL)
        gs_free_object(pie->memory, pie->buffer, "STR");
    if (pie->devc_buffer != NULL)
        gs_free_object(pie->memory, pie->devc_buffer, "STR");

    
    if (pie->icc_link != NULL)
        gsicc_release_link(pie->icc_link);

    return code;
}