CryptSymKeyValidate(
		    TPMT_SYM_DEF_OBJECT *symDef,
		    TPM2B_SYM_KEY       *key
		    )
{
    if(key->t.size != BITS_TO_BYTES(symDef->keyBits.sym))
	return TPM_RCS_KEY_SIZE;
#if ALG_TDES
    if(symDef->algorithm == TPM_ALG_TDES && !CryptDesValidateKey(key))
	return TPM_RCS_KEY;
#endif 
    return TPM_RC_SUCCESS;
}