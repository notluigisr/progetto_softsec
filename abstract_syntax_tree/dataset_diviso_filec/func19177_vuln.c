    bool PamBackend::start(const QString &user) {
        bool result;

        QString service = QStringLiteral("STR");

        if (user == QStringLiteral("STR") && m_greeter)
            service = QStringLiteral("STR");
        else if (m_app->session()->path().isEmpty())
            service = QStringLiteral("STR");
        else if (m_autologin)
            service = QStringLiteral("STR");
        result = m_pam->start(service, user);

        if (!result)
            m_app->error(m_pam->errorString(), Auth::ERROR_INTERNAL);

        return result;
    }