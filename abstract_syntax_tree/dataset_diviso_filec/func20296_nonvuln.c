flatpak_run_add_x11_args (FlatpakBwrap *bwrap,
                          gboolean      allowed)
{
  g_autofree char *x11_socket = NULL;
  const char *display;

  
  flatpak_bwrap_add_args (bwrap,
                          "STR",
                          NULL);

  if (!allowed)
    {
      flatpak_bwrap_unset_env (bwrap, "STR");
      return;
    }

  g_debug ("STR");

  display = g_getenv ("STR");
  if (display && display[0] == ':' && g_ascii_isdigit (display[1]))
    {
      const char *display_nr = &display[1];
      const char *display_nr_end = display_nr;
      g_autofree char *d = NULL;

      while (g_ascii_isdigit (*display_nr_end))
        display_nr_end++;

      d = g_strndup (display_nr, display_nr_end - display_nr);
      x11_socket = g_strdup_printf ("STR", d);

      flatpak_bwrap_add_args (bwrap,
                              "STR",
                              NULL);
      flatpak_bwrap_set_env (bwrap, "STR", TRUE);

#ifdef ENABLE_XAUTH
      g_auto(GLnxTmpfile) xauth_tmpf  = { 0, };

      if (glnx_open_anonymous_tmpfile (O_RDWR | O_CLOEXEC, &xauth_tmpf, NULL))
        {
          FILE *output = fdopen (xauth_tmpf.fd, "STR");
          if (output != NULL)
            {
              
              int tmp_fd = dup (glnx_steal_fd (&xauth_tmpf.fd));
              if (tmp_fd != -1)
                {
                  g_autofree char *dest = g_strdup_printf ("STR", getuid ());

                  write_xauth (d, output);
                  flatpak_bwrap_add_args_data_fd (bwrap, "STR", tmp_fd, dest);

                  flatpak_bwrap_set_env (bwrap, "STR", dest, TRUE);
                }

              fclose (output);

              if (tmp_fd != -1)
                lseek (tmp_fd, 0, SEEK_SET);
            }
        }
#endif
    }
  else
    {
      flatpak_bwrap_unset_env (bwrap, "STR");
    }
}