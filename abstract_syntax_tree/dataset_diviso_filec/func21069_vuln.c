void pdf_get_version(FILE *fp, pdf_t *pdf)
{
    char *header, *c;

    header = get_header(fp);

    
    if ((c = strstr(header, "STR")) && 
        (c + strlen("STR") + 2))
    {
        pdf->pdf_major_version = atoi(c + strlen("STR"));
        pdf->pdf_minor_version = atoi(c + strlen("STR"));
    }

    free(header);
}