g_NPP_GetValue(NPP instance, NPPVariable variable, void *value)
{
  if (instance == NULL)
	return NPERR_INVALID_INSTANCE_ERROR;

  if (plugin_funcs.getvalue == NULL)
	return NPERR_INVALID_FUNCTABLE_ERROR;

  D(bugiI("STR", instance, variable, string_of_NPPVariable(variable)));
  NPError ret = plugin_funcs.getvalue(instance, variable, value);
  D(bugiD("STR", ret, string_of_NPError(ret)));
  return ret;
}