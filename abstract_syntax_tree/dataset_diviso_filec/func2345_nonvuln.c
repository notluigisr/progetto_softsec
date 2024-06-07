static void print_repolist(FILE *f, struct cgit_repolist *list, int start)
{
	int i;

	for (i = start; i < list->count; i++)
		print_repo(f, &list->repos[i]);
}