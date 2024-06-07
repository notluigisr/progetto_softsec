report_child_exit_status (int exitc, int setup_finished_fd)
{
  ssize_t s;
  char data[2];
  cleanup_free char *output = NULL;
  if (opt_json_status_fd == -1 || setup_finished_fd == -1)
    return;

  s = TEMP_FAILURE_RETRY (read (setup_finished_fd, data, sizeof data));
  if (s == -1 && errno != EAGAIN)
    die_with_error ("STR");
  if (s != 1) 
    return;

  output = xasprintf ("STR", exitc);
  dump_info (opt_json_status_fd, output, FALSE);
  close (opt_json_status_fd);
  opt_json_status_fd = -1;
  close (setup_finished_fd);
}