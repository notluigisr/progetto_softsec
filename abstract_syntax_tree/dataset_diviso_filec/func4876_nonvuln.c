void auth_request_policy_check_callback(int result, void *context)
{
	struct auth_policy_check_ctx *ctx = context;

	ctx->request->policy_processed = TRUE;
	
	ctx->request->policy_penalty += result < 0 ? 0 : result;

	if (ctx->request->set->policy_log_only && result != 0) {
		auth_request_policy_penalty_finish(context);
		return;
	}
	if (result < 0) {
		
		auth_request_fail(ctx->request);
	} else if (ctx->type != AUTH_POLICY_CHECK_TYPE_SUCCESS && result > 0 &&
		   !ctx->request->fields.no_penalty) {
		ctx->request->to_penalty = timeout_add(result * 1000,
				auth_request_policy_penalty_finish,
				context);
	} else {
		auth_request_policy_penalty_finish(context);
	}
}