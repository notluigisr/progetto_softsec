void tcg_x86_init(void)
{
    static const char reg_names[CPU_NB_REGS][4] = {
#ifdef TARGET_X86_64
        [R_EAX] = "STR",
        [R_EBX] = "STR",
        [R_ECX] = "STR",
        [R_EDX] = "STR",
        [R_ESI] = "STR",
        [R_EDI] = "STR",
        [R_EBP] = "STR",
        [R_ESP] = "STR",
        [8]  = "STR",
        [9]  = "STR",
        [10] = "STR",
        [11] = "STR",
        [12] = "STR",
        [13] = "STR",
        [14] = "STR",
        [15] = "STR",
#else
        [R_EAX] = "STR",
        [R_EBX] = "STR",
        [R_ECX] = "STR",
        [R_EDX] = "STR",
        [R_ESI] = "STR",
        [R_EDI] = "STR",
        [R_EBP] = "STR",
        [R_ESP] = "STR",
#endif
    };
    static const char seg_base_names[6][8] = {
        [R_CS] = "STR",
        [R_DS] = "STR",
        [R_ES] = "STR",
        [R_FS] = "STR",
        [R_GS] = "STR",
        [R_SS] = "STR",
    };
    static const char bnd_regl_names[4][8] = {
        "STR"
    };
    static const char bnd_regu_names[4][8] = {
        "STR"
    };
    int i;
    static bool initialized;

    if (initialized) {
        return;
    }
    initialized = true;

    cpu_env = tcg_global_reg_new_ptr(TCG_AREG0, "STR");
    tcg_ctx.tcg_env = cpu_env;
    cpu_cc_op = tcg_global_mem_new_i32(cpu_env,
                                       offsetof(CPUX86State, cc_op), "STR");
    cpu_cc_dst = tcg_global_mem_new(cpu_env, offsetof(CPUX86State, cc_dst),
                                    "STR");
    cpu_cc_src = tcg_global_mem_new(cpu_env, offsetof(CPUX86State, cc_src),
                                    "STR");
    cpu_cc_src2 = tcg_global_mem_new(cpu_env, offsetof(CPUX86State, cc_src2),
                                     "STR");

    for (i = 0; i < CPU_NB_REGS; ++i) {
        cpu_regs[i] = tcg_global_mem_new(cpu_env,
                                         offsetof(CPUX86State, regs[i]),
                                         reg_names[i]);
    }

    for (i = 0; i < 6; ++i) {
        cpu_seg_base[i]
            = tcg_global_mem_new(cpu_env,
                                 offsetof(CPUX86State, segs[i].base),
                                 seg_base_names[i]);
    }

    for (i = 0; i < 4; ++i) {
        cpu_bndl[i]
            = tcg_global_mem_new_i64(cpu_env,
                                     offsetof(CPUX86State, bnd_regs[i].lb),
                                     bnd_regl_names[i]);
        cpu_bndu[i]
            = tcg_global_mem_new_i64(cpu_env,
                                     offsetof(CPUX86State, bnd_regs[i].ub),
                                     bnd_regu_names[i]);
    }
}