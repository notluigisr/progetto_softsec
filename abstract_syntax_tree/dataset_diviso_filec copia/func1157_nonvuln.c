set_quantifier(Node* qnode, Node* target, int group, ScanEnv* env)
{
  QtfrNode* qn;

  qn = NQTFR(qnode);
  if (qn->lower == 1 && qn->upper == 1) {
    return 1;
  }

  switch (NTYPE(target)) {
  case NT_STR:
    if (! group) {
      StrNode* sn = NSTR(target);
      if (str_node_can_be_split(sn, env->enc)) {
	Node* n = str_node_split_last_char(sn, env->enc);
	if (IS_NOT_NULL(n)) {
	  qn->target = n;
	  return 2;
	}
      }
    }
    break;

  case NT_QTFR:
    { 
      
      QtfrNode* qnt   = NQTFR(target);
      int nestq_num   = popular_quantifier_num(qn);
      int targetq_num = popular_quantifier_num(qnt);

#ifdef USE_WARNING_REDUNDANT_NESTED_REPEAT_OPERATOR
      if (!IS_QUANTIFIER_BY_NUMBER(qn) && !IS_QUANTIFIER_BY_NUMBER(qnt) &&
	  IS_SYNTAX_BV(env->syntax, ONIG_SYN_WARN_REDUNDANT_NESTED_REPEAT)) {
        UChar buf[WARN_BUFSIZE];

        switch(ReduceTypeTable[targetq_num][nestq_num]) {
        case RQ_ASIS:
          break;

        case RQ_DEL:
          if (onig_verb_warn != onig_null_warn) {
            onig_snprintf_with_pattern(buf, WARN_BUFSIZE, env->enc,
                                 env->pattern, env->pattern_end,
                                 (UChar* )"STR");
            (*onig_verb_warn)((char* )buf);
          }
          goto warn_exit;
          break;

        default:
          if (onig_verb_warn != onig_null_warn) {
            onig_snprintf_with_pattern(buf, WARN_BUFSIZE, env->enc,
                                       env->pattern, env->pattern_end,
            (UChar* )"STR",
            PopularQStr[targetq_num], PopularQStr[nestq_num],
            ReduceQStr[ReduceTypeTable[targetq_num][nestq_num]]);
            (*onig_verb_warn)((char* )buf);
          }
          goto warn_exit;
          break;
        }
      }

    warn_exit:
#endif
      if (targetq_num >= 0) {
	if (nestq_num >= 0) {
	  onig_reduce_nested_quantifier(qnode, target);
	  goto q_exit;
	}
	else if (targetq_num == 1 || targetq_num == 2) { 
	  
	  if (! IS_REPEAT_INFINITE(qn->upper) && qn->upper > 1 && qn->greedy) {
	    qn->upper = (qn->lower == 0 ? 1 : qn->lower);
	  }
	}
      }
    }
    break;

  default:
    break;
  }

  qn->target = target;
 q_exit:
  return 0;
}