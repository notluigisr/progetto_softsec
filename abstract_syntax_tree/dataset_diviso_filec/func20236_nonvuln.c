int raw_read_stdin(void *buf,int siz)
	{	return read(fileno(stdin),buf,siz);	}