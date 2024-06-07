invoke_NPN_GetIntIdentifier(int32_t intid)
{
  npw_return_val_if_fail(rpc_method_invoke_possible(g_rpc_connection), NULL);

  int error = rpc_method_invoke(g_rpc_connection,
								RPC_METHOD_NPN_GET_INT_IDENTIFIER,
								RPC_TYPE_INT32, intid,
								RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("STR", error);
	return NULL;
  }

  NPIdentifier ident;
  error = rpc_method_wait_for_reply(g_rpc_connection,
									RPC_TYPE_NP_IDENTIFIER, &ident,
									RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("STR", error);
	return NULL;
  }

  return ident;
}