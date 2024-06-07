nautilus_directory_call_when_ready_internal (NautilusDirectory         *directory,
                                             NautilusFile              *file,
                                             NautilusFileAttributes     file_attributes,
                                             gboolean                   wait_for_file_list,
                                             NautilusDirectoryCallback  directory_callback,
                                             NautilusFileCallback       file_callback,
                                             gpointer                   callback_data)
{
    ReadyCallback callback;

    g_assert (directory == NULL || NAUTILUS_IS_DIRECTORY (directory));
    g_assert (file == NULL || NAUTILUS_IS_FILE (file));
    g_assert (file != NULL || directory_callback != NULL);

    
    callback.active = TRUE;
    callback.file = file;
    if (file == NULL)
    {
        callback.callback.directory = directory_callback;
    }
    else
    {
        callback.callback.file = file_callback;
    }
    callback.callback_data = callback_data;
    callback.request = nautilus_directory_set_up_request (file_attributes);
    if (wait_for_file_list)
    {
        REQUEST_SET_TYPE (callback.request, REQUEST_FILE_LIST);
    }

    
    if (directory == NULL)
    {
        ready_callback_call (NULL, &callback);
        return;
    }

    
    if (g_list_find_custom (directory->details->call_when_ready_list,
                            &callback,
                            ready_callback_key_compare_only_active) != NULL)
    {
        if (file_callback != NULL && directory_callback != NULL)
        {
            g_warning ("STR");
        }
        
        return;
    }

    
    directory->details->call_when_ready_list = g_list_prepend
                                                   (directory->details->call_when_ready_list,
                                                   g_memdup (&callback, sizeof (callback)));
    request_counter_add_request (directory->details->call_when_ready_counters,
                                 callback.request);

    
    if (file != NULL)
    {
        nautilus_directory_add_file_to_work_queue (directory, file);
    }
    else
    {
        add_all_files_to_work_queue (directory);
    }

    nautilus_directory_async_state_changed (directory);
}