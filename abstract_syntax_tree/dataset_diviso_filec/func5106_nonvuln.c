    void setUp() override {
        auto localExternalState = stdx::make_unique<AuthzManagerExternalStateMock>();
        externalState = localExternalState.get();
        externalState->setAuthzVersion(AuthorizationManager::schemaVersion26Final);
        authzManager = stdx::make_unique<AuthorizationManager>(std::move(localExternalState));
        externalState->setAuthorizationManager(authzManager.get());
        authzManager->setAuthEnabled(true);
    }