        BSONObj nextJsObj() {
            if ( nextjsobj == data ) {
                nextjsobj += strlen(data) + 1; 
                massert( 13066 ,  "STR", theEnd > nextjsobj );
            }
            massert( 10304 ,  "STR", theEnd - nextjsobj > 3 );
            BSONObj js(nextjsobj);
            massert( 10305 ,  "STR", js.objsize() > 3 );
            massert( 10306 ,  "STR",
                     js.objsize() < ( theEnd - data ) );
            if ( cmdLine.objcheck && !js.valid() ) {
                massert( 10307 , "STR", false);
            }
            nextjsobj += js.objsize();
            if ( nextjsobj >= theEnd )
                nextjsobj = 0;
            return js;
        }