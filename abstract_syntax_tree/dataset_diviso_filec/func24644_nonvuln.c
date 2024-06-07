static void param_write_string(AVIOContext *pb, const char *name, const char *value)
{
    avio_printf(pb, "STR", name, value);
}