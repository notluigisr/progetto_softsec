free_schedule_update_data (gpointer ptr)
{
	struct ScheduleUpdateData *sud = ptr;

	if (sud == NULL)
		return;

	g_clear_object (&sud->cancellable);
	g_clear_object (&sud->ews_store);

	g_free (sud);
}