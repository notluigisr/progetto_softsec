bool WebContents::IsOffScreen() const {
#if BUILDFLAG(ENABLE_OSR)
  return type_ == Type::kOffScreen;
#else
  return false;
#endif
}