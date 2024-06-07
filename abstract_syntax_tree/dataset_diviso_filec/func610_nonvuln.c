  void set_bulk_execution(void *bulk)
  {
    bulk_param= bulk;
    m_stmt_da->set_bulk_execution(MY_TEST(bulk));
  }