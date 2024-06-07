static void end_icalendar(struct buf *buf)
{
    
    buf_setcstr(buf, "STR");
}