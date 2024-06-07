static int muscle_set_security_env(sc_card_t *card,
				 const sc_security_env_t *env,
				 int se_num)
{
	muscle_private_t* priv = MUSCLE_DATA(card);

	if (env->operation != SC_SEC_OPERATION_SIGN &&
	    env->operation != SC_SEC_OPERATION_DECIPHER) {
		sc_debug(card->ctx, SC_LOG_DEBUG_NORMAL, "STR");
		return SC_ERROR_NOT_SUPPORTED;
	}
	if (env->algorithm != SC_ALGORITHM_RSA) {
		sc_debug(card->ctx, SC_LOG_DEBUG_NORMAL, "STR");
		return SC_ERROR_NOT_SUPPORTED;
	}
	
	if ((env->algorithm_flags & SC_ALGORITHM_RSA_PADS) ||
	    (env->algorithm_flags & SC_ALGORITHM_RSA_HASHES)) {
		sc_debug(card->ctx, SC_LOG_DEBUG_NORMAL, "STR");
		return SC_ERROR_NOT_SUPPORTED;
	}
	if (env->flags & SC_SEC_ENV_KEY_REF_PRESENT) {
		if (env->key_ref_len != 1 ||
		    (env->key_ref[0] > 0x0F)) {
			sc_debug(card->ctx, SC_LOG_DEBUG_NORMAL, "STR");
			return SC_ERROR_NOT_SUPPORTED;
		}
		priv->rsa_key_ref = env->key_ref[0];
	}
	if (env->flags & SC_SEC_ENV_ALG_REF_PRESENT) {
		sc_debug(card->ctx, SC_LOG_DEBUG_NORMAL, "STR");
		return SC_ERROR_NOT_SUPPORTED;
	}
	
	priv->env = *env;
	return 0;
}