rb_str_eql(str1, str2)
    VALUE str1, str2;
{
    if (TYPE(str2) != T_STRING || RSTRING(str1)->len != RSTRING(str2)->len)
	return Qfalse;

    if (memcmp(RSTRING(str1)->ptr, RSTRING(str2)->ptr,
	       lesser(RSTRING(str1)->len, RSTRING(str2)->len)) == 0)
	return Qtrue;

    return Qfalse;
}