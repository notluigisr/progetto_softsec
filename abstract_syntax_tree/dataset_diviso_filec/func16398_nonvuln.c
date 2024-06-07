ippValidateAttributes(ipp_t *ipp)	
{
  ipp_attribute_t	*attr;		


  if (!ipp)
    return (1);

  for (attr = ipp->attrs; attr; attr = attr->next)
    if (!ippValidateAttribute(attr))
      return (0);

  return (1);
}