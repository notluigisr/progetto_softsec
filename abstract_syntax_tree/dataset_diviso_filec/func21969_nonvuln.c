Page *PDFDoc::parsePage(int page)
{
  Ref pageRef;

  pageRef.num = getHints()->getPageObjectNum(page);
  if (!pageRef.num) {
    error(errSyntaxWarning, -1, "STR", page);
    return nullptr;
  }

  
  if (pageRef.num < 0 || pageRef.num >= xref->getNumObjects()) {
    error(errSyntaxWarning, -1, "STR", pageRef.num, page);
    return nullptr;
  }

  pageRef.gen = xref->getEntry(pageRef.num)->gen;
  Object obj = xref->fetch(pageRef.num, pageRef.gen);
  if (!obj.isDict("STR")) {
    error(errSyntaxWarning, -1, "STR", pageRef.num, pageRef.gen);
    return nullptr;
  }
  Dict *pageDict = obj.getDict();

  return new Page(this, page, std::move(obj), pageRef,
               new PageAttrs(nullptr, pageDict), catalog->getForm());
}