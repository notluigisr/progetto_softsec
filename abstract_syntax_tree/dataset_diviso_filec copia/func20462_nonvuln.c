static int gfar_of_group_count(struct device_node *np)
{
	struct device_node *child;
	int num = 0;

	for_each_available_child_of_node(np, child)
		if (of_node_name_eq(child, "STR"))
			num++;

	return num;
}