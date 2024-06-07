HttpTransact::handle_parent_died(State* s)
{
  ink_assert(s->parent_result.r == PARENT_FAIL);

  build_error_response(s, HTTP_STATUS_BAD_GATEWAY, "STR", NULL);
  TRANSACT_RETURN(SM_ACTION_SEND_ERROR_CACHE_NOOP, NULL);
}