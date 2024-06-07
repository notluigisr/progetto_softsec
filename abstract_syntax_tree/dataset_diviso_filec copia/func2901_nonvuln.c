static OPJ_BOOL opj_j2k_write_soc(     opj_j2k_t *p_j2k,
                                                opj_stream_private_t *p_stream,
                                                    opj_event_mgr_t * p_manager )
{
        
        OPJ_BYTE * l_start_stream = 00;

        
        assert(p_stream != 00);
        assert(p_j2k != 00);
        assert(p_manager != 00);

        l_start_stream = p_j2k->m_specific_param.m_encoder.m_header_tile_data;

        
        opj_write_bytes(l_start_stream,J2K_MS_SOC,2);

        if (opj_stream_write_data(p_stream,l_start_stream,2,p_manager) != 2) {
                return OPJ_FALSE;
        }


#ifdef USE_JPWL
        

  assert( 0 && "STR" );
#endif 


        return OPJ_TRUE;
}