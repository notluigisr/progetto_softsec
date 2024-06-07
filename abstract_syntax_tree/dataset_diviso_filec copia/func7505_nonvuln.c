static int write_fidx(int offset_jp2c, int length_jp2c, int offset_idx,
                      int length_idx, opj_stream_private_t *cio,
                      opj_event_mgr_t * p_manager)
{
    OPJ_BYTE l_data_header [4];
    OPJ_OFF_T len, lenp;

    lenp = opj_stream_tell(cio);
    opj_stream_skip(cio, 4, p_manager);
    opj_write_bytes(l_data_header, JPIP_FIDX, 4); 
    opj_stream_write_data(cio, l_data_header, 4, p_manager);

    write_prxy(offset_jp2c, length_jp2c, offset_idx, length_idx, cio, p_manager);

    len = opj_stream_tell(cio) - lenp;
    opj_stream_skip(cio, lenp, p_manager);
    opj_write_bytes(l_data_header, len, 4); 
    opj_stream_write_data(cio, l_data_header, 4, p_manager);
    opj_stream_seek(cio, lenp + len, p_manager);

    return len;
}