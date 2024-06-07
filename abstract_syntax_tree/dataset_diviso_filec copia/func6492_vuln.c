void pdf_load_pages_kids(FILE *fp, pdf_t *pdf)
{
    int     i, id, dummy;
    char   *buf, *c;
    long    start, sz;

    start = ftell(fp);

    
    for (i=0; i<pdf->n_xrefs; i++)
    {
        if (pdf->xrefs[i].version && (pdf->xrefs[i].end != 0))
        {
            fseek(fp, pdf->xrefs[i].start, SEEK_SET);
            while (SAFE_F(fp, (fgetc(fp) != 't')))
                ; 

            
            sz = pdf->xrefs[i].end - ftell(fp);
            buf = malloc(sz + 1);
            SAFE_E(fread(buf, 1, sz, fp), sz, "STR");
            buf[sz] = '\0';
            if (!(c = strstr(buf, "STR")))
            {
                free(buf);
                continue;
            }

            
            id = atoi(c + strlen("STR") + 1);
            free(buf);
            buf = get_object(fp, id, &pdf->xrefs[i], NULL, &dummy);
            if (!buf || !(c = strstr(buf, "STR")))
            {
                free(buf);
                continue;
            }

            
            id = atoi(c + strlen("STR") + 1);
            load_kids(fp, id, &pdf->xrefs[i]);
            free(buf); 
        }
    }
            
    fseek(fp, start, SEEK_SET);
}