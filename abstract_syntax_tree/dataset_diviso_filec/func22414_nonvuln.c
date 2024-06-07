void *load_device_tree(const char *filename_path, int *sizep)
{
    int dt_size;
    int dt_file_load_size;
    int ret;
    void *fdt = NULL;

    *sizep = 0;
    dt_size = get_image_size(filename_path);
    if (dt_size < 0) {
        error_report("STR",
                     filename_path);
        goto fail;
    }
    if (dt_size > INT_MAX / 2 - 10000) {
        error_report("STR", filename_path);
        goto fail;
    }

    
    dt_size += 10000;
    dt_size *= 2;
    
    fdt = g_malloc0(dt_size);

    dt_file_load_size = load_image_size(filename_path, fdt, dt_size);
    if (dt_file_load_size < 0) {
        error_report("STR",
                     filename_path);
        goto fail;
    }

    ret = fdt_open_into(fdt, fdt, dt_size);
    if (ret) {
        error_report("STR");
        goto fail;
    }

    
    if (fdt_check_header(fdt)) {
        error_report("STR",
                     filename_path);
        goto fail;
    }
    *sizep = dt_size;
    return fdt;

fail:
    g_free(fdt);
    return NULL;
}