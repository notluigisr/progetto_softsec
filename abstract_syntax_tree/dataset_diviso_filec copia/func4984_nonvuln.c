ex_unlet(exarg_T *eap)
{
    ex_unletlock(eap, eap->arg, 0, 0, do_unlet_var, NULL);
}