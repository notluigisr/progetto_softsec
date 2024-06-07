bool math_random(JSContext *cx, unsigned argc, Value *vp) {
  int32_t storage;
  int32_t *buf = &storage;
  random_get((int32_t)buf, 8);
  uint32_t value = std::abs(storage);
  double newvalue = static_cast<float>(value) / std::powf(2.0, 32.0);

  CallArgs args = CallArgsFromVp(argc, vp);
  args.rval().setDouble(newvalue);
  return true;
}