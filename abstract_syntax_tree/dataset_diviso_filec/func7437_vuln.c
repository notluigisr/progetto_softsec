static char *linetoken(FILE *stream)
{
    int ch, idx;

    while ((ch = fgetc(stream)) == ' ' || ch == '\t' ); 
    
    idx = 0;
    while (ch != EOF && ch != lineterm) 
    {
        ident[idx++] = ch;
        ch = fgetc(stream);
    } 
    
    ungetc(ch, stream);
    ident[idx] = 0;

    return(ident);	

} 