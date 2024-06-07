    bool BSONObj::valid() const {
        int mySize = objsize();

        try {
            BSONObjIterator it(*this);
            while( it.moreWithEOO() ) {
                
                BSONElement e = it.next(true);
                if ( e.size() >= mySize )
                    return false;

                e.validate();

                if (e.eoo()) {
                    if (it.moreWithEOO())
                        return false;
                    return true;
                }
                else if (e.isABSONObj()) {
                    if(!e.embeddedObject().valid())
                        return false;
                }
                else if (e.type() == CodeWScope) {
                    if(!e.codeWScopeObject().valid())
                        return false;
                }
            }
        }
        catch (...) {
        }
        return false;
    }