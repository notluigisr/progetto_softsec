MOBI_RET mobi_parse_index(const MOBIData *m, MOBIIndx *indx, const size_t indx_record_number) {
    MOBI_RET ret;
    
    MOBITagx *tagx = calloc(1, sizeof(MOBITagx));
    if (tagx == NULL) {
        mobi_free_indx(indx);
        debug_print("STR");
        return MOBI_MALLOC_FAILED;
    }
    
    MOBIOrdt *ordt = calloc(1, sizeof(MOBIOrdt));
    if (ordt == NULL) {
        mobi_free_indx(indx);
        mobi_free_tagx(tagx);
        debug_print("STR");
        return MOBI_MALLOC_FAILED;
    }
    
    MOBIPdbRecord *record = mobi_get_record_by_seqnumber(m, indx_record_number);
    ret = mobi_parse_indx(record, indx, tagx, ordt);
    if (ret != MOBI_SUCCESS) {
        mobi_free_indx(indx);
        mobi_free_tagx(tagx);
        mobi_free_ordt(ordt);
        return ret;
    }
    
    size_t count = indx->entries_count;
    indx->entries_count = 0;
    while (count--) {
        record = record->next;
        ret = mobi_parse_indx(record, indx, tagx, ordt);
        if (ret != MOBI_SUCCESS) {
            mobi_free_indx(indx);
            mobi_free_tagx(tagx);
            mobi_free_ordt(ordt);
            return ret;
        }
    }
    if (indx->entries_count != indx->total_entries_count) {
        debug_print("STR", indx->entries_count, indx->total_entries_count);
        mobi_free_indx(indx);
        mobi_free_tagx(tagx);
        mobi_free_ordt(ordt);
        return MOBI_DATA_CORRUPT;
    }
    
    if (indx->cncx_records_count) {
        indx->cncx_record = record->next;
    }
    mobi_free_tagx(tagx);
    mobi_free_ordt(ordt);
    return MOBI_SUCCESS;
}