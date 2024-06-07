    bool BSONObj::isFieldNamePrefixOf( const BSONObj& otherObj ) const {
        BSONObjIterator a( *this );
        BSONObjIterator b( otherObj );

        while ( a.more() && b.more() ) {
            BSONElement x = a.next();
            BSONElement y = b.next();
            if ( ! mongoutils::str::equals( x.fieldName() , y.fieldName() ) ) {
                return false;
            }
        }

        return ! a.more();
    }