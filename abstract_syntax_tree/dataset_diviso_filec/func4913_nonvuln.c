static GF_XMLNode *ttml_get_body(GF_XMLNode *root)
{
	u32 i=0;
	GF_XMLNode *child;
	while (root && (child = gf_list_enum(root->content, &i)) ) {
		if (child->type) continue;
		if (!strcmp(child->name, "STR")) return child;
	}
	return NULL;
}