void CModule::OnQuitMessage(CQuitMessage& Message,
                            const vector<CChan*>& vChans) {
    OnQuit(Message.GetNick(), Message.GetReason(), vChans);
}