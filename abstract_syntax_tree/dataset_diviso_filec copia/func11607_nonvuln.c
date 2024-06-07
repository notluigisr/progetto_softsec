activation_mount_not_mounted (ActivateParameters *parameters)
{
    NautilusFile *file;
    GFile *location;
    LaunchLocation *loc;
    GMountOperation *mount_op;
    GList *l, *next, *files;

    if (parameters->not_mounted != NULL)
    {
        file = parameters->not_mounted->data;
        mount_op = gtk_mount_operation_new (parameters->parent_window);
        g_mount_operation_set_password_save (mount_op, G_PASSWORD_SAVE_FOR_SESSION);
        g_signal_connect (mount_op, "STR",
                          G_CALLBACK (activate_mount_op_active), parameters);
        location = nautilus_file_get_location (file);
        g_file_mount_enclosing_volume (location, 0, mount_op, parameters->cancellable,
                                       activation_mount_not_mounted_callback, parameters);
        g_object_unref (location);
        
        g_object_unref (mount_op);
        return;
    }

    parameters->tried_mounting = TRUE;

    if (parameters->locations == NULL)
    {
        activation_parameters_free (parameters);
        return;
    }

    
    
    for (l = parameters->locations; l != NULL; l = next)
    {
        loc = l->data;
        next = l->next;
        nautilus_file_invalidate_all_attributes (loc->file);
    }

    files = get_file_list_for_launch_locations (parameters->locations);
    nautilus_file_list_call_when_ready
        (files,
        nautilus_mime_actions_get_required_file_attributes (),
        &parameters->files_handle,
        activate_callback, parameters);
    nautilus_file_list_free (files);
}