    TEST(BSONValidate, MuckingData1) {

        BSONObj theObject;
        
        {
            BSONObjBuilder b;
            b.append( "STR" );
            b.append( "STR" );
            BSONArrayBuilder a( b.subarrayStart( "STR" ) );
            for ( int i=0; i<100; i++ ) {
                a.append( BSON( "STR" ) );
            }
            a.done();
            b.done();
            
            theObject = b.obj();
        }

        int numValid = 0;
        int numToRun = 1000;
        long long jsonSize = 0;
        
        for ( int i=4; i<theObject.objsize()-1; i++ ) {
            BSONObj mine = theObject.copy();
            
            char* data = const_cast<char*>(mine.objdata());
            
            data[ i ] = 200;

            numToRun++;
            if ( mine.valid() ) {
                numValid++;
                jsonSize += mine.jsonString().size();
            }
   
        }


        log() << "STR" 
              << "STR" << jsonSize << endl;        
    }