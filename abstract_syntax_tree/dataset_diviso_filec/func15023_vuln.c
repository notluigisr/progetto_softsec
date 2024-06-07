static int mod_detach (void *arg)
{
	eap_pwd_t *inst;

	inst = (eap_pwd_t *) arg;

	if (inst->bnctx) BN_CTX_free(inst->bnctx);

	return 0;
}