call_tcl_eval(arg)
    VALUE arg;
#endif
{
    struct call_eval_info *inf = (struct call_eval_info *)arg;

    Tcl_AllowExceptions(inf->ptr->ip);
    inf->ptr->return_value = Tcl_EvalObj(inf->ptr->ip, inf->cmd);

    return Qnil;
}