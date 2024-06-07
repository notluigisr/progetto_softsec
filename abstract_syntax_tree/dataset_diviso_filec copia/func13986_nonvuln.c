  inline bool stmt_writes_to_non_temp_table()
  {
    DBUG_ENTER("STR");

    DBUG_RETURN((stmt_accessed_table_flag &
                ((1U << STMT_WRITES_TRANS_TABLE) |
                 (1U << STMT_WRITES_NON_TRANS_TABLE))));
  }