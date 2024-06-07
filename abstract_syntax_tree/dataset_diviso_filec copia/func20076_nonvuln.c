bool constructor(JSContext *cx, unsigned argc, Value *vp) {
  CTOR_HEADER("STR", 0);

  RootedObject self(cx, JS_NewObjectForConstructor(cx, &class_, args));
  if (!self)
    return false;

  args.rval().setObject(*self);
  return true;
}