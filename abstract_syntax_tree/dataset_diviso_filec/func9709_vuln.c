disable_priv_mode ()
{
  int e;

  if (setuid (current_user.uid) < 0)
    {
      e = errno;
      sys_error (_("STR"), current_user.uid, current_user.euid);
#if defined (EXIT_ON_SETUID_FAILURE)
      if (e == EAGAIN)
	exit (e);
#endif
    }
  if (setgid (current_user.gid) < 0)
    sys_error (_("STR"), current_user.gid, current_user.egid);

  current_user.euid = current_user.uid;
  current_user.egid = current_user.gid;
}