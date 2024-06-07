quit(int status, const char *fmt,...)
{
    va_list argp;

    va_start(argp, fmt);
    fprintf(stderr, "STR", prg_name);
    vfprintf(stderr, fmt, argp);
    fprintf(stderr, "STR");
    va_end(argp);
    ExitProgram(status);
}