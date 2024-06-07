fiddle_handle_sym(void *handle, const char *name)
{
#if defined(HAVE_DLERROR)
    const char *err;
# define CHECK_DLERROR if( err = dlerror() ){ func = 0; }
#else
# define CHECK_DLERROR
#endif
    void (*func)();

    rb_secure(2);
#ifdef HAVE_DLERROR
    dlerror();
#endif
    func = (void (*)())(VALUE)dlsym(handle, name);
    CHECK_DLERROR;
#if defined(FUNC_STDCALL)
    if( !func ){
	int  i;
	int  len = (int)strlen(name);
	char *name_n;
#if defined(__CYGWIN__) || defined(_WIN32) || defined(__MINGW32__)
	{
	    char *name_a = (char*)xmalloc(len+2);
	    strcpy(name_a, name);
	    name_n = name_a;
	    name_a[len]   = 'A';
	    name_a[len+1] = '\0';
	    func = dlsym(handle, name_a);
	    CHECK_DLERROR;
	    if( func ) goto found;
	    name_n = xrealloc(name_a, len+6);
	}
#else
	name_n = (char*)xmalloc(len+6);
#endif
	memcpy(name_n, name, len);
	name_n[len++] = '@';
	for( i = 0; i < 256; i += 4 ){
	    sprintf(name_n + len, "STR", i);
	    func = dlsym(handle, name_n);
	    CHECK_DLERROR;
	    if( func ) break;
	}
	if( func ) goto found;
	name_n[len-1] = 'A';
	name_n[len++] = '@';
	for( i = 0; i < 256; i += 4 ){
	    sprintf(name_n + len, "STR", i);
	    func = dlsym(handle, name_n);
	    CHECK_DLERROR;
	    if( func ) break;
	}
      found:
	xfree(name_n);
    }
#endif
    if( !func ){
	rb_raise(rb_eFiddleError, "STR", name);
    }

    return PTR2NUM(func);
}