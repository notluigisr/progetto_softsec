static OPJ_BOOL opj_jp2_read_boxhdr_char(opj_jp2_box_t *box,
        OPJ_BYTE * p_data,
        OPJ_UINT32 * p_number_bytes_read,
        OPJ_UINT32 p_box_max_size,
        opj_event_mgr_t * p_manager
                                        )
{
    OPJ_UINT32 l_value;

    
    assert(p_data != 00);
    assert(box != 00);
    assert(p_number_bytes_read != 00);
    assert(p_manager != 00);

    if (p_box_max_size < 8) {
        opj_event_msg(p_manager, EVT_ERROR, "STR");
        return OPJ_FALSE;
    }

    
    opj_read_bytes(p_data, &l_value, 4);
    p_data += 4;
    box->length = (OPJ_UINT32)(l_value);

    opj_read_bytes(p_data, &l_value, 4);
    p_data += 4;
    box->type = (OPJ_UINT32)(l_value);

    *p_number_bytes_read = 8;

    
    
    if (box->length == 1) {
        OPJ_UINT32 l_xl_part_size;

        if (p_box_max_size < 16) {
            opj_event_msg(p_manager, EVT_ERROR,
                          "STR");
            return OPJ_FALSE;
        }

        opj_read_bytes(p_data, &l_xl_part_size, 4);
        p_data += 4;
        *p_number_bytes_read += 4;

        if (l_xl_part_size != 0) {
            opj_event_msg(p_manager, EVT_ERROR,
                          "STR");
            return OPJ_FALSE;
        }

        opj_read_bytes(p_data, &l_value, 4);
        *p_number_bytes_read += 4;
        box->length = (OPJ_UINT32)(l_value);

        if (box->length == 0) {
            opj_event_msg(p_manager, EVT_ERROR, "STR");
            return OPJ_FALSE;
        }
    } else if (box->length == 0) {
        opj_event_msg(p_manager, EVT_ERROR, "STR");
        return OPJ_FALSE;
    }
    if (box->length < *p_number_bytes_read) {
        opj_event_msg(p_manager, EVT_ERROR, "STR");
        return OPJ_FALSE;
    }
    return OPJ_TRUE;
}