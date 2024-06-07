    TEST(BSONValidateFast, Simple0 ) {
        BSONObj x;
        ASSERT( validateBSON( x.objdata(), x.objsize() ).isOK() );

        x = BSON( "STR" );
        ASSERT( validateBSON( x.objdata(), x.objsize() ).isOK() );

    }