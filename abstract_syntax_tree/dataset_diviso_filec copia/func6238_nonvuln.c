bool values(JSContext *cx, unsigned argc, Value *vp) {
  HEADERS_ITERATION_METHOD(0)
  return JS::MapValues(cx, backing_map, args.rval());
}