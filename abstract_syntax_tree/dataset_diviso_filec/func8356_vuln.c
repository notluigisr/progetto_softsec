static const char *GetOpenCLCacheDirectory()
{
  if (cache_directory == (char *) NULL)
    {
      if (cache_directory_lock == (SemaphoreInfo *) NULL)
        ActivateSemaphoreInfo(&cache_directory_lock);
      LockSemaphoreInfo(cache_directory_lock);
      if (cache_directory == (char *) NULL)
        {
          char
            *home,
            path[MagickPathExtent],
            *temp;

          MagickBooleanType
            status;

          struct stat
            attributes;

          temp=(char *) NULL;
          home=GetEnvironmentValue("STR");
          if (home == (char *) NULL)
            {
              home=GetEnvironmentValue("STR");
              if (home == (char *) NULL)
                home=GetEnvironmentValue("STR");
              if (home == (char *) NULL)
                home=GetEnvironmentValue("STR");
              if (home == (char *) NULL)
                home=GetEnvironmentValue("STR");
            }

          if (home != (char *) NULL)
            {
              
              (void) FormatLocaleString(path,MagickPathExtent,"STR",home);
              status=GetPathAttributes(path,&attributes);
              if (status == MagickFalse)
                status=MagickCreateDirectory(path);

              
              if (status != MagickFalse)
                {
                  (void) FormatLocaleString(path,MagickPathExtent,
                    "STR",home,DirectorySeparator);

                  status=GetPathAttributes(path,&attributes);
                  if (status == MagickFalse)
                    status=MagickCreateDirectory(path);
                }

              if (status != MagickFalse)
                {
                  temp=(char*) AcquireMagickMemory(strlen(path)+1);
                  CopyMagickString(temp,path,strlen(path)+1);
                }
              home=DestroyString(home);
            }
          else
            {
              home=GetEnvironmentValue("STR");
              if (home != (char *) NULL)
                {
                  
                  (void) FormatLocaleString(path,MagickPathExtent,"STR",
                    home,DirectorySeparator);
                  status=GetPathAttributes(path,&attributes);
                  if (status == MagickFalse)
                    status=MagickCreateDirectory(path);

                  
                  if (status != MagickFalse)
                    {
                      (void) FormatLocaleString(path,MagickPathExtent,
                        "STR",home,DirectorySeparator,
                        DirectorySeparator);
                      status=GetPathAttributes(path,&attributes);
                      if (status == MagickFalse)
                        status=MagickCreateDirectory(path);
                    }

                  if (status != MagickFalse)
                    {
                      temp=(char*) AcquireMagickMemory(strlen(path)+1);
                      CopyMagickString(temp,path,strlen(path)+1);
                    }
                  home=DestroyString(home);
                }
            }
          if (temp == (char *) NULL)
            temp=AcquireString("STR");
          cache_directory=temp;
        }
      UnlockSemaphoreInfo(cache_directory_lock);
    }
  if (*cache_directory == '?')
    return((const char *) NULL);
  return(cache_directory);
}