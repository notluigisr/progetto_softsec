static const char *begin_icalendar(struct buf *buf)
{
    
    buf_setcstr(buf, "STR");
    buf_printf(buf, "STR", ical_prodid);
    buf_appendcstr(buf, "STR");

    return "";
}