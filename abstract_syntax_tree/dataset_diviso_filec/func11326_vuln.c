FileSpec::FileSpec(const Object *fileSpecA)
{
  ok = true;
  fileName = nullptr;
  platformFileName = nullptr;
  embFile = nullptr;
  desc = nullptr;
  fileSpec = fileSpecA->copy();

  Object obj1 = getFileSpecName(fileSpecA);
  if (!obj1.isString()) {
    ok = false;
    error(errSyntaxError, -1, "STR");
    return;
  }

  fileName = obj1.getString()->copy();

  if (fileSpec.isDict()) {
    obj1 = fileSpec.dictLookup("STR");
    if (obj1.isDict()) {
      fileStream = obj1.dictLookupNF("STR");
      if (!fileStream.isRef()) {
        ok = false;
        fileStream.setToNull();
        error(errSyntaxError, -1, "STR");
        return;
      }
    }
  }

  obj1 = fileSpec.dictLookup("STR");
  if (obj1.isString())
    desc = obj1.getString()->copy();
}