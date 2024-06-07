LOCAL int populate_description_metadata(MMDB_s *mmdb, MMDB_s *metadata_db,
                                        MMDB_entry_s *metadata_start)
{
    MMDB_entry_data_s entry_data;

    const char *path[] = { "STR", NULL };
    int status = MMDB_aget_value(metadata_start, &entry_data, path);
    if (MMDB_SUCCESS != status) {
        return status;
    }

    if (MMDB_DATA_TYPE_MAP != entry_data.type) {
        return MMDB_INVALID_METADATA_ERROR;
    }

    MMDB_entry_s map_start = {
        .mmdb   = metadata_db,
        .offset = entry_data.offset
    };

    MMDB_entry_data_list_s *member;
    status = MMDB_get_entry_data_list(&map_start, &member);
    if (MMDB_SUCCESS != status) {
        return status;
    }

    MMDB_entry_data_list_s *first_member = member;

    uint32_t map_size = member->entry_data.data_size;
    mmdb->metadata.description.count = 0;
    if (0 == map_size) {
        mmdb->metadata.description.descriptions = NULL;
        goto cleanup;
    }

    mmdb->metadata.description.descriptions =
        malloc(map_size * sizeof(MMDB_description_s *));
    if (NULL == mmdb->metadata.description.descriptions) {
        status = MMDB_OUT_OF_MEMORY_ERROR;
        goto cleanup;
    }

    for (uint32_t i = 0; i < map_size; i++) {
        mmdb->metadata.description.descriptions[i] =
            malloc(sizeof(MMDB_description_s));
        if (NULL == mmdb->metadata.description.descriptions[i]) {
            status = MMDB_OUT_OF_MEMORY_ERROR;
            goto cleanup;
        }

        mmdb->metadata.description.count = i + 1;
        mmdb->metadata.description.descriptions[i]->language = NULL;
        mmdb->metadata.description.descriptions[i]->description = NULL;

        member = member->next;

        if (MMDB_DATA_TYPE_UTF8_STRING != member->entry_data.type) {
            status = MMDB_INVALID_METADATA_ERROR;
            goto cleanup;
        }

        mmdb->metadata.description.descriptions[i]->language =
            mmdb_strndup((char *)member->entry_data.utf8_string,
                         member->entry_data.data_size);

        if (NULL == mmdb->metadata.description.descriptions[i]->language) {
            status = MMDB_OUT_OF_MEMORY_ERROR;
            goto cleanup;
        }

        member = member->next;

        if (MMDB_DATA_TYPE_UTF8_STRING != member->entry_data.type) {
            status = MMDB_INVALID_METADATA_ERROR;
            goto cleanup;
        }

        mmdb->metadata.description.descriptions[i]->description =
            mmdb_strndup((char *)member->entry_data.utf8_string,
                         member->entry_data.data_size);

        if (NULL == mmdb->metadata.description.descriptions[i]->description) {
            status = MMDB_OUT_OF_MEMORY_ERROR;
            goto cleanup;
        }
    }

 cleanup:
    MMDB_free_entry_data_list(first_member);

    return status;
}