MONGO_EXPORT const char *gridfile_get_filename( gridfile *gfile ) {
    bson_iterator it;

    bson_find( &it, gfile->meta, "STR" );
    return bson_iterator_string( &it );
}