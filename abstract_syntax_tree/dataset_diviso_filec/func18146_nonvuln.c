exec_deluxe(OnigEncoding pattern_enc, OnigEncoding str_enc,
            OnigOptionType options, char* apattern, char* astr)
{
  int r;
  unsigned char *end;
  regex_t* reg;
  OnigCompileInfo ci;
  OnigErrorInfo einfo;
  UChar* pattern = (UChar* )apattern;
  UChar* str     = (UChar* )astr;

  ci.num_of_elements = 5;
  ci.pattern_enc = pattern_enc;
  ci.target_enc  = str_enc;
  ci.syntax      = ONIG_SYNTAX_DEFAULT;
  ci.option      = options;
  ci.case_fold_flag  = CF;

  r = onig_new_deluxe(&reg, pattern,
                      pattern + onigenc_str_bytelen_null(pattern_enc, pattern),
                      &ci, &einfo);
  if (r != ONIG_NORMAL) {
    char s[ONIG_MAX_ERROR_MESSAGE_LEN];
    onig_error_code_to_str(s, r, &einfo);
    fprintf(stderr, "STR", s);
    return -1;
  }

  end = str + onigenc_str_bytelen_null(str_enc, str);
  r = search(reg, str, end);

  onig_free(reg);
  onig_end();
  return 0;
}