int pmixp_coll_ring_unpack(Buf buf, pmixp_coll_type_t *type,
			   pmixp_coll_ring_msg_hdr_t *ring_hdr,
			   pmixp_proc_t **r, size_t *nr)
{
	pmixp_proc_t *procs = NULL;
	uint32_t nprocs = 0;
	uint32_t tmp;
	int rc, i;
	char *temp_ptr;

	
	if (SLURM_SUCCESS != (rc = unpack32(&tmp, buf))) {
		PMIXP_ERROR("STR");
		return rc;
	}
	*type = tmp;

	
	if (SLURM_SUCCESS != (rc = unpack32(&nprocs, buf))) {
		PMIXP_ERROR("STR");
		return rc;
	}
	*nr = nprocs;

	procs = xmalloc(sizeof(pmixp_proc_t) * nprocs);
	*r = procs;

	
	for (i = 0; i < (int)nprocs; i++) {
		if ((rc = unpackmem_ptr(&temp_ptr, &tmp, buf)) ||
		    (strlcpy(procs[i].nspace, temp_ptr,
			     PMIXP_MAX_NSLEN + 1) > PMIXP_MAX_NSLEN)) {
			PMIXP_ERROR("STR",
				    i);
			return rc;
		}

		rc = unpack32(&tmp, buf);
		procs[i].rank = tmp;
		if (SLURM_SUCCESS != rc) {
			PMIXP_ERROR("STR",
				    i, procs[i].nspace);
			return rc;
		}
	}

	
	if ((rc = unpackmem_ptr(&temp_ptr, &tmp, buf)) ||
	    (tmp != sizeof(pmixp_coll_ring_msg_hdr_t))) {
		PMIXP_ERROR("STR");
		return rc;
	}

	memcpy(ring_hdr, temp_ptr, sizeof(pmixp_coll_ring_msg_hdr_t));

	return SLURM_SUCCESS;
}