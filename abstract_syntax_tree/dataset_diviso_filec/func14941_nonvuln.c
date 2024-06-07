static void console_respond_str(QemuConsole *s, const char *buf)
{
    while (*buf) {
        console_put_one(s, *buf);
        buf++;
    }
}