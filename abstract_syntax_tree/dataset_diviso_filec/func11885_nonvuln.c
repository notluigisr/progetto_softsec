bool ok_get(JSContext *cx, unsigned argc, Value *vp) {
  METHOD_HEADER(0)

  uint16_t status = Response::status(self);
  args.rval().setBoolean(status >= 200 && status < 300);
  return true;
}