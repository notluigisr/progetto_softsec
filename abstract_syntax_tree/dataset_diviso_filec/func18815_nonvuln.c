int Lex_input_stream::find_keyword(Lex_ident_cli_st *kwd,
                                   uint len, bool function)
{
  const char *tok= m_tok_start;

  SYMBOL *symbol= get_hash_symbol(tok, len, function);
  if (symbol)
  {
    kwd->set_keyword(tok, len);
    DBUG_ASSERT(tok >= get_buf());
    DBUG_ASSERT(tok < get_end_of_query());

    if (m_thd->variables.sql_mode & MODE_ORACLE)
    {
      switch (symbol->tok) {
      case BEGIN_MARIADB_SYM:          return BEGIN_ORACLE_SYM;
      case BLOB_MARIADB_SYM:           return BLOB_ORACLE_SYM;
      case BODY_MARIADB_SYM:           return BODY_ORACLE_SYM;
      case CLOB_MARIADB_SYM:           return CLOB_ORACLE_SYM;
      case CONTINUE_MARIADB_SYM:       return CONTINUE_ORACLE_SYM;
      case DECLARE_MARIADB_SYM:        return DECLARE_ORACLE_SYM;
      case DECODE_MARIADB_SYM:         return DECODE_ORACLE_SYM;
      case ELSEIF_MARIADB_SYM:         return ELSEIF_ORACLE_SYM;
      case ELSIF_MARIADB_SYM:          return ELSIF_ORACLE_SYM;
      case EXCEPTION_MARIADB_SYM:      return EXCEPTION_ORACLE_SYM;
      case EXIT_MARIADB_SYM:           return EXIT_ORACLE_SYM;
      case GOTO_MARIADB_SYM:           return GOTO_ORACLE_SYM;
      case NUMBER_MARIADB_SYM:         return NUMBER_ORACLE_SYM;
      case OTHERS_MARIADB_SYM:         return OTHERS_ORACLE_SYM;
      case PACKAGE_MARIADB_SYM:        return PACKAGE_ORACLE_SYM;
      case RAISE_MARIADB_SYM:          return RAISE_ORACLE_SYM;
      case RAW_MARIADB_SYM:            return RAW_ORACLE_SYM;
      case RETURN_MARIADB_SYM:         return RETURN_ORACLE_SYM;
      case ROWTYPE_MARIADB_SYM:        return ROWTYPE_ORACLE_SYM;
      case VARCHAR2_MARIADB_SYM:       return VARCHAR2_ORACLE_SYM;
      }
    }

    if ((symbol->tok == NOT_SYM) &&
        (m_thd->variables.sql_mode & MODE_HIGH_NOT_PRECEDENCE))
      return NOT2_SYM;
    if ((symbol->tok == OR2_SYM) &&
        (m_thd->variables.sql_mode & MODE_PIPES_AS_CONCAT))
    {
      return (m_thd->variables.sql_mode & MODE_ORACLE) ?
             ORACLE_CONCAT_SYM : MYSQL_CONCAT_SYM;
    }

    return symbol->tok;
  }
  return 0;
}