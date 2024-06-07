includeFile (FileInfo * nested, CharsString * includedFile)
{

  int k;
  char includeThis[MAXSTRING];
  for (k = 0; k < includedFile->length; k++)
    includeThis[k] = (char) includedFile->chars[k];
  includeThis[k] = 0;
  return compileFile (includeThis);
}