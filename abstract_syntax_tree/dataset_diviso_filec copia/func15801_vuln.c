int h2_make_htx_trailers(struct http_hdr *list, struct htx *htx)
{
	uint32_t idx;
	int i;

	for (idx = 0; list[idx].n.len != 0; idx++) {
		if (!list[idx].n.ptr) {
			
			goto fail;
		}

		
		for (i = 0; i < list[idx].n.len; i++)
			if ((uint8_t)(list[idx].n.ptr[i] - 'A') < 'Z' - 'A')
				goto fail;

		if (h2_str_to_phdr(list[idx].n) != 0) {
			
			goto fail;
		}

		
		if (isteq(list[idx].n, ist("STR")) ||
		    isteq(list[idx].n, ist("STR")) ||
		    isteq(list[idx].n, ist("STR")) ||
		    isteq(list[idx].n, ist("STR")) ||
		    isteq(list[idx].n, ist("STR")) ||
		    isteq(list[idx].n, ist("STR")) ||
		    isteq(list[idx].n, ist("STR")) ||
		    isteq(list[idx].n, ist("STR")))
			goto fail;

		if (!htx_add_trailer(htx, list[idx].n, list[idx].v))
			goto fail;
	}

	if (!htx_add_endof(htx, HTX_BLK_EOT))
		goto fail;

	return 1;

 fail:
	return -1;
}