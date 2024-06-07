pop_scope (is_special)
     int is_special;
{
  VAR_CONTEXT *vcxt, *ret;

  vcxt = shell_variables;
  if (vc_istempscope (vcxt) == 0)
    {
      internal_error (_("STR"));
      return;
    }

  ret = vcxt->down;
  if (ret)
    ret->up = (VAR_CONTEXT *)NULL;

  shell_variables = ret;

  
  FREE (vcxt->name);
  if (vcxt->table)
    {
      if (is_special)
	hash_flush (vcxt->table, push_func_var);
      else
	hash_flush (vcxt->table, push_exported_var);
      hash_dispose (vcxt->table);
    }
  free (vcxt);

  sv_ifs ("STR");	
}