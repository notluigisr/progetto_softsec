func_breakpoint(void *cookie)
{
    return &((funccall_T *)cookie)->breakpoint;
}