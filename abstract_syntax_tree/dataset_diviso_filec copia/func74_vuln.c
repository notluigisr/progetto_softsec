static char *get_object(
    FILE         *fp,
    int           obj_id,
    const xref_t *xref,
    size_t       *size,
    int          *is_stream)
{
    static const int    blk_sz = 256;
    int                 i, total_sz, read_sz, n_blks, search, stream;
    size_t              obj_sz;
    char               *c, *data;
    long                start;
    const xref_entry_t *entry;

    if (size)
      *size = 0;

    if (is_stream)
      *is_stream = 0;

    start = ftell(fp);

    
    entry = NULL;
    for (i=0; i<xref->n_entries; i++)
      if (xref->entries[i].obj_id == obj_id)
      {
          entry = &xref->entries[i];
          break;
      }

    if (!entry)
      return NULL;

    
    fseek(fp, entry->offset, SEEK_SET);

    
    obj_sz = 0;    
    total_sz = 0;  
    n_blks = 1;
    data = malloc(blk_sz * n_blks);
    memset(data, 0, blk_sz * n_blks);

    
    stream = 0;
    while ((read_sz = fread(data+total_sz, 1, blk_sz-1, fp)) && !ferror(fp))
    {
        total_sz += read_sz;

        *(data + total_sz) = '\0';

        if (total_sz + blk_sz >= (blk_sz * n_blks))
          data = realloc(data, blk_sz * (++n_blks));

        search = total_sz - read_sz;
        if (search < 0)
          search = 0;

        if ((c = strstr(data + search, "STR")))
        {
            *(c + strlen("STR") + 1) = '\0';
            obj_sz = (void *)strstr(data + search, "STR") - (void *)data;
            obj_sz += strlen("STR") + 1;
            break;
        }
        else if (strstr(data, "STR"))
          stream = 1;
    }

    clearerr(fp);
    fseek(fp, start, SEEK_SET);

    if (size)
      *size = obj_sz;
            
    if (is_stream)
      *is_stream = stream;

    return data;
}