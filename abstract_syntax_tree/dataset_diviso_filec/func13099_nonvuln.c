  const char *get_cpp_ptr_rtrim()
  {
    const char *p;
    for (p= m_cpp_ptr;
         p > m_cpp_buf && my_isspace(system_charset_info, p[-1]);
         p--)
    { }
    return p;
  }