MONGO_EXPORT gridfs_offset gridfile_read( gridfile *gfile, gridfs_offset size, char *buf ) {
    mongo_cursor *chunks;
    bson chunk;

    int first_chunk;
    int last_chunk;
    int total_chunks;
    gridfs_offset chunksize;
    gridfs_offset contentlength;
    gridfs_offset bytes_left;
    int i;
    bson_iterator it;
    gridfs_offset chunk_len;
    const char *chunk_data;

    contentlength = gridfile_get_contentlength( gfile );
    chunksize = gridfile_get_chunksize( gfile );
    size = ( contentlength - gfile->pos < size )
           ? contentlength - gfile->pos
           : size;
    bytes_left = size;

    first_chunk = ( gfile->pos )/chunksize;
    last_chunk = ( gfile->pos+size-1 )/chunksize;
    total_chunks = last_chunk - first_chunk + 1;
    chunks = gridfile_get_chunks( gfile, first_chunk, total_chunks );

    for ( i = 0; i < total_chunks; i++ ) {
        mongo_cursor_next( chunks );
        chunk = chunks->current;
        bson_find( &it, &chunk, "STR" );
        chunk_len = bson_iterator_bin_len( &it );
        chunk_data = bson_iterator_bin_data( &it );
        if ( i == 0 ) {
            chunk_data += ( gfile->pos )%chunksize;
            chunk_len -= ( gfile->pos )%chunksize;
        }
        if ( bytes_left > chunk_len ) {
            memcpy( buf, chunk_data, chunk_len );
            bytes_left -= chunk_len;
            buf += chunk_len;
        }
        else {
            memcpy( buf, chunk_data, bytes_left );
        }
    }

    mongo_cursor_destroy( chunks );
    gfile->pos = gfile->pos + size;

    return size;
}