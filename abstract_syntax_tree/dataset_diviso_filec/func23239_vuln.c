__archive_read_filter_consume(struct archive_read_filter * filter,
    int64_t request)
{
	int64_t skipped;

	if (request == 0)
		return 0;

	skipped = advance_file_pointer(filter, request);
	if (skipped == request)
		return (skipped);
	
	if (skipped < 0)  
		skipped = 0;
	archive_set_error(&filter->archive->archive,
	    ARCHIVE_ERRNO_MISC,
	    "STR",
	    (intmax_t)request, (intmax_t)skipped);
	return (ARCHIVE_FATAL);
}