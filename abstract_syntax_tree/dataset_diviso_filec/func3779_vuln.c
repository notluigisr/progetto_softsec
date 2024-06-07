psf_fwrite (const void *ptr, sf_count_t bytes, sf_count_t items, SF_PRIVATE *psf)
{	sf_count_t total = 0 ;
	ssize_t	count ;
	DWORD dwNumberOfBytesWritten ;

	if (psf->virtual_io)
		return psf->vio.write (ptr, bytes * items, psf->vio_user_data) / bytes ;

	items *= bytes ;

	
	if (items <= 0)
		return 0 ;

	while (items > 0)
	{	
		count = (items > SENSIBLE_SIZE) ? SENSIBLE_SIZE : (ssize_t) items ;

		if (WriteFile (psf->file.handle, ((const char*) ptr) + total, count, &dwNumberOfBytesWritten, 0) == 0)
		{	psf_log_syserr (psf, GetLastError ()) ;
			break ;
			}
		else
			count = dwNumberOfBytesWritten ;

		if (count == 0)
			break ;

		total += count ;
		items -= count ;
		} ;

	if (psf->is_pipe)
		psf->pipeoffset += total ;

	return total / bytes ;
} 