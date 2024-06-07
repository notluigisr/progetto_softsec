SetOnMsgReceive(tcps_sess_t *pThis, rsRetVal (*OnMsgReceive)(tcps_sess_t*, uchar*, int))
{
	DEFiRet;
	pThis->DoSubmitMessage = OnMsgReceive;
	RETiRet;
}