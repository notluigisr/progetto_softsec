int TS_RESP_CTX_set_accuracy(TS_RESP_CTX *ctx, 
			     int secs, int millis, int micros)
	{

	TS_RESP_CTX_accuracy_free(ctx);
	if (secs && (!(ctx->seconds = ASN1_INTEGER_new())
		     || !ASN1_INTEGER_set(ctx->seconds, secs)))
		goto err;
	if (millis && (!(ctx->millis = ASN1_INTEGER_new())
		       || !ASN1_INTEGER_set(ctx->millis, millis)))
		goto err;
	if (micros && (!(ctx->micros = ASN1_INTEGER_new())
		       || !ASN1_INTEGER_set(ctx->micros, micros)))
		goto err;

	return 1;
 err:
	TS_RESP_CTX_accuracy_free(ctx);
	TSerr(TS_F_TS_RESP_CTX_SET_ACCURACY, ERR_R_MALLOC_FAILURE);
	return 0;
	}