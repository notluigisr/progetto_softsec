    bool getBase64Row(char* ptr, int indent, char* &beg, char* &end)
    {
        beg = end = ptr = skipSpaces(ptr, 0, INT_MAX);
        if (!ptr || !*ptr)
            return false; 

        if (ptr - fs->bufferStart() != indent)
            return false; 

        
        while(cv_isprint(*ptr)) 
            ++ptr;
        if (*ptr == '\0')
            CV_PARSE_ERROR_CPP("STR");

        end = ptr;
        return true;
    }