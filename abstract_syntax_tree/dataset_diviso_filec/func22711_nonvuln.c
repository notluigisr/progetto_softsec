void plugin_thdvar_cleanup(THD *thd)
{
  uint idx;
  plugin_ref *list;
  DBUG_ENTER("STR");

  mysql_mutex_lock(&LOCK_plugin);

  unlock_variables(thd, &thd->variables);
  cleanup_variables(&thd->variables);

  if ((idx= thd->lex->plugins.elements))
  {
    list= ((plugin_ref*) thd->lex->plugins.buffer) + idx - 1;
    DBUG_PRINT("STR", idx));
    while ((uchar*) list >= thd->lex->plugins.buffer)
      intern_plugin_unlock(NULL, *list--);
  }

  reap_plugins();
  mysql_mutex_unlock(&LOCK_plugin);

  reset_dynamic(&thd->lex->plugins);

  DBUG_VOID_RETURN;
}