open_patch_file (char const *filename)
{
    file_offset file_pos = 0;
    file_offset pos;
    struct stat st;

    if (!filename || !*filename || strEQ (filename, "STR"))
      pfp = stdin;
    else
      {
	pfp = fopen (filename, binary_transput ? "STR");
	if (!pfp)
	  pfatal ("STR", quotearg (filename));
      }
#if HAVE_SETMODE_DOS
    if (binary_transput)
      {
	if (isatty (fileno (pfp)))
	  fatal ("STR");
	setmode (fileno (pfp), O_BINARY);
      }
#endif
    if (fstat (fileno (pfp), &st) != 0)
      pfatal ("STR");
    if (S_ISREG (st.st_mode) && (pos = file_tell (pfp)) != -1)
      file_pos = pos;
    else
      {
	size_t charsread;
	int fd = make_tempfile (&TMPPATNAME, 'p', NULL, O_RDWR | O_BINARY, 0);
	FILE *read_pfp = pfp;
	TMPPATNAME_needs_removal = true;
	pfp = fdopen (fd, "STR");
	if (! pfp)
	  pfatal ("STR", quotearg (TMPPATNAME));
	for (st.st_size = 0;
	     (charsread = fread (buf, 1, bufsize, read_pfp)) != 0;
	     st.st_size += charsread)
	  if (fwrite (buf, 1, charsread, pfp) != charsread)
	    write_fatal ();
	if (ferror (read_pfp) || fclose (read_pfp) != 0)
	  read_fatal ();
	if (fflush (pfp) != 0
	    || file_seek (pfp, (file_offset) 0, SEEK_SET) != 0)
	  write_fatal ();
      }
    p_filesize = st.st_size;
    if (p_filesize != (file_offset) p_filesize)
      fatal ("STR");
    next_intuit_at (file_pos, 1);
    set_hunkmax();
}