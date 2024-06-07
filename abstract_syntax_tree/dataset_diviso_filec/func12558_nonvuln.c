static OPJ_BOOL opj_jpip_write_cidx(opj_jp2_t *jp2,
                                    opj_stream_private_t *cio,
                                    opj_event_mgr_t * p_manager)
{
    OPJ_OFF_T j2k_codestream_exit;
    OPJ_BYTE l_data_header [24];

    OPJ_UNUSED(jp2);

    
    assert(jp2 != 00);
    assert(cio != 00);
    assert(p_manager != 00);
    assert(opj_stream_has_seek(cio));

    j2k_codestream_exit = opj_stream_tell(cio);
    opj_write_bytes(l_data_header, 24, 4); 
    opj_write_bytes(l_data_header + 4, JPIP_CIDX,
                    4);                                      
#if 0
    opj_write_bytes(l_data_header + 4 + 4, 0, 8); 
    opj_write_bytes(l_data_header + 8 + 8, 0, 8); 
#else
    opj_write_double(l_data_header + 4 + 4, 0); 
    opj_write_double(l_data_header + 8 + 8, 0); 
#endif

    if (! opj_stream_seek(cio, j2k_codestream_exit, p_manager)) {
        opj_event_msg(p_manager, EVT_ERROR, "STR");
        return OPJ_FALSE;
    }

    if (opj_stream_write_data(cio, l_data_header, 24, p_manager) != 24) {
        opj_event_msg(p_manager, EVT_ERROR, "STR");
        return OPJ_FALSE;
    }

    j2k_codestream_exit = opj_stream_tell(cio);
    if (! opj_stream_seek(cio, j2k_codestream_exit, p_manager)) {
        opj_event_msg(p_manager, EVT_ERROR, "STR");
        return OPJ_FALSE;
    }

    return OPJ_TRUE;
}