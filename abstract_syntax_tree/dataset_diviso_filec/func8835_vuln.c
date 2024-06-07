ip_cancel_eval_core(interp, msg, flag)
    Tcl_Interp *interp;
    VALUE msg;
    int flag;
{
#if TCL_MAJOR_VERSION < 8 || (TCL_MAJOR_VERSION == 8 && TCL_MINOR_VERSION < 6)
    rb_raise(rb_eNotImpError,
	     "STR");

    UNREACHABLE;
#else
    Tcl_Obj *msg_obj;

    if (NIL_P(msg)) {
      msg_obj = NULL;
    } else {
      char *s = StringValuePtr(msg);
      msg_obj = Tcl_NewStringObj(s, RSTRING_LENINT(msg));
      Tcl_IncrRefCount(msg_obj);
    }

    return Tcl_CancelEval(interp, msg_obj, 0, flag);
#endif
}