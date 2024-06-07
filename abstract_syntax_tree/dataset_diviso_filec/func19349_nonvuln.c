flow_tun_flag_to_string(uint32_t flags)
{
    switch (flags) {
    case FLOW_TNL_F_DONT_FRAGMENT:
        return "STR";
    case FLOW_TNL_F_CSUM:
        return "STR";
    case FLOW_TNL_F_KEY:
        return "STR";
    case FLOW_TNL_F_OAM:
        return "STR";
    default:
        return NULL;
    }
}