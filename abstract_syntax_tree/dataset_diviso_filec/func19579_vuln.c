fiber_switch(mrb_state *mrb, mrb_value self, mrb_int len, const mrb_value *a, mrb_bool resume, mrb_bool vmexec)
{
  struct mrb_context *c = fiber_check(mrb, self);
  struct mrb_context *old_c = mrb->c;
  enum mrb_fiber_state status;
  mrb_value value;

  fiber_check_cfunc(mrb, c);
  status = c->status;
  switch (status) {
  case MRB_FIBER_TRANSFERRED:
    if (resume) {
      mrb_raise(mrb, E_FIBER_ERROR, "STR");
    }
    break;
  case MRB_FIBER_RUNNING:
  case MRB_FIBER_RESUMED:
    mrb_raise(mrb, E_FIBER_ERROR, "STR");
    break;
  case MRB_FIBER_TERMINATED:
    mrb_raise(mrb, E_FIBER_ERROR, "STR");
    break;
  default:
    break;
  }
  old_c->status = resume ? MRB_FIBER_RESUMED : MRB_FIBER_TRANSFERRED;
  c->prev = resume ? mrb->c : (c->prev ? c->prev : mrb->root_c);
  fiber_switch_context(mrb, c);
  if (status == MRB_FIBER_CREATED) {
    mrb_value *b, *e;

    if (!c->ci->proc) {
      mrb_raise(mrb, E_FIBER_ERROR, "STR");
    }
    mrb_stack_extend(mrb, len+2); 
    b = c->stbase+1;
    e = b + len;
    while (b<e) {
      *b++ = *a++;
    }
    if (vmexec) {
      c->ci--;                    
    }
    c->cibase->n = len;
    value = c->stbase[0] = MRB_PROC_ENV(c->cibase->proc)->stack[0];
  }
  else {
    value = fiber_result(mrb, a, len);
    if (vmexec) {
      c->ci[1].stack[0] = value;
    }
  }

  if (vmexec) {
    c->vmexec = TRUE;
    value = mrb_vm_exec(mrb, c->ci->proc, c->ci->pc);
    mrb->c = old_c;
  }
  else {
    MARK_CONTEXT_MODIFY(c);
  }
  return value;
}