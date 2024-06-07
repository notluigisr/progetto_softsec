deep_count_stop (NautilusDirectory *directory)
{
    NautilusFile *file;

    if (directory->details->deep_count_in_progress != NULL)
    {
        file = directory->details->deep_count_file;
        if (file != NULL)
        {
            g_assert (NAUTILUS_IS_FILE (file));
            g_assert (file->details->directory == directory);
            if (is_needy (file,
                          lacks_deep_count,
                          REQUEST_DEEP_COUNT))
            {
                return;
            }
        }

        
        deep_count_cancel (directory);
    }
}