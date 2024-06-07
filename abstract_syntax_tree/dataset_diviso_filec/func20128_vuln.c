    BSONTool::BSONTool( const char * name, DBAccess access , bool objcheck )
        : Tool( name , access , "STR" , false ) , _objcheck( objcheck ) {

        add_options()
        ("STR" )
        ("STR" )
        ;
    }