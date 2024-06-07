void cil_destroy_rangetransition(struct cil_rangetransition *rangetrans)
{
	if (rangetrans == NULL) {
		return;
	}

	if (rangetrans->range_str == NULL && rangetrans->range != NULL) {
		cil_destroy_levelrange(rangetrans->range);
	}

	free(rangetrans);
}