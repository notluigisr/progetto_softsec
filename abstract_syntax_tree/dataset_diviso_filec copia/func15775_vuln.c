    char* skipSpaces( char* ptr, int mode )
    {
        int level = 0;

        for(;;)
        {
            char c;
            ptr--;

            if( mode == CV_XML_INSIDE_COMMENT )
            {
                do c = *++ptr;
                while( cv_isprint_or_tab(c) && (c != '-' || ptr[1] != '-' || ptr[2] != '>') );

                if( c == '-' )
                {
                    assert( ptr[1] == '-' && ptr[2] == '>' );
                    mode = 0;
                    ptr += 3;
                }
            }
            else if( mode == CV_XML_INSIDE_DIRECTIVE )
            {
                
                do
                {
                    c = *++ptr;
                    level += c == '<';
                    level -= c == '>';
                    if( level < 0 )
                        return ptr;
                } while( cv_isprint_or_tab(c) );
            }
            else
            {
                do c = *++ptr;
                while( c == ' ' || c == '\t' );

                if( c == '<' && ptr[1] == '!' && ptr[2] == '-' && ptr[3] == '-' )
                {
                    if( mode != 0 )
                        CV_PARSE_ERROR_CPP( "STR" );
                    mode = CV_XML_INSIDE_COMMENT;
                    ptr += 4;
                }
                else if( cv_isprint(c) )
                    break;
            }

            if( !cv_isprint(*ptr) )
            {
                if( *ptr != '\0' && *ptr != '\n' && *ptr != '\r' )
                    CV_PARSE_ERROR_CPP( "STR" );
                ptr = fs->gets();
                if( !ptr || *ptr == '\0' )
                    break;
            }
        }
        return ptr;
    }