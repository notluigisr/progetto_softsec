static OPJ_BOOL opj_jp2_setup_header_writing(opj_jp2_t *jp2,
        opj_event_mgr_t * p_manager)
{
    
    assert(jp2 != 00);
    assert(p_manager != 00);

    if (! opj_procedure_list_add_procedure(jp2->m_procedure_list,
                                           (opj_procedure)opj_jp2_write_jp, p_manager)) {
        return OPJ_FALSE;
    }
    if (! opj_procedure_list_add_procedure(jp2->m_procedure_list,
                                           (opj_procedure)opj_jp2_write_ftyp, p_manager)) {
        return OPJ_FALSE;
    }
    if (! opj_procedure_list_add_procedure(jp2->m_procedure_list,
                                           (opj_procedure)opj_jp2_write_jp2h, p_manager)) {
        return OPJ_FALSE;
    }
    if (jp2->jpip_on) {
        if (! opj_procedure_list_add_procedure(jp2->m_procedure_list,
                                               (opj_procedure)opj_jpip_skip_iptr, p_manager)) {
            return OPJ_FALSE;
        }
    }
    if (! opj_procedure_list_add_procedure(jp2->m_procedure_list,
                                           (opj_procedure)opj_jp2_skip_jp2c, p_manager)) {
        return OPJ_FALSE;
    }

    

    return OPJ_TRUE;
}