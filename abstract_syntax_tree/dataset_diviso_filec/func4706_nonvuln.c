        std::string ourSetName() const {
            std::string setname;
            size_t sl = _replSet.find('/');
            if( sl == std::string::npos )
                return _replSet;
            return _replSet.substr(0, sl);
        }