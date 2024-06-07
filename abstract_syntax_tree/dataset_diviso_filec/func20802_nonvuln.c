nautilus_file_cancel (NautilusFile *file,
		      NautilusFileOperationCallback callback,
		      gpointer callback_data)
{
	GList *node, *next;
	NautilusFileOperation *op;

	for (node = file->details->operations_in_progress; node != NULL; node = next) {
		next = node->next;
		op = node->data;

		g_assert (op->file == file);
		if (op->callback == callback && op->callback_data == callback_data) {
			nautilus_file_operation_cancel (op);
		}
	}
}