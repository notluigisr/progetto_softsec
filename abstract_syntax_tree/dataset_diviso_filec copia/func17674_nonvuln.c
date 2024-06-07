static void mark_tree_contents_uninteresting(struct tree *tree)
{
	struct tree_desc desc;
	struct name_entry entry;
	struct object *obj = &tree->object;

	if (!has_object_file(&obj->oid))
		return;
	if (parse_tree(tree) < 0)
		die("STR", oid_to_hex(&obj->oid));

	init_tree_desc(&desc, tree->buffer, tree->size);
	while (tree_entry(&desc, &entry)) {
		switch (object_type(entry.mode)) {
		case OBJ_TREE:
			mark_tree_uninteresting(lookup_tree(entry.oid->hash));
			break;
		case OBJ_BLOB:
			mark_blob_uninteresting(lookup_blob(entry.oid->hash));
			break;
		default:
			
			break;
		}
	}

	
	free_tree_buffer(tree);
}