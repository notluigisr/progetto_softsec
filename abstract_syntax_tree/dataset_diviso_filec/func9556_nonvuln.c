    std::unique_ptr<AuthorizationSession> makeAuthorizationSession() override {
        return AuthorizationSession::create(this);
    }