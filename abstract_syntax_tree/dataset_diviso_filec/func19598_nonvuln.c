UnicodeString::copy(int32_t start, int32_t limit, int32_t dest) {
    if (limit <= start) {
        return; 
    }
    UChar* text = (UChar*) uprv_malloc( sizeof(UChar) * (limit - start) );
    
    if (text != NULL) {
	    extractBetween(start, limit, text, 0);
	    insert(dest, text, 0, limit - start);    
	    uprv_free(text);
    }
}