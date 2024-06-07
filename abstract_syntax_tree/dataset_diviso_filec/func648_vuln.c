    if (!NIL_P(exc)) {
        volatile VALUE eclass = rb_obj_class(exc);
        volatile VALUE backtrace;

        DUMP1("STR");

        thr_crit_bup = rb_thread_critical;
        rb_thread_critical = Qtrue;

        DUMP1("STR");
        if (!NIL_P(backtrace = rb_funcallv(exc, ID_backtrace, 0, 0))) {
            backtrace = rb_ary_join(backtrace, rb_str_new2("STR"));
            Tcl_AddErrorInfo(interp, StringValuePtr(backtrace));
        }

        rb_thread_critical = thr_crit_bup;

        ip_set_exc_message(interp, exc);

        if (eclass == eTkCallbackReturn)
            return TCL_RETURN;

        if (eclass == eTkCallbackBreak)
            return TCL_BREAK;

        if (eclass == eTkCallbackContinue)
            return TCL_CONTINUE;

        if (eclass == rb_eSystemExit || eclass == rb_eInterrupt) {
            rbtk_pending_exception = exc;
            return TCL_RETURN;
        }

        if (rb_obj_is_kind_of(exc, eTkLocalJumpError)) {
            rbtk_pending_exception = exc;
            return TCL_ERROR;
        }

        if (rb_obj_is_kind_of(exc, eLocalJumpError)) {
            VALUE reason = rb_ivar_get(exc, ID_at_reason);

            if (RB_TYPE_P(reason, T_SYMBOL)) {
                if (SYM2ID(reason) == ID_return)
                    return TCL_RETURN;

                if (SYM2ID(reason) == ID_break)
                    return TCL_BREAK;

                if (SYM2ID(reason) == ID_next)
                    return TCL_CONTINUE;
            }
        }

        return TCL_ERROR;
    }