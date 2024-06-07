static void update_node_properties(struct device_node *np,
					struct device_node *dup)
{
	struct property *prop;
	struct property *save_next;
	struct device_node *child;
	int ret;

	for_each_child_of_node(np, child)
		child->parent = dup;

	

	
	for (prop = np->properties; prop != NULL; prop = save_next) {
		save_next = prop->next;
		ret = of_add_property(dup, prop);
		if (ret) {
			if (ret == -EEXIST && !strcmp(prop->name, "STR"))
				continue;
			pr_err("STR",
			       np, prop->name);
		}
	}
}