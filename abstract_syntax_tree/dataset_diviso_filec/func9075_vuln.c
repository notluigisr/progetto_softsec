static OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *p_j2k,
                                  opj_tcd_t * p_tile_coder,
                                  OPJ_BYTE * p_data,
                                  OPJ_UINT32 * p_data_written,
                                  OPJ_UINT32 total_data_size,
                                  const opj_stream_private_t *p_stream,
                                  opj_event_mgr_t * p_manager
                                 )
{
    opj_codestream_info_t *l_cstr_info = 00;
    OPJ_UINT32 l_remaining_data;

    
    assert(p_j2k != 00);
    assert(p_manager != 00);
    assert(p_stream != 00);

    OPJ_UNUSED(p_stream);

    if (total_data_size < 4) {
        opj_event_msg(p_manager, EVT_ERROR,
                      "STR");
        return OPJ_FALSE;
    }

    opj_write_bytes(p_data, J2K_MS_SOD,
                    2);                                 
    p_data += 2;

    
    l_remaining_data =  total_data_size - 4;

    
    p_tile_coder->tp_num =
        p_j2k->m_specific_param.m_encoder.m_current_poc_tile_part_number ;
    p_tile_coder->cur_tp_num =
        p_j2k->m_specific_param.m_encoder.m_current_tile_part_number;

    
    
    
    
    
    
#ifdef USE_JPWL
    
    
    assert(0 && "STR");
#endif 
    
    
    

    if (p_j2k->m_specific_param.m_encoder.m_current_tile_part_number == 0) {
        p_tile_coder->tcd_image->tiles->packno = 0;
#ifdef deadcode
        if (l_cstr_info) {
            l_cstr_info->packno = 0;
        }
#endif
    }

    *p_data_written = 0;

    if (! opj_tcd_encode_tile(p_tile_coder, p_j2k->m_current_tile_number, p_data,
                              p_data_written, l_remaining_data, l_cstr_info,
                              p_manager)) {
        opj_event_msg(p_manager, EVT_ERROR, "STR");
        return OPJ_FALSE;
    }

    *p_data_written += 2;

    return OPJ_TRUE;
}