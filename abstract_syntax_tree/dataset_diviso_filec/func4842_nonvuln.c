(AuthorizationManager* authzManager)->std::unique_ptr<AuthorizationSession> {
    return std::make_unique<AuthorizationSessionImpl>(
        AuthzSessionExternalState::create(authzManager),
        AuthorizationSessionImpl::InstallMockForTestingOrAuthImpl{});
}