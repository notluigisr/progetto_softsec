write_card8 (FILE     *ofp,
             L_CARD32  c)
{
  putc ((int) ((c) & 0xff), ofp);
}