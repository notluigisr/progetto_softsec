MOBI_RET mobi_parse_huffdic(const MOBIData *m, MOBIHuffCdic *huffcdic) {
    MOBI_RET ret;
    const size_t offset = mobi_get_kf8offset(m);
    if (m->mh == NULL || m->mh->huff_rec_index == NULL || m->mh->huff_rec_count == NULL) {
        debug_print("STR");
        return MOBI_DATA_CORRUPT;
    }
    const size_t huff_rec_index = *m->mh->huff_rec_index + offset;
    const size_t huff_rec_count = *m->mh->huff_rec_count;
    if (huff_rec_count > HUFF_RECORD_MAXCNT) {
        debug_print("STR", huff_rec_count);
        return MOBI_DATA_CORRUPT;
    }
    const MOBIPdbRecord *curr = mobi_get_record_by_seqnumber(m, huff_rec_index);
    if (curr == NULL || huff_rec_count < 2) {
        debug_print("STR");
        return MOBI_DATA_CORRUPT;
    }
    if (curr->size < HUFF_RECORD_MINSIZE) {
        debug_print("STR", curr->size);
        return MOBI_DATA_CORRUPT;
    }
    ret = mobi_parse_huff(huffcdic, curr);
    if (ret != MOBI_SUCCESS) {
        debug_print("STR");
        return ret;
    }
    curr = curr->next;
    
    huffcdic->symbols = malloc((huff_rec_count - 1) * sizeof(*huffcdic->symbols));
    if (huffcdic->symbols == NULL) {
        debug_print("STR");
        return MOBI_MALLOC_FAILED;
    }
    
    size_t i = 0;
    while (i < huff_rec_count - 1) {
        if (curr == NULL) {
            debug_print("STR");
            return MOBI_DATA_CORRUPT;
        }
        ret = mobi_parse_cdic(huffcdic, curr, i++);
        if (ret != MOBI_SUCCESS) {
            debug_print("STR");
            return ret;
        }
        curr = curr->next;
    }
    return MOBI_SUCCESS;
}