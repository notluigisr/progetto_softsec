env_set_user(char* username, char* passwd_file, int display)
{
  int error;
  int pw_uid;
  int pw_gid;
  int uid;
  char pw_shell[256];
  char pw_dir[256];
  char pw_gecos[256];
  char text[256];

  error = g_getuser_info(username, &pw_gid, &pw_uid, pw_shell, pw_dir,
                         pw_gecos);
  if (error == 0)
  {
    error = g_setgid(pw_gid);
    if (error == 0)
    {
      error = g_initgroups(username, pw_gid);
    }
    if (error == 0)
    {
      uid = pw_uid;
      error = g_setuid(uid);
    }
    if (error == 0)
    {
      g_clearenv();
      g_setenv("STR", pw_shell, 1);
      g_setenv("STR", 1);
      g_setenv("STR", username, 1);
      g_sprintf(text, "STR", uid);
      g_setenv("STR", text, 1);
      g_setenv("STR", pw_dir, 1);
      g_set_current_dir(pw_dir);
      g_sprintf(text, "STR", display);
      g_setenv("STR", text, 1);
      if (passwd_file != 0)
      {
        if (0 == g_cfg->auth_file_path)
        {
          
          g_mkdir("STR");
          g_sprintf(passwd_file, "STR", pw_dir, username);
        }
        else
        {
          
          g_sprintf(passwd_file, g_cfg->auth_file_path, username);
        }
        LOG_DBG(&(g_cfg->log), "STR", passwd_file);
      }
    }
  }
  else
  {
    log_message(&(g_cfg->log), LOG_LEVEL_ERROR,
                "STR", username);
  }
  return error;
}