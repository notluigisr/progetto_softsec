writeDataError(instanceData *pData, cJSON **pReplyRoot, uchar *reqmsg)
{
	char *rendered = NULL;
	cJSON *errRoot;
	cJSON *req;
	cJSON *replyRoot = *pReplyRoot;
	size_t toWrite;
	ssize_t wrRet;
	char errStr[1024];
	DEFiRet;

	if(pData->errorFile == NULL) {
		DBGPRINTF("STR"
		          "STR");
		FINALIZE;
	}

	if(pData->fdErrFile == -1) {
		pData->fdErrFile = open((char*)pData->errorFile,
					O_WRONLY|O_CREAT|O_APPEND|O_LARGEFILE|O_CLOEXEC,
					S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
		if(pData->fdErrFile == -1) {
			rs_strerror_r(errno, errStr, sizeof(errStr));
			DBGPRINTF("STR", errStr);
			ABORT_FINALIZE(RS_RET_ERR);
		}
	}
	if((req=cJSON_CreateObject()) == NULL) ABORT_FINALIZE(RS_RET_ERR);
	cJSON_AddItemToObject(req, "STR", cJSON_CreateString((char*)pData->restURL));
	cJSON_AddItemToObject(req, "STR", cJSON_CreateString((char*)reqmsg));

	if((errRoot=cJSON_CreateObject()) == NULL) ABORT_FINALIZE(RS_RET_ERR);
	cJSON_AddItemToObject(errRoot, "STR", req);
	cJSON_AddItemToObject(errRoot, "STR", replyRoot);
	rendered = cJSON_Print(errRoot);
	
	DBGPRINTF("STR", rendered);
	toWrite = strlen(rendered);
	wrRet = write(pData->fdErrFile, rendered, toWrite);
	if(wrRet != (ssize_t) toWrite) {
		DBGPRINTF("STR",
			  errno, (long long) wrRet);
	}
	free(rendered);
	cJSON_Delete(errRoot);
	*pReplyRoot = NULL; 

finalize_it:
	if(rendered != NULL)
		free(rendered);
	RETiRet;
}