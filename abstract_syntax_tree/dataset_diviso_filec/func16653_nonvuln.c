    if (argv) {
      
      int i;
      for(i = 0; i < argc; i++) { argv[i] = (VALUE)NULL; }

#if 0 
      Tcl_EventuallyFree((ClientData)argv, TCL_DYNAMIC); 
#else
#if 0 
      Tcl_Release((ClientData)argv); 
#else
      ckfree((char*)argv);
#endif
#endif
    }