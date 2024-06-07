    bool parse( char* ptr )
    {
        ptr = skipSpaces( ptr );
        if ( !ptr || !*ptr )
            return false;

        FileNode root_collection(fs->getFS(), 0, 0);

        if( *ptr == '{' )
        {
            FileNode root_node = fs->addNode(root_collection, std::string(), FileNode::MAP);
            parseMap( ptr, root_node );
        }
        else if ( *ptr == '[' )
        {
            FileNode root_node = fs->addNode(root_collection, std::string(), FileNode::SEQ);
            parseSeq( ptr, root_node );
        }
        else
        {
            CV_PARSE_ERROR_CPP( "STR" );
        }

        if( !ptr || !*ptr )
            CV_PARSE_ERROR_CPP( "STR" );
        return true;
    }