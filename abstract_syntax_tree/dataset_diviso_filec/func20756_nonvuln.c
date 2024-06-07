int exif_inf(png_structp png_ptr, unsigned char *source,
    unsigned char **dest, size_t n, png_uint_32 inflated_size)
{
    

    int ret;
    z_stream strm;

    size_t inflated_length = inflated_size;

    if (inflated_length >= PNG_USER_CHUNK_MALLOC_MAX - 1U ||
        inflated_length == 0)
        return (-1);

    
#if PNG_LIBPNG_VER >= 14000
    *dest=(unsigned char *) png_malloc(png_ptr,
       (png_alloc_size_t) inflated_length);
#else
    *dest=(unsigned char *) png_malloc(png_ptr,
       (png_size_t) inflated_length);
#endif
    
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return (-1);
    
    do {
        strm.avail_in = (int)n;
        strm.next_in = source;

        
        do {
            strm.avail_out = (int)inflated_length;
            strm.next_out = *dest;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);  
            switch (ret) {
            case Z_NEED_DICT:
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
                return (-1);
            }
        } while (strm.avail_out == 0);
        
    } while (ret != Z_STREAM_END);

    

    

    (void)inflateEnd(&strm);
    return (inflated_length);
}