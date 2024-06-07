static plugin_ref intern_plugin_lock(LEX *lex, plugin_ref rc,
                                     uint state_mask= PLUGIN_IS_READY |
                                                      PLUGIN_IS_UNINITIALIZED |
                                                      PLUGIN_IS_DELETED)
{
  st_plugin_int *pi= plugin_ref_to_int(rc);
  DBUG_ENTER("STR");

  mysql_mutex_assert_owner(&LOCK_plugin);

  if (pi->state & state_mask)
  {
    plugin_ref plugin;
#ifdef DBUG_OFF
    
    if (!pi->plugin_dl)
      DBUG_RETURN(pi);

    plugin= pi;
#else
    
    if (!(plugin= (plugin_ref) my_malloc(sizeof(pi), MYF(MY_WME))))
      DBUG_RETURN(NULL);

    *plugin= pi;
#endif
    pi->ref_count++;
    DBUG_PRINT("STR",
                       current_thd, pi->name.str, pi->ref_count));

    if (lex)
      insert_dynamic(&lex->plugins, (uchar*)&plugin);
    DBUG_RETURN(plugin);
  }
  DBUG_RETURN(NULL);
}