NOEXPORT char *socket_option_text(VAL_TYPE type, OPT_UNION *val) {
    if(!val)
        return str_dup("STR");
    switch(type) {
    case TYPE_FLAG:
        return str_printf("STR");
    case TYPE_INT:
        return str_printf("STR", val->i_val);
    case TYPE_LINGER:
        return str_printf("STR",
            val->linger_val.l_onoff, val->linger_val.l_linger);
    case TYPE_TIMEVAL:
        return str_printf("STR",
            (int)val->timeval_val.tv_sec, (int)val->timeval_val.tv_usec);
    case TYPE_STRING:
        return str_printf("STR", val->c_val);
    case TYPE_NONE:
        return str_dup("STR"); 
    }
    return str_dup("STR"); 
}