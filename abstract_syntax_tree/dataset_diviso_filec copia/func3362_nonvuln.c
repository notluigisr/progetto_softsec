parse_subexp(Node** top, PToken* tok, int term, UChar** src, UChar* end,
             ScanEnv* env, int group_head)
{
  int r;
  Node *node, **headp;

  *top = NULL;
  env->parse_depth++;
  if (env->parse_depth > ParseDepthLimit)
    return ONIGERR_PARSE_DEPTH_LIMIT_OVER;

  r = parse_branch(&node, tok, term, src, end, env, group_head);
  if (r < 0) {
    onig_node_free(node);
    return r;
  }

  if (r == term) {
    *top = node;
  }
  else if (r == TK_ALT) {
    *top  = onig_node_new_alt(node, NULL);
    if (IS_NULL(*top)) {
      onig_node_free(node);
      return ONIGERR_MEMORY;
    }

    headp = &(NODE_CDR(*top));
    while (r == TK_ALT) {
      r = fetch_token(tok, src, end, env);
      if (r < 0) return r;
      r = parse_branch(&node, tok, term, src, end, env, 0);
      if (r < 0) {
        onig_node_free(node);
        return r;
      }
      *headp = onig_node_new_alt(node, NULL);
      if (IS_NULL(*headp)) {
        onig_node_free(node);
        onig_node_free(*top);
        return ONIGERR_MEMORY;
      }

      headp = &(NODE_CDR(*headp));
    }

    if (tok->type != (enum TokenSyms )term)
      goto err;
  }
  else {
    onig_node_free(node);
  err:
    if (term == TK_SUBEXP_CLOSE)
      return ONIGERR_END_PATTERN_WITH_UNMATCHED_PARENTHESIS;
    else
      return ONIGERR_PARSER_BUG;
  }

  env->parse_depth--;
  return r;
}