prefix_array (const char *dirname, char **array, size_t n)
{
  size_t i;
  size_t dirlen = strlen (dirname);
  char dirsep_char = '/';

  if (dirlen == 1 && dirname[0] == '/')
    
    dirlen = 0;

#if defined __MSDOS__ || defined WINDOWS32
  if (dirlen > 1)
    {
      if (dirname[dirlen - 1] == '/' && dirname[dirlen - 2] == ':')
        
        --dirlen;
      else if (dirname[dirlen - 1] == ':')
        {
          
          --dirlen;
          dirsep_char = ':';
        }
    }
#endif

  for (i = 0; i < n; ++i)
    {
      size_t eltlen = strlen (array[i]) + 1;
      char *new = malloc (dirlen + 1 + eltlen);
      if (new == NULL)
        {
          while (i > 0)
            free (array[--i]);
          return 1;
        }

      {
        char *endp = mempcpy (new, dirname, dirlen);
        *endp++ = dirsep_char;
        mempcpy (endp, array[i], eltlen);
      }
      free (array[i]);
      array[i] = new;
    }

  return 0;
}