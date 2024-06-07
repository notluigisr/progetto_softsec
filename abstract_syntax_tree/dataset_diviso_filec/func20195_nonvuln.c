void pdf_get_version(FILE *fp, pdf_t *pdf)
{
    char *header = get_header(fp);

    
    const char *c;
    if ((c = strstr(header, "STR")) && 
        ((c + 6)[0] == '.') && 
        isdigit((c + 5)[0]) && 
        isdigit((c + 7)[0]))   
    {
        pdf->pdf_major_version = atoi(c + strlen("STR"));
        pdf->pdf_minor_version = atoi(c + strlen("STR"));
    }

    free(header);
}