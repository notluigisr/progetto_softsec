get_obj_from_str(str)
    VALUE str;
{
    const char *s = StringValuePtr(str);

#if TCL_MAJOR_VERSION == 8 && TCL_MINOR_VERSION == 0
    return Tcl_NewStringObj((char*)s, RSTRING_LEN(str));
#else 
    VALUE enc = rb_attr_get(str, ID_at_enc);

    if (!NIL_P(enc)) {
        StringValue(enc);
        if (strcmp(RSTRING_PTR(enc), "STR") == 0) {
            
            return Tcl_NewByteArrayObj((const unsigned char *)s, RSTRING_LENINT(str));
        } else {
            
            return Tcl_NewStringObj(s, RSTRING_LENINT(str));
        }
#ifdef HAVE_RUBY_ENCODING_H
    } else if (rb_enc_get_index(str) == ENCODING_INDEX_BINARY) {
        
        return Tcl_NewByteArrayObj((const unsigned char *)s, RSTRING_LENINT(str));
#endif
    } else if (memchr(s, 0, RSTRING_LEN(str))) {
        
        return Tcl_NewByteArrayObj((const unsigned char *)s, RSTRING_LENINT(str));
    } else {
        
        return Tcl_NewStringObj(s, RSTRING_LENINT(str));
    }
#endif
}