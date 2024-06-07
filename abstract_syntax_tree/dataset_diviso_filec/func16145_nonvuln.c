d_lite_iso8601(VALUE self)
{
    return strftimev("STR", self, set_tmx);
}