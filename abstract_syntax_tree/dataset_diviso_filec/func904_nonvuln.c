d_lite_httpdate(VALUE self)
{
    volatile VALUE dup = dup_obj_with_new_offset(self, 0);
    return strftimev("STR", dup, set_tmx);
}