get_glyph_class (gunichar   charcode,
		 HB_UShort *class)
{
  
  if ((charcode >= 0xFB50 && charcode <= 0xFDFF) || 
      (charcode >= 0xFE70 && charcode <= 0XFEFF))   
    return FALSE;

  switch ((int) g_unichar_type (charcode))
    {
    case G_UNICODE_COMBINING_MARK:
    case G_UNICODE_ENCLOSING_MARK:
    case G_UNICODE_NON_SPACING_MARK:
      *class = 3;		
      return TRUE;
    case G_UNICODE_UNASSIGNED:
    case G_UNICODE_PRIVATE_USE:
      return FALSE;		
    default:
      *class = 1;               
      return TRUE;
    }
}