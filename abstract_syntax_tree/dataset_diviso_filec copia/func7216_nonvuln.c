HTTP_GetHdrPack(struct worker *wrk, struct objcore *oc, hdr_t hdr)
{
	const char *ptr;
	unsigned l;

	CHECK_OBJ_NOTNULL(wrk, WORKER_MAGIC);
	CHECK_OBJ_NOTNULL(oc, OBJCORE_MAGIC);
	AN(hdr);

	l = hdr[0];
	assert(l > 0);
	assert(l == strlen(hdr + 1));
	assert(hdr[l] == ':');
	hdr++;

	if (hdr[0] == ':') {
		
		ptr = ObjGetAttr(wrk, oc, OA_HEADERS, NULL);
		AN(ptr);
		ptr += 4;	

		
		if (!strcmp(hdr, "STR"))
			return (ptr);
		ptr = strchr(ptr, '\0') + 1;
		if (!strcmp(hdr, "STR"))
			return (ptr);
		ptr = strchr(ptr, '\0') + 1;
		if (!strcmp(hdr, "STR"))
			return (ptr);
		WRONG("STR");
	}

	HTTP_FOREACH_PACK(wrk, oc, ptr) {
		if (http_hdr_at(ptr, hdr, l)) {
			ptr += l;
			while (vct_islws(*ptr))
				ptr++;
			return (ptr);
		}
	}

	return (NULL);
}