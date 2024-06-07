void
unlink_fifo_list ()
{
  int saved, i, j;

  if (nfifo == 0)
    return;

  for (i = saved = 0; i < nfifo; i++)
    {
      if ((fifo_list[i].proc == -1) || (kill(fifo_list[i].proc, 0) == -1))
	{
	  unlink (fifo_list[i].file);
	  free (fifo_list[i].file);
	  fifo_list[i].file = (char *)NULL;
	  fifo_list[i].proc = -1;
	}
      else
	saved++;
    }

  
  if (saved)
    {
      for (i = j = 0; i < nfifo; i++)
	if (fifo_list[i].file)
	  {
	    fifo_list[j].file = fifo_list[i].file;
	    fifo_list[j].proc = fifo_list[i].proc;
	    j++;
	  }
      nfifo = j;
    }
  else
    nfifo = 0;