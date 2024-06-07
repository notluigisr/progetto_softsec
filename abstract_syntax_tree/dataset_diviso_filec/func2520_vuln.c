NO_INLINE JsVar *__jspeAssignmentExpression(JsVar *lhs) {
  if (lex->tk=='=' || lex->tk==LEX_PLUSEQUAL || lex->tk==LEX_MINUSEQUAL ||
      lex->tk==LEX_MULEQUAL || lex->tk==LEX_DIVEQUAL || lex->tk==LEX_MODEQUAL ||
      lex->tk==LEX_ANDEQUAL || lex->tk==LEX_OREQUAL ||
      lex->tk==LEX_XOREQUAL || lex->tk==LEX_RSHIFTEQUAL ||
      lex->tk==LEX_LSHIFTEQUAL || lex->tk==LEX_RSHIFTUNSIGNEDEQUAL) {
    JsVar *rhs;

    int op = lex->tk;
    JSP_ASSERT_MATCH(op);
    rhs = jspeAssignmentExpression();
    rhs = jsvSkipNameAndUnLock(rhs); 

    if (JSP_SHOULD_EXECUTE && lhs) {
      if (op=='=') {
        
        if (!jsvGetRefs(lhs) && jsvIsName(lhs)) {
          if (!jsvIsArrayBufferName(lhs) && !jsvIsNewChild(lhs))
            jsvAddName(execInfo.root, lhs);
        }
        jspReplaceWith(lhs, rhs);
      } else {
        if (op==LEX_PLUSEQUAL) op='+';
        else if (op==LEX_MINUSEQUAL) op='-';
        else if (op==LEX_MULEQUAL) op='*';
        else if (op==LEX_DIVEQUAL) op='/';
        else if (op==LEX_MODEQUAL) op='%';
        else if (op==LEX_ANDEQUAL) op='&';
        else if (op==LEX_OREQUAL) op='|';
        else if (op==LEX_XOREQUAL) op='^';
        else if (op==LEX_RSHIFTEQUAL) op=LEX_RSHIFT;
        else if (op==LEX_LSHIFTEQUAL) op=LEX_LSHIFT;
        else if (op==LEX_RSHIFTUNSIGNEDEQUAL) op=LEX_RSHIFTUNSIGNED;
        if (op=='+' && jsvIsName(lhs)) {
          JsVar *currentValue = jsvSkipName(lhs);
          if (jsvIsString(currentValue) && !jsvIsFlatString(currentValue) && jsvGetRefs(currentValue)==1 && rhs!=currentValue) {
            
            JsVar *str = jsvAsString(rhs, false);
            jsvAppendStringVarComplete(currentValue, str);
            jsvUnLock(str);
            op = 0;
          }
          jsvUnLock(currentValue);
        }
        if (op) {
          
          JsVar *res = jsvMathsOpSkipNames(lhs,rhs,op);
          jspReplaceWith(lhs, res);
          jsvUnLock(res);
        }
      }
    }
    jsvUnLock(rhs);
  }
  return lhs;
}