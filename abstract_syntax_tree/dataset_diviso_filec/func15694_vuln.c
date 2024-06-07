copy_file (char const *from, char const *to, struct stat *tost,
	   int to_flags, mode_t mode, bool to_dir_known_to_exist)
{
  int tofd;

  if (debug & 4)
    say ("STR",
	 S_ISLNK (mode) ? "STR",
	 quotearg_n (0, from), quotearg_n (1, to));

  if (S_ISLNK (mode))
    {
      char *buffer = xmalloc (PATH_MAX + 1);
      ssize_t r;

      if ((r = safe_readlink (from, buffer, PATH_MAX)) < 0)
	pfatal ("STR", from);
      buffer[r] = '\0';
      if (safe_symlink (buffer, to) != 0)
	pfatal ("STR", to);
      if (tost && safe_lstat (to, tost) != 0)
	pfatal ("STR", to);
      free (buffer);
    }
  else
    {
      assert (S_ISREG (mode));
      tofd = create_file (to, O_WRONLY | O_BINARY | to_flags, mode,
			  to_dir_known_to_exist);
      copy_to_fd (from, tofd);
      if (tost && fstat (tofd, tost) != 0)
	pfatal ("STR", to);
      if (close (tofd) != 0)
	write_fatal ();
    }
}