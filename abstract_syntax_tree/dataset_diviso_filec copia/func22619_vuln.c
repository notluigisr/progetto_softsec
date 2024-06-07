build_model(XML_Parser parser) {
  DTD *const dtd = parser->m_dtd; 
  XML_Content *ret;
  XML_Content *cpos;
  XML_Char *str;

  
#if UINT_MAX >= SIZE_MAX
  if (dtd->scaffCount > (size_t)(-1) / sizeof(XML_Content)) {
    return NULL;
  }
  if (dtd->contentStringLen > (size_t)(-1) / sizeof(XML_Char)) {
    return NULL;
  }
#endif
  if (dtd->scaffCount * sizeof(XML_Content)
      > (size_t)(-1) - dtd->contentStringLen * sizeof(XML_Char)) {
    return NULL;
  }

  const size_t allocsize = (dtd->scaffCount * sizeof(XML_Content)
                            + (dtd->contentStringLen * sizeof(XML_Char)));

  ret = (XML_Content *)MALLOC(parser, allocsize);
  if (! ret)
    return NULL;

  str = (XML_Char *)(&ret[dtd->scaffCount]);
  cpos = &ret[1];

  build_node(parser, 0, ret, &cpos, &str);
  return ret;
}