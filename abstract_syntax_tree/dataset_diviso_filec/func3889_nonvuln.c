OPJ_BOOL OPJ_CALLCONV opj_set_decode_area(opj_codec_t *p_codec,
        opj_image_t* p_image,
        OPJ_INT32 p_start_x, OPJ_INT32 p_start_y,
        OPJ_INT32 p_end_x, OPJ_INT32 p_end_y
                                         )
{
    if (p_codec) {
        opj_codec_private_t * l_codec = (opj_codec_private_t *) p_codec;

        if (! l_codec->is_decompressor) {
            return OPJ_FALSE;
        }

        return  l_codec->m_codec_data.m_decompression.opj_set_decode_area(
                    l_codec->m_codec,
                    p_image,
                    p_start_x, p_start_y,
                    p_end_x, p_end_y,
                    &(l_codec->m_event_mgr));
    }
    return OPJ_FALSE;
}