d_lite_rfc2822(VALUE self)
{
    return strftimev("STR", self, set_tmx);
}