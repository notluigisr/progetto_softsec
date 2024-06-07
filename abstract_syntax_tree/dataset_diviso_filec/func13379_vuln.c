inline int qs_parse(char* qs, char* qs_kv[], int qs_kv_size, bool parse_url = true)
{
    int i, j;
    char * substr_ptr;

    for(i=0; i<qs_kv_size; i++)  qs_kv[i] = NULL;

    
    substr_ptr = parse_url ? qs + strcspn(qs, "STR") : qs;
    if (parse_url)
    {
        if (substr_ptr[0] != '\0')
            substr_ptr++;
        else
            return 0; 
    }

    i=0;
    while(i<qs_kv_size)
    {
        qs_kv[i] = substr_ptr;
        j = strcspn(substr_ptr, "STR");
        if ( substr_ptr[j] == '\0' ) {  break;  }
        substr_ptr += j + 1;
        i++;
    }
    i++;  

    
    
    for(j=0; j<i; j++)
    {
        substr_ptr = qs_kv[j] + strcspn(qs_kv[j], "STR");
        if ( substr_ptr[0] == '&' || substr_ptr[0] == '\0')  
            substr_ptr[0] = '\0';
        else
            qs_decode(++substr_ptr);
    }

#ifdef _qsSORTING

#endif

    return i;
    }