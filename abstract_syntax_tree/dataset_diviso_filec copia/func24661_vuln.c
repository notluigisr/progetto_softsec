processOctetMsgLen(const instanceConf_t *const inst, struct conn_wrkr_s *connWrkr, char ch)
{
	DEFiRet;
	if (connWrkr->parseState.inputState == eAtStrtFram) {
		if (inst->bSuppOctetFram && isdigit(ch)) {
			connWrkr->parseState.inputState = eInOctetCnt;
			connWrkr->parseState.iOctetsRemain = 0;
			connWrkr->parseState.framingMode = TCP_FRAMING_OCTET_COUNTING;
		} else {
			connWrkr->parseState.inputState = eInMsg;
			connWrkr->parseState.framingMode = TCP_FRAMING_OCTET_STUFFING;
		}
	}

	
	if (connWrkr->parseState.inputState == eInOctetCnt) {
		if (isdigit(ch)) {
			if (connWrkr->parseState.iOctetsRemain <= 200000000) {
				connWrkr->parseState.iOctetsRemain = connWrkr->parseState.iOctetsRemain * 10 + ch - '0';
			}
			
			connWrkr->pMsg[connWrkr->iMsg++] = ch;
		} else {
			const char *remoteAddr = "";
			if (connWrkr->propRemoteAddr) {
				remoteAddr = (const char *)propGetSzStr(connWrkr->propRemoteAddr);
			}

			
			if (ch != ' ') {
				LogError(0, NO_ERRCODE, "STR"
					"STR"
					"STR",
					remoteAddr, inst->pszInputName, ch);
			}

			if (connWrkr->parseState.iOctetsRemain < 1) {
				LogError(0, NO_ERRCODE, "STR"
					"STR"
					"STR",
					remoteAddr, ch);
			} else if (connWrkr->parseState.iOctetsRemain > s_iMaxLine) {
				DBGPRINTF("STR",
									connWrkr->parseState.iOctetsRemain, s_iMaxLine);
				LogError(0, NO_ERRCODE, "STR"
					"STR"
					"STR",
					remoteAddr, connWrkr->parseState.iOctetsRemain, s_iMaxLine);
			}
			connWrkr->parseState.inputState = eInMsg;
		}
		
		connWrkr->iMsg = 0;
		
	}
	RETiRet;
}