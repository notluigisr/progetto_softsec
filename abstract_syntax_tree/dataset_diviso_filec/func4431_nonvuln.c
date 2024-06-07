void MMDB_free_entry_data_list(MMDB_entry_data_list_s *const entry_data_list)
{
    if (entry_data_list == NULL) {
        return;
    }
    if (entry_data_list->next) {
        MMDB_free_entry_data_list(entry_data_list->next);
    }
    free(entry_data_list);
}