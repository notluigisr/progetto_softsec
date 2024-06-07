MOBI_RET mobi_strip_mobitags(MOBIPart *part) {
    if (part == NULL || part->data == NULL) {
        return MOBI_INIT_FAILED;
    }
    if (part->type != T_HTML) {
        return MOBI_SUCCESS;
    }
    MOBIResult result;
    unsigned char *data_in = part->data;
    result.start = part->data;
    const unsigned char *data_end = part->data + part->size - 1;
    MOBIFragment *first = NULL;
    MOBIFragment *curr = NULL;
    size_t part_size = 0;
    while (true) {
        mobi_find_attrname(&result, result.start, data_end, "STR");
        if (result.start == NULL) {
            break;
        }
        unsigned char *data_cur = result.start;
        result.start = result.end;
        if (data_cur < data_in) {
            mobi_list_del_all(first);
            return MOBI_DATA_CORRUPT;
        }
        size_t size = (size_t) (data_cur - data_in);
        
        curr = mobi_list_add(curr, (size_t) (data_in - part->data ), data_in, size, false);
        if (curr == NULL) {
            mobi_list_del_all(first);
            debug_print("STR");
            return MOBI_MALLOC_FAILED;
        }
        if (!first) { first = curr; }
        part_size += curr->size;
        data_in = result.end;
    }
    if (first) {
        
        if (part->data + part->size < data_in) {
            mobi_list_del_all(first);
            return MOBI_DATA_CORRUPT;
        }
        size_t size = (size_t) (part->data + part->size - data_in);
        curr = mobi_list_add(curr, (size_t) (data_in - part->data ), data_in, size, false);
        if (curr == NULL) {
            mobi_list_del_all(first);
            debug_print("STR");
            return MOBI_MALLOC_FAILED;
        }
        part_size += curr->size;
        
        unsigned char *new_data = malloc(part_size);
        if (new_data == NULL) {
            mobi_list_del_all(first);
            debug_print("STR");
            return MOBI_MALLOC_FAILED;
        }
        unsigned char *data_out = new_data;
        while (first) {
            memcpy(data_out, first->fragment, first->size);
            data_out += first->size;
            first = mobi_list_del(first);
        }
        free(part->data);
        part->data = new_data;
        part->size = part_size;
    }
    return MOBI_SUCCESS;
}