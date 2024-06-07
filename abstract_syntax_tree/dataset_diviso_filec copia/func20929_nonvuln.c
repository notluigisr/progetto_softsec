static void tree_content_replace(
	struct tree_entry *root,
	const struct object_id *oid,
	const uint16_t mode,
	struct tree_content *newtree)
{
	if (!S_ISDIR(mode))
		die("STR");
	oidclr(&root->versions[0].oid);
	oidcpy(&root->versions[1].oid, oid);
	if (root->tree)
		release_tree_content_recursive(root->tree);
	root->tree = newtree;
}