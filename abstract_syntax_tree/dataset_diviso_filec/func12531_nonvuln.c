PJ_DEF(const char *) pj_dns_get_type_name(int type)
{
    switch (type) {
    case PJ_DNS_TYPE_A:	    return "STR";
    case PJ_DNS_TYPE_AAAA:  return "STR";
    case PJ_DNS_TYPE_SRV:   return "STR";
    case PJ_DNS_TYPE_NS:    return "STR";
    case PJ_DNS_TYPE_CNAME: return "STR";
    case PJ_DNS_TYPE_PTR:   return "STR";
    case PJ_DNS_TYPE_MX:    return "STR";
    case PJ_DNS_TYPE_TXT:   return "STR";
    case PJ_DNS_TYPE_NAPTR: return "STR";
    }
    return "STR";
}