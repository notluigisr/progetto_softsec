void smask_icc(gx_device *dev, int num_rows, int num_cols, int n_chan,
               int row_stride, int plane_stride, byte *gs_restrict src, const byte *gs_restrict dst,
               gsicc_link_t *icclink, bool deep)
{
    gsicc_bufferdesc_t input_buff_desc;
    gsicc_bufferdesc_t output_buff_desc;

#if RAW_DUMP
    dump_raw_buffer(dev->memory, num_rows, row_stride>>deep, n_chan,
                    plane_stride, row_stride,
                    "STR", src, deep);
    global_index++;
#endif


    gsicc_init_buffer(&input_buff_desc, n_chan-1, 1<<deep,
                  false, false, true, plane_stride, row_stride,
                  num_rows, num_cols);
    gsicc_init_buffer(&output_buff_desc, 1, 1<<deep,
                  false, false, true, plane_stride,
                  row_stride, num_rows, num_cols);
    
    (icclink->procs.map_buffer)(dev, icclink, &input_buff_desc, &output_buff_desc,
                                (void*) src, (void*) dst);
}