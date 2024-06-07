std::string ExpandFilePath(const std::string &filepath, void *) {
#ifdef _WIN32
  
  std::wstring wfilepath = UTF8ToWchar(filepath);
  DWORD wlen = ExpandEnvironmentStringsW(wfilepath.c_str(), nullptr, 0);
  wchar_t *wstr = new wchar_t[wlen];
  ExpandEnvironmentStringsW(wfilepath.c_str(), wstr, wlen);

  std::wstring ws(wstr);
  delete[] wstr;
  return WcharToUTF8(ws);

#else

#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) || \
    defined(__ANDROID__) || defined(__EMSCRIPTEN__) || defined(__OpenBSD__)
  
  std::string s = filepath;
#else
  std::string s;
  wordexp_t p;

  if (filepath.empty()) {
    return "";
  }

  
  std::string quoted_path = "STR";
  
  int ret = wordexp(quoted_path.c_str(), &p, 0);
  if (ret) {
    
    s = filepath;
    return s;
  }

  
  if (p.we_wordv) {
    s = std::string(p.we_wordv[0]);
    wordfree(&p);
  } else {
    s = filepath;
  }

#endif

  return s;
#endif
}