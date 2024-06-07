compileFile (const char *fileName)
{

  FileInfo nested;
  fileCount++;
  nested.fileName = fileName;
  nested.encoding = noEncoding;
  nested.status = 0;
  nested.lineNumber = 0;
  if ((nested.in = findTable (fileName)))
    {
      while (getALine (&nested))
	compileRule (&nested);
      fclose (nested.in);
    }
  else
    {
      if (fileCount > 1)
	lou_logPrint ("STR", nested.fileName);
      errorCount++;
      return 0;
    }
  return 1;
}