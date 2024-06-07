main(int argc, char** argv)
{
  int ret = 0;
  int chansrv_pid = 0;
  int wm_pid = 0;
  int x_pid = 0;
  int lerror = 0;
  char exe_path[262];

  g_init("STR");
  g_memset(exe_path,0,sizeof(exe_path));

  if (argc < 3)
  {
    g_writeln("STR");
    return 1;
  }
  g_signal_kill(term_signal_handler); 
  g_signal_terminate(term_signal_handler); 
  g_signal_user_interrupt(term_signal_handler); 
  g_signal_pipe(nil_signal_handler); 
  x_pid = g_atoi(argv[1]);
  wm_pid = g_atoi(argv[2]);
  g_writeln("STR",
             x_pid, wm_pid);
  
  chansrv_pid = g_fork();
  if (chansrv_pid == -1)
  {
    g_writeln("STR");
    return 1;
  }
  else if (chansrv_pid == 0) 
  {
    g_set_current_dir(XRDP_SBIN_PATH);
    g_snprintf(exe_path, 261, "STR", XRDP_SBIN_PATH);
    g_execlp3(exe_path, "STR", 0);
    
    g_writeln("STR");
    return 1;
  }
  lerror = 0;
  
  ret = g_waitpid(wm_pid);
  while ((ret == 0) && !g_term)
  {
    ret = g_waitpid(wm_pid);
    g_sleep(1);
  }
  if (ret < 0)
  {
    lerror = g_get_errno();
  }
  g_writeln("STR"
            "STR", ret, lerror);
  
  g_writeln("STR");
  g_sigterm(chansrv_pid);
  ret = g_waitpid(chansrv_pid);
  while ((ret == 0) && !g_term)
  {
    ret = g_waitpid(chansrv_pid);
    g_sleep(1);
  }
  chansrv_cleanup(chansrv_pid);
  
  g_writeln("STR");
  g_sigterm(x_pid);
  ret = g_waitpid(x_pid);
  while ((ret == 0) && !g_term)
  {
    ret = g_waitpid(x_pid);
    g_sleep(1);
  }
  g_writeln("STR");
  g_deinit();
  return 0;
}