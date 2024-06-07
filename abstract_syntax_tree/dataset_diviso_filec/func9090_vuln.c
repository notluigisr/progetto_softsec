extern "STR" const char * aspell_version_string() {
#ifdef NDEBUG
  return VERSION "STR";
#endif
  return VERSION;
}