file_error (filename)
     const char *filename;
{
  report_error ("STR", filename, strerror (errno));
}