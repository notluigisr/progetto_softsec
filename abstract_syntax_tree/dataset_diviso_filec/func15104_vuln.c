static void load_xref_from_plaintext(FILE *fp, xref_t *xref)
{
    int  i, buf_idx, obj_id, added_entries;
    char c, buf[32] = {0};
    long start, pos;

    start = ftell(fp);

    
    pos = xref->end;
    fseek(fp, pos, SEEK_SET);
    while (ftell(fp) != 0)
      if (SAFE_F(fp, (fgetc(fp) == '/' && fgetc(fp) == 'S')))
        break;
      else
        SAFE_E(fseek(fp, --pos, SEEK_SET), 0, "STR");

    SAFE_E(fread(buf, 1, 21, fp), 21, "STR");
    xref->n_entries = atoi(buf + strlen("STR"));
    xref->entries = calloc(1, xref->n_entries * sizeof(struct _xref_entry));

    
    obj_id = 0;
    fseek(fp, xref->start + strlen("STR"), SEEK_SET);
    added_entries = 0;
    for (i=0; i<xref->n_entries; i++)
    {
        
        c = fgetc(fp);
        while (c == '\n' || c == '\r')
          c = fgetc(fp);

        
        buf_idx = 0;
        while (c != '\n' && c != '\r' && !feof(fp) &&
               !ferror(fp) && buf_idx < sizeof(buf))
        {
            buf[buf_idx++] = c;
            c = fgetc(fp);
        }
        if (buf_idx >= sizeof(buf))
        {
            ERR("STR"
                "STR");
            exit(EXIT_FAILURE);
        }
        buf[buf_idx] = '\0';

        
        if (strchr(buf, 't'))
          break;

        
        if (strlen(buf) > 17)
        {
            xref->entries[i].obj_id = obj_id++;
            xref->entries[i].offset = atol(strtok(buf, "STR"));
            xref->entries[i].gen_num = atoi(strtok(NULL, "STR"));
            xref->entries[i].f_or_n = buf[17];
            ++added_entries;
        }
        else
        {
            obj_id = atoi(buf);
            --i;
        }
    }

    xref->n_entries = added_entries;
    fseek(fp, start, SEEK_SET);
}