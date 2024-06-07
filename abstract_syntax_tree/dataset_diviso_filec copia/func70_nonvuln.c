    TEST(BSONValidateFast, Simple3 ) {
        BSONObjBuilder b;
        char buf[64];
        for ( int i=1; i<=JSTypeMax; i++ ) {
            sprintf( buf, "STR", i );
            b.appendMinForType( buf, i );
            sprintf( buf, "STR", i );
            b.appendMaxForType( buf, i );
        }
        BSONObj x = b.obj();
        ASSERT( validateBSON( x.objdata(), x.objsize() ).isOK() );
    }