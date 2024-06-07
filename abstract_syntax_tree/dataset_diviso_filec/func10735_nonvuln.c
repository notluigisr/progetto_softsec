static void jpake_send_step2(BIO *bconn, JPAKE_CTX *ctx)
	{
	JPAKE_STEP2 s2;

	JPAKE_STEP2_init(&s2);
	JPAKE_STEP2_generate(&s2, ctx);
	jpake_send_part(bconn, &s2);
	(void)BIO_flush(bconn);
	JPAKE_STEP2_release(&s2);
	}