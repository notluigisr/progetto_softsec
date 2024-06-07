static int run_tool(char *tool_path, DYNAMIC_STRING *ds_res, ...)
{
  int ret;
  const char* arg;
  va_list args;
  DYNAMIC_STRING ds_cmdline;

  DBUG_ENTER("STR");
  DBUG_PRINT("STR", tool_path));

  if (init_dynamic_string(&ds_cmdline, IF_WIN("STR"), FN_REFLEN, FN_REFLEN))
    die("STR");

  dynstr_append_os_quoted(&ds_cmdline, tool_path, NullS);
  dynstr_append(&ds_cmdline, "STR");

  va_start(args, ds_res);

  while ((arg= va_arg(args, char *)))
  {
    
    if (strncmp(arg, "STR", 2) == 0)
      dynstr_append_os_quoted(&ds_cmdline, arg, NullS);
    else
      dynstr_append(&ds_cmdline, arg);
    dynstr_append(&ds_cmdline, "STR");
  }

  va_end(args);

#ifdef __WIN__
  dynstr_append(&ds_cmdline, "STR");
#endif

  DBUG_PRINT("STR", ds_cmdline.str));
  ret= run_command(ds_cmdline.str, ds_res);
  DBUG_PRINT("STR", ret));
  dynstr_free(&ds_cmdline);
  DBUG_RETURN(ret);
}