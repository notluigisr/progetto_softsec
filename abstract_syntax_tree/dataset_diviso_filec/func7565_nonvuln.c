rb_str_hex(str)
    VALUE str;
{
    return rb_str_to_inum(str, 16, Qfalse);
}