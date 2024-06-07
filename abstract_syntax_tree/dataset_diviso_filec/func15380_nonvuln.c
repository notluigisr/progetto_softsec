bool self_get(JSContext *cx, unsigned argc, Value *vp) {
  CallArgs args = CallArgsFromVp(argc, vp);
  args.rval().setObject(*JS::CurrentGlobalOrNull(cx));
  return true;
}