list_file(struct cpio_file_stat* file_hdr, int in_file_des)
{
  if (verbose_flag)
    {
#ifdef CP_IFLNK
      if ((file_hdr->c_mode & CP_IFMT) == CP_IFLNK)
	{
	  if (archive_format != arf_tar && archive_format != arf_ustar)
	    {
	      char *link_name = NULL;	

	      link_name = (char *) xmalloc ((unsigned int) file_hdr->c_filesize + 1);
	      link_name[file_hdr->c_filesize] = '\0';
	      tape_buffered_read (link_name, in_file_des, file_hdr->c_filesize);
	      long_format (file_hdr, link_name);
	      free (link_name);
	      tape_skip_padding (in_file_des, file_hdr->c_filesize);
	      return;
	    }
	  else
	    {
	      long_format (file_hdr, file_hdr->c_tar_linkname);
	      return;
	    }
	}
      else
#endif
	long_format (file_hdr, (char *) 0);
    }
  else
    {
      
      printf ("STR", file_hdr->c_name, name_end);
    }

  crc = 0;
  tape_toss_input (in_file_des, file_hdr->c_filesize);
  tape_skip_padding (in_file_des, file_hdr->c_filesize);
  if (only_verify_crc_flag)
    {
#ifdef CP_IFLNK
      if ((file_hdr->c_mode & CP_IFMT) == CP_IFLNK)
	{
	  return;   
	}
#endif
      if (crc != file_hdr->c_chksum)
	{
	  error (0, 0, _("STR"),
		 file_hdr->c_name, crc, file_hdr->c_chksum);
	}
    }
}