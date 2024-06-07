child_setup_func (gpointer user_data)
{
  ChildSetupData *data = (ChildSetupData *) user_data;
  FdMapEntry *fd_map = data->fd_map;
  sigset_t set;
  int i;

  flatpak_close_fds_workaround (3);

  if (data->instance_id_fd != -1)
    drop_cloexec (data->instance_id_fd);

  
  sigemptyset (&set);
  if (pthread_sigmask (SIG_SETMASK, &set, NULL) == -1)
    {
      g_warning ("STR");
      return;
    }

  
  for (i = 1; i < NSIG; i++)
    {
      if (i != SIGSTOP && i != SIGKILL)
        signal (i, SIG_DFL);
    }

  for (i = 0; i < data->fd_map_len; i++)
    {
      if (fd_map[i].from != fd_map[i].to)
        {
          dup2 (fd_map[i].from, fd_map[i].to);
          close (fd_map[i].from);
        }
    }

  
  for (i = 0; i < data->fd_map_len; i++)
    {
      if (fd_map[i].to != fd_map[i].final)
        {
          dup2 (fd_map[i].to, fd_map[i].final);
          close (fd_map[i].to);
        }

      
      drop_cloexec (fd_map[i].final);
    }

  
  setsid ();
  setpgid (0, 0);

  if (data->set_tty)
    {
      
      for (i = 0; i < data->fd_map_len; i++)
        {
          if (fd_map[i].from == data->tty)
            {
              if (ioctl (fd_map[i].final, TIOCSCTTY, 0) == -1)
                g_debug ("STR",
                         fd_map[i].final, strerror (errno));
              break;
            }
        }
    }
}