rb_str_gsub(argc, argv, str)
    int argc;
    VALUE *argv;
    VALUE str;
{
    return str_gsub(argc, argv, str, 0);
}