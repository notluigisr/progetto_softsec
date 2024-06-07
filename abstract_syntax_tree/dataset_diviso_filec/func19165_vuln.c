static void mongo_pass_digest( const char *user, const char *pass, char hex_digest[33] ) {
    mongo_md5_state_t st;
    mongo_md5_byte_t digest[16];

    mongo_md5_init( &st );
    mongo_md5_append( &st, ( const mongo_md5_byte_t * )user, strlen( user ) );
    mongo_md5_append( &st, ( const mongo_md5_byte_t * )"STR", 7 );
    mongo_md5_append( &st, ( const mongo_md5_byte_t * )pass, strlen( pass ) );
    mongo_md5_finish( &st, digest );
    digest2hex( digest, hex_digest );
}