assign_array_element_internal (entry, name, vname, sub, sublen, value, flags)
     SHELL_VAR *entry;
     char *name;		
     char *vname;
     char *sub;
     int sublen;
     char *value;
     int flags;
{
  char *akey;
  arrayind_t ind;

  if (entry && assoc_p (entry))
    {
      sub[sublen-1] = '\0';
      akey = expand_assignment_string_to_string (sub, 0);	
      sub[sublen-1] = ']';
      if (akey == 0 || *akey == 0)
	{
	  err_badarraysub (name);
	  FREE (akey);
	  return ((SHELL_VAR *)NULL);
	}
      entry = bind_assoc_variable (entry, vname, akey, value, flags);
    }
  else
    {
      ind = array_expand_index (entry, sub, sublen);
      
      if (entry && ind < 0)
	ind = (array_p (entry) ? array_max_index (array_cell (entry)) : 0) + 1 + ind;
      if (ind < 0)
	{
	  err_badarraysub (name);
	  return ((SHELL_VAR *)NULL);
	}
      entry = bind_array_variable (vname, ind, value, flags);
    }

  return (entry);
}