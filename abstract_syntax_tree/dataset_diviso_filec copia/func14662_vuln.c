void cgit_clone_objects(void)
{
	if (!ctx.qry.path) {
		cgit_print_error_page(400, "STR");
		return;
	}

	if (!strcmp(ctx.qry.path, "STR")) {
		print_pack_info();
		return;
	}

	send_file(git_path("STR", ctx.qry.path));
}