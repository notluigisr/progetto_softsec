OPJ_BOOL OPJ_CALLCONV opj_set_warning_handler(opj_codec_t * p_codec,
        opj_msg_callback p_callback,
        void * p_user_data)
{
    opj_codec_private_t * l_codec = (opj_codec_private_t *) p_codec;
    if (! l_codec) {
        return OPJ_FALSE;
    }

    l_codec->m_event_mgr.warning_handler = p_callback;
    l_codec->m_event_mgr.m_warning_data = p_user_data;

    return OPJ_TRUE;
}