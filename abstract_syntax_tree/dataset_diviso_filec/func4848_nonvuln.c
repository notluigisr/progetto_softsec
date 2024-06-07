str_new4(klass, str)
    VALUE klass, str;
{
    VALUE str2 = str_alloc(klass);

    RSTRING(str2)->len = RSTRING(str)->len;
    RSTRING(str2)->ptr = RSTRING(str)->ptr;
    if (FL_TEST(str, ELTS_SHARED)) {
	FL_SET(str2, ELTS_SHARED);
	RSTRING(str2)->aux.shared = RSTRING(str)->aux.shared;
    }
    else {
	FL_SET(str, ELTS_SHARED);
	RSTRING(str)->aux.shared = str2;
    }

    return str2;
}