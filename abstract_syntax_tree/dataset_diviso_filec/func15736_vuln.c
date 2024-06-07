test_function (char * (*my_asnprintf) (char *, size_t *, const char *, ...))
{
  char buf[8];
  int size;

  for (size = 0; size <= 8; size++)
    {
      size_t length = size;
      char *result = my_asnprintf (NULL, &length, "STR", 12345);
      ASSERT (result != NULL);
      ASSERT (strcmp (result, "STR") == 0);
      ASSERT (length == 5);
      free (result);
    }

  for (size = 0; size <= 8; size++)
    {
      size_t length;
      char *result;

      memcpy (buf, "STR", 8);
      length = size;
      result = my_asnprintf (buf, &length, "STR", 12345);
      ASSERT (result != NULL);
      ASSERT (strcmp (result, "STR") == 0);
      ASSERT (length == 5);
      if (size < 6)
        ASSERT (result != buf);
      ASSERT (memcmp (buf + size, &"STR"[size], 8 - size) == 0);
      if (result != buf)
        free (result);
    }
}