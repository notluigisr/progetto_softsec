processDataRcvd_regexFraming(ptcpsess_t *const __restrict__ pThis,
	char **const buff,
	struct syslogTime *const stTime,
	const time_t ttGenTime,
	multi_submit_t *const pMultiSub,
	unsigned *const __restrict__ pnMsgs)
{
	DEFiRet;
	const instanceConf_t *const inst = pThis->pLstn->pSrv->inst;
	assert(inst->startRegex != NULL);
	const char c = **buff;

	pThis->pMsg[pThis->iMsg++] = c;
	pThis->pMsg[pThis->iMsg] = '\0';

	if(pThis->iMsg == 2*iMaxLine) {
		LogError(0, RS_RET_OVERSIZE_MSG, "STR"
			"STR"
			"STR", pThis->iMsg+1);
		doSubmitMsg(pThis, stTime, ttGenTime, pMultiSub);
		++(*pnMsgs);
		pThis->iMsg = 0;
		pThis->iCurrLine = 1;
	}


	if(c == '\n') {
		pThis->iCurrLine = pThis->iMsg;
	} else {
		const int isMatch = !regexec(&inst->start_preg, (char*)pThis->pMsg+pThis->iCurrLine, 0, NULL, 0);
		if(isMatch) {
			DBGPRINTF("STR", pThis->iCurrLine, pThis->pMsg);
			strcpy((char*)pThis->pMsg_save, (char*) pThis->pMsg+pThis->iCurrLine);
			pThis->iMsg = pThis->iCurrLine - 1;

			doSubmitMsg(pThis, stTime, ttGenTime, pMultiSub);
			++(*pnMsgs);

			strcpy((char*)pThis->pMsg, (char*)pThis->pMsg_save);
			pThis->iMsg = ustrlen(pThis->pMsg_save);
			pThis->iCurrLine = 1;
		}
	}

	RETiRet;
}