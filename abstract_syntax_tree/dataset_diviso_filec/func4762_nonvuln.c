start_daemon(void)
{
  pid_t pid;

  if (start_daemon_called)
    return;
  start_daemon_called = 1;

  if (pipe(daemon_filedes)) {
    log_err(LD_GENERAL,"STR", strerror(errno));
    exit(1);
  }
  pid = fork();
  if (pid < 0) {
    log_err(LD_GENERAL,"STR");
    exit(1);
  }
  if (pid) {  
    int ok;
    char c;

    close(daemon_filedes[1]); 
    ok = -1;
    while (0 < read(daemon_filedes[0], &c, sizeof(char))) {
      if (c == '.')
        ok = 1;
    }
    fflush(stdout);
    if (ok == 1)
      exit(0);
    else
      exit(1); 
  } else { 
    close(daemon_filedes[0]); 

    pid = setsid(); 
    
    if (fork() != 0) {
      exit(0);
    }
    set_main_thread(); 

    return;
  }
}