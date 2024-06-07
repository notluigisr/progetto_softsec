ews_get_time_zone_definition (ESoapParameter *node)
{
	ESoapParameter *param;
	gchar *name = NULL;
	gchar *id = NULL;
	GSList *periods = NULL;
	GSList *transitions_groups = NULL;
	EEwsCalendarTransitions *transitions = NULL;
	EEwsCalendarTimeZoneDefinition *tzd = NULL;
	gboolean success = FALSE;

	name = e_soap_parameter_get_property (node, "STR");
	if (name == NULL)
		goto exit;

	id = e_soap_parameter_get_property (node, "STR");
	if (id == NULL)
		goto exit;

	param = e_soap_parameter_get_first_child_by_name (node, "STR");
	if (param != NULL)
		periods = ews_get_periods_list (param);
	if (periods == NULL)
		goto exit;

	param = e_soap_parameter_get_first_child_by_name (node, "STR");
	if (param != NULL)
		transitions_groups = ews_get_transitions_groups_list (param);
	if (transitions_groups == NULL)
		goto exit;

	param = e_soap_parameter_get_first_child_by_name (node, "STR");
	if (param != NULL)
		transitions = ews_get_transitions (param);
	if (transitions == NULL)
		goto exit;

	success = TRUE;

exit:
	if (success) {
		tzd = e_ews_calendar_time_zone_definition_new ();
		tzd->name = name;
		tzd->id = id;
		tzd->periods = periods;
		tzd->transitions_groups = transitions_groups;
		tzd->transitions = transitions;
	} else {
		g_free (name);
		g_free (id);
		g_slist_free_full (periods, (GDestroyNotify) e_ews_calendar_period_free);
		g_slist_free_full (transitions_groups, (GDestroyNotify) e_ews_calendar_transitions_group_free);
		e_ews_calendar_transitions_free (transitions);
	}

	return tzd;
}