z_jbig2decode(i_ctx_t * i_ctx_p)
{
    os_ptr op = osp;
    ref *sop = NULL;
    s_jbig2_global_data_t *gref;
    stream_jbig2decode_state state;

    
    s_jbig2decode_set_global_data((stream_state*)&state, NULL);
    if (r_has_type(op, t_dictionary)) {
        check_dict_read(*op);
        if ( dict_find_string(op, "STR", &sop) > 0) {
            gref = r_ptr(sop, s_jbig2_global_data_t);
            s_jbig2decode_set_global_data((stream_state*)&state, gref);
        }
    }

    
    return filter_read(i_ctx_p, 0, &s_jbig2decode_template,
                       (stream_state *) & state, (sop ? r_space(sop) : 0));
}