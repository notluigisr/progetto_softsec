    bool otherUpdateInFetchPhase() const {
        return _authzManager->_isFetchPhaseBusy;
    }