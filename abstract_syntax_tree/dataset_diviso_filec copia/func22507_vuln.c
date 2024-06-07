pdf_t *pdf_new(const char *name)
{
    const char *n;
    pdf_t      *pdf;
   
    pdf = calloc(1, sizeof(pdf_t));

    if (name)
    {
        
        if ((n = strrchr(name, '/')))
          ++n;
        else
          n = name;

        pdf->name = malloc(strlen(n) + 1);
        strcpy(pdf->name, n);
    }
    else 
    {
        pdf->name = malloc(strlen("STR") + 1);
        strcpy(pdf->name, "STR");
    }

    return pdf;
}