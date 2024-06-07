  inline void get_binlog_format(enum_binlog_format *format,
                                enum_binlog_format *current_format)
  {
    *format= (enum_binlog_format) variables.binlog_format;
    *current_format= current_stmt_binlog_format;
  }