rsCStrExtendBuf(cstr_t *pThis, size_t iMinNeeded)
{
	uchar *pNewBuf;
	unsigned short iNewSize;
	DEFiRet;

	
	if(iMinNeeded > RS_STRINGBUF_ALLOC_INCREMENT) {
		
		iNewSize = (iMinNeeded / RS_STRINGBUF_ALLOC_INCREMENT + 1) * RS_STRINGBUF_ALLOC_INCREMENT;
	} else {
		iNewSize = pThis->iBufSize + RS_STRINGBUF_ALLOC_INCREMENT;
	}
	iNewSize += pThis->iBufSize; 

	
	CHKmalloc(pNewBuf = (uchar*) realloc(pThis->pBuf, iNewSize * sizeof(uchar)));
	pThis->iBufSize = iNewSize;
	pThis->pBuf = pNewBuf;

finalize_it:
	RETiRet;
}