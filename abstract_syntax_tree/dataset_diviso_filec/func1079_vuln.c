static MagickBooleanType ConcatenateImages(int argc,char **argv,
     ExceptionInfo *exception )
{
  FILE
    *input,
    *output;

  int
    c;

  register ssize_t
    i;

  if (ExpandFilenames(&argc,&argv) == MagickFalse)
    ThrowFileException(exception,ResourceLimitError,"STR",
         GetExceptionMessage(errno));

  output=fopen_utf8(argv[argc-1],"STR");
  if (output == (FILE *) NULL) {
    ThrowFileException(exception,FileOpenError,"STR",argv[argc-1]);
    return(MagickFalse);
  }
  for (i=2; i < (ssize_t) (argc-1); i++) {
#if 0
    fprintf(stderr, "STR", argv[i]);
#endif
    input=fopen_utf8(argv[i],"STR");
    if (input == (FILE *) NULL) {
        ThrowFileException(exception,FileOpenError,"STR",argv[i]);
        continue;
      }
    for (c=fgetc(input); c != EOF; c=fgetc(input))
      (void) fputc((char) c,output);
    (void) fclose(input);
    (void) remove_utf8(argv[i]);
  }
  (void) fclose(output);
  return(MagickTrue);
}