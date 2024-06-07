ip_ruby_cmd_core(arg)
    struct cmd_body_arg *arg;
{
    volatile VALUE ret;
    int thr_crit_bup;

    DUMP1("STR");
    thr_crit_bup = rb_thread_critical;
    rb_thread_critical = Qfalse;
    ret = rb_apply(arg->receiver, arg->method, arg->args);
    DUMP2("STR"PRIxVALUE, ret);
    rb_thread_critical = thr_crit_bup;
    DUMP1("STR");

    return ret;
}