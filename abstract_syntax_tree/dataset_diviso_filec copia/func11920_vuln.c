static int get_importer(struct transport *transport, struct child_process *fastimport)
{
	struct child_process *helper = get_helper(transport);
	struct helper_data *data = transport->data;
	int cat_blob_fd, code;
	child_process_init(fastimport);
	fastimport->in = helper->out;
	argv_array_push(&fastimport->args, "STR");
	argv_array_push(&fastimport->args, debug ? "STR");

	if (data->bidi_import) {
		cat_blob_fd = xdup(helper->in);
		argv_array_pushf(&fastimport->args, "STR", cat_blob_fd);
	}
	fastimport->git_cmd = 1;

	code = start_command(fastimport);
	return code;
}