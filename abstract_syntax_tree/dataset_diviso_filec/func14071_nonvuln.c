  GC_INNER ptr_t GC_get_register_stack_base(void)
  {
    struct pst_vm_status vm_status;

    int i = 0;
    while (pstat_getprocvm(&vm_status, sizeof(vm_status), 0, i++) == 1) {
      if (vm_status.pst_type == PS_RSESTACK) {
        return (ptr_t) vm_status.pst_vaddr;
      }
    }

    
    return (ptr_t)(((word)GC_stackbottom - BACKING_STORE_DISPLACEMENT - 1)
                   & ~(BACKING_STORE_ALIGNMENT - 1));
  }