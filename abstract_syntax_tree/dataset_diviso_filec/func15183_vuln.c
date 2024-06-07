grub_username_get (char buf[], unsigned buf_size)
{
  unsigned cur_len = 0;
  int key;

  while (1)
    {
      key = grub_getkey (); 
      if (key == '\n' || key == '\r')
	break;

      if (key == '\e')
	{
	  cur_len = 0;
	  break;
	}

      if (key == '\b')
	{
	  cur_len--;
	  grub_printf ("STR");
	  continue;
	}

      if (!grub_isprint (key))
	continue;

      if (cur_len + 2 < buf_size)
	{
	  buf[cur_len++] = key;
	  grub_printf ("STR", key);
	}
    }

  grub_memset (buf + cur_len, 0, buf_size - cur_len);

  grub_xputs ("STR");
  grub_refresh ();

  return (key != '\e');
}