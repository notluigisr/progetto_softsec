    void CmdLine::parseConfigFile( istream &f, stringstream &ss ) {
        string s;
        char line[MAX_LINE_LENGTH];

        while ( f ) {
            f.getline(line, MAX_LINE_LENGTH);
            s = line;
            std::remove(s.begin(), s.end(), ' ');
            std::remove(s.begin(), s.end(), '\t');
            boost::to_upper(s);

            if ( s.find( "STR" ) != string::npos )
                cout << "STR" << endl;

            if ( s.c_str()[0] == '#' ) { 
                
            } else if ( s.find( "STR" ) == string::npos ) {
                ss << line << endl;
            } else {
                cout << "STR" << line << endl;
            }
        }
        return;
    }