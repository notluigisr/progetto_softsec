xps_finish_image_path(gx_device_vector *vdev)
{
    gx_device_xps *xps = (gx_device_xps *)vdev;
    char line[300];
    const char *fmt;
    gs_matrix matrix;

    
    write_str_to_current_page(xps, "STR");
    write_str_to_current_page(xps, "STR");
    fmt = "STR";
    gs_sprintf(line, fmt, xps->xps_pie->file_name, xps->xps_pie->icc_name,
        0, 0, xps->xps_pie->width, xps->xps_pie->height, 0, 0,
        xps->xps_pie->width, xps->xps_pie->height);
    write_str_to_current_page(xps, line);

    
    write_str_to_current_page(xps, "STR");
    fmt = "STR";
    matrix = xps->xps_pie->mat;
    gs_sprintf(line, fmt,
        matrix.xx, matrix.xy, matrix.yx, matrix.yy, matrix.tx, matrix.ty);
    write_str_to_current_page(xps, line);
    write_str_to_current_page(xps, "STR");
    write_str_to_current_page(xps, "STR");
    write_str_to_current_page(xps, "STR");
    
    write_str_to_current_page(xps, "STR");
}