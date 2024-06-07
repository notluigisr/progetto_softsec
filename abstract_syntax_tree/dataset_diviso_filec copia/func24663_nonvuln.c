static int do_auth_once(THD *thd, LEX_STRING *auth_plugin_name,
                        MPVIO_EXT *mpvio)
{
  DBUG_ENTER("STR");
  int res= CR_OK, old_status= MPVIO_EXT::FAILURE;
  bool unlock_plugin= false;
  plugin_ref plugin= NULL;

  if (auth_plugin_name->str == native_password_plugin_name.str)
    plugin= native_password_plugin;
#ifndef EMBEDDED_LIBRARY
  else
  if (auth_plugin_name->str == old_password_plugin_name.str)
    plugin= old_password_plugin;
  else
  {
    if (auth_plugin_name->length == 0)
    {
      auth_plugin_name->str= default_auth_plugin_name.str;
      auth_plugin_name->length= default_auth_plugin_name.length;
    }
    if ((plugin= my_plugin_lock_by_name(thd, auth_plugin_name,
                                        MYSQL_AUTHENTICATION_PLUGIN)))
      unlock_plugin= true;
  }
#endif

    
  mpvio->plugin= plugin;
  old_status= mpvio->status;
  
  if (plugin)
  {
    st_mysql_auth *auth= (st_mysql_auth *) plugin_decl(plugin)->info;
    res= auth->authenticate_user(mpvio, &mpvio->auth_info);

    if (unlock_plugin)
      plugin_unlock(thd, plugin);
  }
  else
  {
    
    Host_errors errors;
    errors.m_no_auth_plugin= 1;
    inc_host_errors(mpvio->ip, &errors);
    my_error(ER_PLUGIN_IS_NOT_LOADED, MYF(0), auth_plugin_name->str);
    res= CR_ERROR;
  }

  
  if (old_status == MPVIO_EXT::RESTART && mpvio->status == MPVIO_EXT::RESTART)
    mpvio->status= MPVIO_EXT::FAILURE; 

  DBUG_RETURN(res);
}