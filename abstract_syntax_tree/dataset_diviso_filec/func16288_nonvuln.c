static void calipso_doi_free(struct calipso_doi *doi_def)
{
	kfree(doi_def);
}