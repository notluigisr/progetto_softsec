alloc_invoke_arguments(argc, argv)
    int argc;
    VALUE *argv;
{
    int i;
    int thr_crit_bup;

#if TCL_MAJOR_VERSION >= 8
    Tcl_Obj **av;
#else 
    char **av;
#endif

    thr_crit_bup = rb_thread_critical;
    rb_thread_critical = Qtrue;

    
#if TCL_MAJOR_VERSION >= 8
     
    av = RbTk_ALLOC_N(Tcl_Obj *, (argc+1));
#if 0 
    Tcl_Preserve((ClientData)av); 
#endif
    for (i = 0; i < argc; ++i) {
        av[i] = get_obj_from_str(argv[i]);
        Tcl_IncrRefCount(av[i]);
    }
    av[argc] = NULL;

#else 
    
    
    av = RbTk_ALLOC_N(char *, (argc+1));
#if 0 
    Tcl_Preserve((ClientData)av); 
#endif
    for (i = 0; i < argc; ++i) {
        av[i] = strdup(StringValuePtr(argv[i]));
    }
    av[argc] = NULL;
#endif

    rb_thread_critical = thr_crit_bup;

    return av;
}