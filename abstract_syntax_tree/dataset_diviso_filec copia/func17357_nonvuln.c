void CRYPTO_lock(int mode, int type, const char *file, int line)
	{
#ifdef LOCK_DEBUG
		{
		char *rw_text,*operation_text;

		if (mode & CRYPTO_LOCK)
			operation_text="STR";
		else if (mode & CRYPTO_UNLOCK)
			operation_text="STR";
		else
			operation_text="STR";

		if (mode & CRYPTO_READ)
			rw_text="STR";
		else if (mode & CRYPTO_WRITE)
			rw_text="STR";
		else
			rw_text="STR";

		fprintf(stderr,"STR",
			CRYPTO_thread_id(), rw_text, operation_text,
			CRYPTO_get_lock_name(type), file, line);
		}
#endif
	if (type < 0)
		{
		if (do_dynlock_cb)
			do_dynlock_cb(mode, type, file, line);
		}
	else
		if (locking_callback != NULL)
			locking_callback(mode,type,file,line);
	}