    char* parseKey( char* ptr, FileNode& collection, FileNode& value_placeholder )
    {
        if( *ptr != '"' )
            CV_PARSE_ERROR_CPP( "STR" );

        char * beg = ptr + 1;

        do {
            ++ptr;
            CV_PERSISTENCE_CHECK_END_OF_BUFFER_BUG_CPP();
        } while( cv_isprint(*ptr) && *ptr != '"' );

        if( *ptr != '"' )
            CV_PARSE_ERROR_CPP( "STR" );

        const char * end = ptr;
        ptr++;
        ptr = skipSpaces( ptr );
        if( !ptr || !*ptr )
            return 0;

        if( *ptr != ':' )
            CV_PARSE_ERROR_CPP( "STR" );

        
        if( end <= beg )
            CV_PARSE_ERROR_CPP( "STR" );

        value_placeholder = fs->addNode(collection, std::string(beg, (size_t)(end - beg)), FileNode::NONE);
        return ++ptr;
    }