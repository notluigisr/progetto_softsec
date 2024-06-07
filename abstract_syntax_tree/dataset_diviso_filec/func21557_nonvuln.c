cgi_find_variable(const char *name)	
{
  _cgi_var_t	key;			


  if (form_count < 1 || name == NULL)
    return (NULL);

  key.name = name;

  return ((_cgi_var_t *)bsearch(&key, form_vars, (size_t)form_count, sizeof(_cgi_var_t),
                           (int (*)(const void *, const void *))cgi_compare_variables));
}