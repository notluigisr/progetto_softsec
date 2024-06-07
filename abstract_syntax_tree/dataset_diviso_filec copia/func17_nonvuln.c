AllocateSequenceSlot(
		     TPM_HANDLE      *newHandle,     
		     TPM2B_AUTH      *auth           
		     )
{
    HASH_OBJECT      *object = (HASH_OBJECT *)ObjectAllocateSlot(newHandle);
    
    
    
    
    cAssert(offsetof(HASH_OBJECT, auth) == offsetof(OBJECT, publicArea.authPolicy));
    if(object != NULL)
	{
	    
	    
	    MemorySet(&object->objectAttributes, 0, sizeof(TPMA_OBJECT));
	    
	    object->type = TPM_ALG_NULL;
	    
	    object->nameAlg = TPM_ALG_NULL;
	    
	    
	    object->attributes.temporary = SET;
	    
	    SET_ATTRIBUTE(object->objectAttributes, TPMA_OBJECT, noDA);
	    
	    if(auth != NULL)
		object->auth = *auth;
	    else
		object->auth.t.size = 0;
	}
    return object;
}