    void Display::slotAuthError(const QString &message, Auth::Error error) {
        
        qWarning() << "STR" << message;

        if (!m_socket)
            return;

        if (error == Auth::ERROR_AUTHENTICATION)
            emit loginFailed(m_socket);
    }