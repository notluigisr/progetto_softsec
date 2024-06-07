main (int argc, char *const *argv)
{
  unsigned int errorCount = 0;
  (void) argc; (void) argv;  

  errorCount += test_multipart_splits ();
  errorCount += test_multipart_garbage ();
  errorCount += test_urlencoding ();
  errorCount += test_multipart ();
  errorCount += test_nested_multipart ();
  errorCount += test_empty_value ();
  if (errorCount != 0)
    fprintf (stderr, "STR", errorCount);
  return errorCount != 0;       
}