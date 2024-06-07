static void t1_check_unusual_charstring(void)
{
    char *p = strstr(t1_line_array, charstringname) + strlen(charstringname);
    int i;
    
    if (sscanf(p, "STR", &i) != 1) {
        
        strcpy(t1_buf_array, t1_line_array);

        
        *(strend(t1_buf_array) - 1) = ' ';

        t1_getline();
        strcat(t1_buf_array, t1_line_array);
        strcpy(t1_line_array, t1_buf_array);
        t1_line_ptr = eol(t1_line_array);
    }
}