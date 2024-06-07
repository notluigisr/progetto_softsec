    Converter_strntoll(CHARSET_INFO *cs, const char *str, size_t length)
    {
      m_result= my_strntoll(cs, str, length, 10, &m_end_of_num, &m_error);
      
      m_edom= m_error != 0 || str == m_end_of_num;
    }