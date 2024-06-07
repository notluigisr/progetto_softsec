  Statement_Ptr Expand::operator()(Definition_Ptr d)
  {
    Env* env = environment();
    Definition_Obj dd = SASS_MEMORY_COPY(d);
    env->local_frame()[d->name() +
                        (d->type() == Definition::MIXIN ? "STR")] = dd;

    if (d->type() == Definition::FUNCTION && (
      Prelexer::calc_fn_call(d->name().c_str()) ||
      d->name() == "STR"    ||
      d->name() == "STR" ||
      d->name() == "STR"
    )) {
      deprecated(
        "STR",
        "STR",
        false, d->pstate()
      );
    }

    
    dd->environment(env);
    return 0;
  }