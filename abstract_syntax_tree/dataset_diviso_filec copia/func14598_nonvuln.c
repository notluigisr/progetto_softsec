get_activation_action (NautilusFile *file)
{
	ActivationAction action;
	char *activation_uri;

	if (nautilus_file_is_launcher (file)) {
		return ACTIVATION_ACTION_LAUNCH_DESKTOP_FILE;
	}
	
	activation_uri = nautilus_file_get_activation_uri (file);
	if (activation_uri == NULL) {
		activation_uri = nautilus_file_get_uri (file);
	}

	action = ACTIVATION_ACTION_DO_NOTHING;
	if (nautilus_file_is_launchable (file)) {
		char *executable_path;
		
		action = ACTIVATION_ACTION_LAUNCH;
		
		executable_path = g_filename_from_uri (activation_uri, NULL, NULL);
		if (!executable_path) {
			action = ACTIVATION_ACTION_DO_NOTHING;
		} else if (nautilus_file_contains_text (file)) {
			action = get_default_executable_text_file_action ();
		}
		g_free (executable_path);
	} 

	if (action == ACTIVATION_ACTION_DO_NOTHING) {
		if (nautilus_mime_file_opens_in_view (file)) {
			action = ACTIVATION_ACTION_OPEN_IN_VIEW;
		} else {
			action = ACTIVATION_ACTION_OPEN_IN_APPLICATION;
		}
	}
	g_free (activation_uri);

	return action;
}