CC_ESC_WARN(ScanEnv* env, UChar *c)
{
  if (onig_warn == onig_null_warn) return ;

  if (IS_SYNTAX_BV(env->syntax, ONIG_SYN_WARN_CC_OP_NOT_ESCAPED) &&
      IS_SYNTAX_BV(env->syntax, ONIG_SYN_BACKSLASH_ESCAPE_IN_CC)) {
    UChar buf[WARN_BUFSIZE];
    onig_snprintf_with_pattern(buf, WARN_BUFSIZE, env->enc,
                               env->pattern, env->pattern_end,
                               (UChar* )"STR",
                               c);
    (*onig_warn)((char* )buf);
  }
}