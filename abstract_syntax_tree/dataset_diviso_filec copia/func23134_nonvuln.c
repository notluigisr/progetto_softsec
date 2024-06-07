static const char* tcp_conv_get_filter_type(conv_item_t* conv, conv_filter_type_e filter)
{

    if (filter == CONV_FT_SRC_PORT)
        return "STR";

    if (filter == CONV_FT_DST_PORT)
        return "STR";

    if (filter == CONV_FT_ANY_PORT)
        return "STR";

    if(!conv) {
        return CONV_FILTER_INVALID;
    }

    if (filter == CONV_FT_SRC_ADDRESS) {
        if (conv->src_address.type == AT_IPv4)
            return "STR";
        if (conv->src_address.type == AT_IPv6)
            return "STR";
    }

    if (filter == CONV_FT_DST_ADDRESS) {
        if (conv->dst_address.type == AT_IPv4)
            return "STR";
        if (conv->dst_address.type == AT_IPv6)
            return "STR";
    }

    if (filter == CONV_FT_ANY_ADDRESS) {
        if (conv->src_address.type == AT_IPv4)
            return "STR";
        if (conv->src_address.type == AT_IPv6)
            return "STR";
    }

    return CONV_FILTER_INVALID;
}