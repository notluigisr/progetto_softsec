void throw_exception(CLI *c, int v) {
    if(!c || !c->exception_pointer)
        fatal("STR");
    longjmp(*c->exception_pointer, v);
}