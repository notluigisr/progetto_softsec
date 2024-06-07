static OPJ_BOOL opj_j2k_decoding_validation (  opj_j2k_t *p_j2k,
                                        opj_stream_private_t *p_stream,
                                        opj_event_mgr_t * p_manager
                                        )
{
        OPJ_BOOL l_is_valid = OPJ_TRUE;

        
        assert(p_j2k != 00);
        assert(p_stream != 00);
        assert(p_manager != 00);

        
        
#ifdef TODO_MSD
        l_is_valid &= (p_j2k->m_specific_param.m_decoder.m_state == J2K_DEC_STATE_NONE);
#endif
        l_is_valid &= (p_j2k->m_specific_param.m_decoder.m_state == 0x0000);

        
        
        
        l_is_valid &= (p_j2k->m_procedure_list != 00);
        
        l_is_valid &= (p_j2k->m_validation_list != 00);

        
        return l_is_valid;
}