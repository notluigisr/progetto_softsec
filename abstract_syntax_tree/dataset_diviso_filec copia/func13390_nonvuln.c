static NTSTATUS add_socket(struct task_server *task,
			   struct loadparm_context *lp_ctx,
			   const struct model_ops *model_ops,
			   const char *address, struct ldapsrv_service *ldap_service)
{
	uint16_t port = 389;
	NTSTATUS status;
	struct ldb_context *ldb;

	status = stream_setup_socket(task, task->event_ctx, lp_ctx,
				     model_ops, &ldap_stream_nonpriv_ops,
				     "STR", address, &port,
				     lpcfg_socket_options(lp_ctx),
				     ldap_service, task->process_context);
	if (!NT_STATUS_IS_OK(status)) {
		DBG_ERR("STR",
			address, port, nt_errstr(status));
		return status;
	}

	if (tstream_tls_params_enabled(ldap_service->tls_params)) {
		
		port = 636;
		status = stream_setup_socket(task, task->event_ctx, lp_ctx,
					     model_ops,
					     &ldap_stream_nonpriv_ops,
					     "STR", address, &port,
					     lpcfg_socket_options(lp_ctx),
					     ldap_service,
					     task->process_context);
		if (!NT_STATUS_IS_OK(status)) {
			DBG_ERR("STR",
				address, port, nt_errstr(status));
			return status;
		}
	}

	
	ldb = samdb_connect(ldap_service,
			    ldap_service->task->event_ctx,
			    lp_ctx,
			    system_session(lp_ctx),
			    NULL,
			    0);
	if (!ldb) {
		return NT_STATUS_INTERNAL_DB_CORRUPTION;
	}

	if (samdb_is_gc(ldb)) {
		port = 3268;
		status = stream_setup_socket(task, task->event_ctx, lp_ctx,
					     model_ops,
					     &ldap_stream_nonpriv_ops,
					     "STR", address, &port,
					     lpcfg_socket_options(lp_ctx),
					     ldap_service,
					     task->process_context);
		if (!NT_STATUS_IS_OK(status)) {
			DBG_ERR("STR",
				address, port, nt_errstr(status));
			return status;
		}
		if (tstream_tls_params_enabled(ldap_service->tls_params)) {
			
			port = 3269;
			status = stream_setup_socket(task, task->event_ctx, lp_ctx,
						     model_ops,
						     &ldap_stream_nonpriv_ops,
						     "STR", address, &port,
						     lpcfg_socket_options(lp_ctx),
						     ldap_service,
						     task->process_context);
			if (!NT_STATUS_IS_OK(status)) {
				DBG_ERR("STR",
					address, port, nt_errstr(status));
				return status;
			}
		}
	}

	
	talloc_unlink(ldap_service, ldb);

	return NT_STATUS_OK;
}