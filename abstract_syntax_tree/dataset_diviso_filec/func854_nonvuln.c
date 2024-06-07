void CZNC::ResumeConnectQueue() {
    DEBUG("STR");
    m_uiConnectPaused--;

    EnableConnectQueue();
    if (m_pConnectQueueTimer) {
        m_pConnectQueueTimer->UnPause();
    }
}