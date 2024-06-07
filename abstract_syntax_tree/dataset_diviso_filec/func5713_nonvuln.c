NO_INLINE bool jspeFunctionArguments(JsVar *funcVar) {
  JSP_MATCH('(');
  while (lex->tk!=')') {
    if (funcVar) {
      char buf[JSLEX_MAX_TOKEN_LENGTH+1];
      buf[0] = '\xFF';
      strcpy(&buf[1], jslGetTokenValueAsString(lex));
      JsVar *param = jsvAddNamedChild(funcVar, 0, buf);
      if (!param) { 
        jspSetError(false);
        return false;
      }
      jsvMakeFunctionParameter(param); 
      jsvUnLock(param);
    }
    JSP_MATCH(LEX_ID);
    if (lex->tk!=')') JSP_MATCH(',');
  }
  JSP_MATCH(')');
  return true;
}