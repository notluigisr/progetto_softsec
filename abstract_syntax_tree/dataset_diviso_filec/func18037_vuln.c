CryptRsaDecrypt(
		TPM2B               *dOut,          
		TPM2B               *cIn,           
		OBJECT              *key,           
		TPMT_RSA_DECRYPT    *scheme,        
		const TPM2B         *label          
		)
{
    TPM_RC                 retVal;
    
    pAssert(cIn != NULL && dOut != NULL && key != NULL);
    
    if(cIn->size != key->publicArea.unique.rsa.t.size)
	ERROR_RETURN(TPM_RC_SIZE);
    TEST(scheme->scheme);
    
    
    retVal = RSADP(cIn, key);
    if(retVal == TPM_RC_SUCCESS)
	{
	    
	    switch(scheme->scheme)
		{
		  case ALG_NULL_VALUE:
		    if(dOut->size < cIn->size)
			return TPM_RC_VALUE;
		    MemoryCopy2B(dOut, cIn, dOut->size);
		    break;
		  case ALG_RSAES_VALUE:
		    retVal = RSAES_Decode(dOut, cIn);
		    break;
		  case ALG_OAEP_VALUE:
		    retVal = OaepDecode(dOut, scheme->details.oaep.hashAlg, label, cIn);
		    break;
		  default:
		    retVal = TPM_RC_SCHEME;
		    break;
		}
	}
 Exit:
    return retVal;
}