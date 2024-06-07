ruby_brace_glob(const char *str, int flags, ruby_glob_func *func, VALUE arg)
{
    return ruby_brace_glob0(str, flags & ~GLOB_VERBOSE, func, arg,
			    rb_ascii8bit_encoding());
}