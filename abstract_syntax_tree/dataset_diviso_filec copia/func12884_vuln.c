batchInit(batch_t *pBatch, int maxElem) {
	DEFiRet;
	pBatch->maxElem = maxElem;
	CHKmalloc(pBatch->pElem = calloc((size_t)maxElem, sizeof(batch_obj_t)));
	
finalize_it:
	RETiRet;
}