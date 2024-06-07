find_module (lt_dlhandle *handle, const char *dir, const char *libdir,
	     const char *dlname,  const char *old_name, int installed,
	     lt_dladvise advise)
{
  
  if (old_name && tryall_dlopen (handle, old_name, advise, 0) == 0)
    {
      return 0;
    }

  
  if (dlname)
    {
      
      if (installed && libdir)
	{
	  if (tryall_dlopen_module (handle, (const char *) 0,
				    libdir, dlname, advise) == 0)
	    return 0;
	}

      
      if (!installed)
	{
	  if (tryall_dlopen_module (handle, dir, objdir,
				    dlname, advise) == 0)
	    return 0;
	}

      
      {
	  if (dir && (tryall_dlopen_module (handle, (const char *) 0,
					    dir, dlname, advise) == 0))
	    return 0;
      }
    }

  return 1;
}