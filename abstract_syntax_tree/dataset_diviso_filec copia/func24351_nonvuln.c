mrb_prepend_module(mrb_state *mrb, struct RClass *c, struct RClass *m)
{
  struct RClass *origin;

  mrb_check_frozen(mrb, c);
  if (!(c->flags & MRB_FL_CLASS_IS_PREPENDED)) {
    struct RClass *c0;

    if (c->tt == MRB_TT_ICLASS) {
      c0 = c->c;
    }
    else {
      c0 = c;
    }
    origin = MRB_OBJ_ALLOC(mrb, MRB_TT_ICLASS, c0);
    origin->flags |= MRB_FL_CLASS_IS_ORIGIN | MRB_FL_CLASS_IS_INHERITED;
    origin->super = c->super;
    c->super = origin;
    origin->mt = c->mt;
    c->mt = NULL;
    origin->iv = c->iv;
    mrb_field_write_barrier(mrb, (struct RBasic*)c, (struct RBasic*)origin);
    c->flags |= MRB_FL_CLASS_IS_PREPENDED;
  }
  if (include_module_at(mrb, c, c, m, 0) < 0) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "STR");
  }
  if (c->tt == MRB_TT_MODULE &&
      (c->flags & (MRB_FL_CLASS_IS_INHERITED|MRB_FL_CLASS_IS_PREPENDED))) {
    struct RClass *data[2];
    data[0] = c;
    data[1] = m;
    mrb_objspace_each_objects(mrb, fix_prepend_module, data);
  }
}