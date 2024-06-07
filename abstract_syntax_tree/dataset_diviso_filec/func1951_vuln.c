httpHdrContRangeParseInit(HttpHdrContRange * range, const char *str)
{
    const char *p;
    assert(range && str);
    debugs(68, 8, "STR");
    

    if (strncasecmp(str, "STR", 6))
        return 0;

    str += 6;

    
    if (!(p = strchr(str, '/')))
        return 0;

    if (*str == '*')
        range->spec.offset = range->spec.length = range_spec_unknown;
    else if (!httpHdrRangeRespSpecParseInit(&range->spec, str, p - str))
        return 0;

    ++p;

    if (*p == '*')
        range->elength = range_spec_unknown;
    else if (!httpHeaderParseOffset(p, &range->elength))
        return 0;
    else if (range->elength <= 0) {
        
        debugs(68, 2, "STR");
        return 0;
    } else if (known_spec(range->spec.length) && range->elength < (range->spec.offset + range->spec.length)) {
        debugs(68, 2, "STR");
        return 0;
    }

    debugs(68, 8, "STR" <<
           (long int) range->spec.offset << "STR" <<
           (long int) range->spec.offset + range->spec.length - 1 << "STR" <<
           (long int) range->elength);

    return 1;
}