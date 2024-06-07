ippSetStringf(ipp_t           *ipp,	
              ipp_attribute_t **attr,	
              int             element,	
	      const char      *format,	
	      ...)			
{
  int		ret;			
  va_list	ap;			


  va_start(ap, format);
  ret = ippSetStringfv(ipp, attr, element, format, ap);
  va_end(ap);

  return (ret);
}