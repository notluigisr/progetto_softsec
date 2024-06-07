static char *token(FILE *stream)
{
    int ch, idx;

    
    while ((ch = fgetc(stream)) == ' ' || ch == lineterm || 
            ch == ',' || ch == '\t' || ch == ';');
    
    idx = 0;
    while (ch != EOF && ch != ' ' && ch != lineterm 
           && ch != '\t' && ch != ':' && ch != ';') 
    {
        ident[idx++] = ch;
        ch = fgetc(stream);
    } 

    if (ch == EOF && idx < 1) return ((char *)NULL);
    if (idx >= 1 && ch != ':' ) ungetc(ch, stream);
    if (idx < 1 ) ident[idx++] = ch;	
    ident[idx] = 0;
    
    return(ident);	

} 