static void __init of_unittest_dynamic(void)
{
	struct device_node *np;
	struct property *prop;

	np = of_find_node_by_path("STR");
	if (!np) {
		pr_err("STR");
		return;
	}

	
	prop = kcalloc(4, sizeof(*prop), GFP_KERNEL);
	if (!prop) {
		unittest(0, "STR");
		return;
	}

	
	prop->name = "STR";
	prop->value = "STR";
	prop->length = strlen(prop->value) + 1;
	unittest(of_add_property(np, prop) == 0, "STR");

	
	prop++;
	prop->name = "STR";
	prop->value = "STR";
	prop->length = strlen(prop->value) + 1;
	unittest(of_add_property(np, prop) != 0,
		 "STR");

	
	prop->value = "STR";
	prop->length = strlen(prop->value) + 1;
	unittest(of_update_property(np, prop) == 0,
		 "STR");

	
	prop++;
	prop->name = "STR";
	prop->value = "STR";
	prop->length = strlen(prop->value) + 1;
	unittest(of_update_property(np, prop) == 0,
		 "STR");

	
	unittest(of_remove_property(np, prop) == 0,
		 "STR");

	
	prop++;
	prop->name = "STR";
	prop->length = PAGE_SIZE * 8;
	prop->value = kzalloc(prop->length, GFP_KERNEL);
	unittest(prop->value != NULL, "STR");
	if (prop->value)
		unittest(of_add_property(np, prop) == 0,
			 "STR");
}