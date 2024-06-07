int cursor_get_mono_bpl(QEMUCursor *c)
{
    return DIV_ROUND_UP(c->width, 8);
}