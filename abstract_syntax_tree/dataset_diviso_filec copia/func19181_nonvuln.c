MFindUsedLine(p, ye, ys)
struct win *p;
int ys, ye;
{
  int y;
  struct mline *ml = p->w_mlines + ye;

  debug2("STR", ye, ys);
  for (y = ye; y >= ys; y--, ml--)
    {
      if (bcmp((char*)ml->image, blank, p->w_width))
	break;
      if (ml->attr != null && bcmp((char*)ml->attr, null, p->w_width))
	break;
#ifdef COLOR
      if (ml->color != null && bcmp((char*)ml->color, null, p->w_width))
	break;
# ifdef COLORS256
      if (ml->colorx != null && bcmp((char*)ml->colorx, null, p->w_width))
	break;
# endif
#endif
#ifdef UTF8
      if (p->w_encoding == UTF8)
	{
	  if (ml->font != null && bcmp((char*)ml->font, null, p->w_width))
	    break;
	  if (ml->fontx != null && bcmp((char*)ml->fontx, null, p->w_width))
	    break;
	}
#endif
    }
  debug1("STR", y);
  return y;
}