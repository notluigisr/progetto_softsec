    GC_API int GC_CALL GC_get_stack_base(struct GC_stack_base *sb)
    {
#     ifdef X86_64
        sb -> mem_base = ((NT_TIB*)NtCurrentTeb())->StackBase;
#     else
        void * _tlsbase;

        __asm__ ("STR"
                 : "STR" (_tlsbase));
        sb -> mem_base = _tlsbase;
#     endif
      return GC_SUCCESS;
    }