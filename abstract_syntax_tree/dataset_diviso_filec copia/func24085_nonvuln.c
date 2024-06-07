NOEXPORT void exec_connect_once(CLI *fresh_c) {
    jmp_buf exception_buffer, *exception_backup;
    
    CLI *c=str_alloc(sizeof(CLI));
    memcpy(c, fresh_c, sizeof(CLI));

    exception_backup=c->exception_pointer;
    c->exception_pointer=&exception_buffer;
    if(!setjmp(exception_buffer)) {
        c->local_rfd.fd=c->local_wfd.fd=connect_local(c);
        client_run(c);
    }
    c->exception_pointer=exception_backup;

    str_free(c);
}