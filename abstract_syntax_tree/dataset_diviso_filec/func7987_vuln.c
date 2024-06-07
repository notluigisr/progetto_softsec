STATIC U8 *
S_reghop3(U8 *s, SSize_t off, const U8* lim)
{
    

    PERL_ARGS_ASSERT_REGHOP3;

    if (off >= 0) {
	while (off-- && s < lim) {
	    
	    s += UTF8SKIP(s);
	}
    }
    else {
        while (off++ && s > lim) {
            s--;
            if (UTF8_IS_CONTINUED(*s)) {
                while (s > lim && UTF8_IS_CONTINUATION(*s))
                    s--;
	    }
            
	}
    }
    return s;