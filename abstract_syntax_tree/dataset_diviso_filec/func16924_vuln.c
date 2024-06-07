static rsRetVal qAddDirect(qqueue_t *pThis, void* pUsr)
{
	batch_t singleBatch;
	batch_obj_t batchObj;
	DEFiRet;

	
	ASSERT(pThis != NULL);

	
	
	memset(&batchObj, 0, sizeof(batch_obj_t));
	memset(&singleBatch, 0, sizeof(batch_t));
	batchObj.state = BATCH_STATE_RDY;
	batchObj.pUsrp = (obj_t*) pUsr;
	batchObj.bFilterOK = 1;
	singleBatch.nElem = 1; 
	singleBatch.pElem = &batchObj;
	iRet = pThis->pConsumer(pThis->pUsr, &singleBatch, &pThis->bShutdownImmediate);
	objDestruct(pUsr);

	RETiRet;
}