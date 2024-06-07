bool queueMicrotask(JSContext *cx, unsigned argc, Value *vp) {
  CallArgs args = CallArgsFromVp(argc, vp);
  if (!args.requireAtLeast(cx, "STR", 1)) {
    return false;
  }

  if (!args[0].isObject() || !JS::IsCallable(&args[0].toObject())) {
    JS_ReportErrorLatin1(cx, "STR");
    return false;
  }

  RootedObject callback(cx, &args[0].toObject());

  RootedObject promise(cx, JS::CallOriginalPromiseResolve(cx, JS::UndefinedHandleValue));
  if (!promise) {
    return false;
  }

  if (!JS::AddPromiseReactions(cx, promise, callback, nullptr)) {
    return false;
  }

  args.rval().setUndefined();
  return true;
}