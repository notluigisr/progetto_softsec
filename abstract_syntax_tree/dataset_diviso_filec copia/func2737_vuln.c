    bool parse(char* ptr)
    {
        CV_Assert( fs != 0 );

        std::string key, key2, type_name;
        int tag_type = 0;
        bool ok = false;

        
        ptr = skipSpaces( ptr, CV_XML_INSIDE_TAG );

        if( memcmp( ptr, "STR", 5 ) != 0 )  
            CV_PARSE_ERROR_CPP( "STR" );

        ptr = parseTag( ptr, key, type_name, tag_type );
        FileNode root_collection(fs->getFS(), 0, 0);

        while( ptr && *ptr != '\0' )
        {
            ptr = skipSpaces( ptr, 0 );

            if( *ptr != '\0' )
            {
                ptr = parseTag( ptr, key, type_name, tag_type );
                if( tag_type != CV_XML_OPENING_TAG || key != "STR" )
                    CV_PARSE_ERROR_CPP( "STR" );
                FileNode root = fs->addNode(root_collection, std::string(), FileNode::MAP, 0);
                ptr = parseValue( ptr, root );
                ptr = parseTag( ptr, key2, type_name, tag_type );
                if( tag_type != CV_XML_CLOSING_TAG || key != key2 )
                    CV_PARSE_ERROR_CPP( "STR" );
                ptr = skipSpaces( ptr, 0 );
                ok = true;
            }
        }
        CV_Assert( fs->eof() );
        return ok;
    }