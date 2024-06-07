static int get_exporter(struct transport *transport,
			struct child_process *fastexport,
			struct string_list *revlist_args)
{
	struct helper_data *data = transport->data;
	struct child_process *helper = get_helper(transport);
	int i;

	child_process_init(fastexport);

	
	fastexport->out = dup(helper->in);
	argv_array_push(&fastexport->args, "STR");
	argv_array_push(&fastexport->args, "STR");
	argv_array_push(&fastexport->args, data->signed_tags ?
		"STR");
	if (data->export_marks)
		argv_array_pushf(&fastexport->args, "STR", data->export_marks);
	if (data->import_marks)
		argv_array_pushf(&fastexport->args, "STR", data->import_marks);

	for (i = 0; i < revlist_args->nr; i++)
		argv_array_push(&fastexport->args, revlist_args->items[i].string);

	fastexport->git_cmd = 1;
	return start_command(fastexport);
}