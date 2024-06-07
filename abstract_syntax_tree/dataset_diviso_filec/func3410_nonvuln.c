    bool PamData::insertPrompt(const struct pam_message* msg, bool predict) {
        Prompt &p = findPrompt(msg);

        
        if (p.valid()) {
            
            if (m_sent)
                return false;
            
            p.message = QString::fromLocal8Bit(msg->msg);
            return true;
        }
        
        else if (m_currentRequest.prompts.length() != 0) {
            
            if (m_sent) {
                m_currentRequest.clear();
                m_sent = false;
            }
        }

        
        if (predict) {
            AuthPrompt::Type type = detectPrompt(msg);
            switch (type) {
                case AuthPrompt::LOGIN_USER:
                    m_currentRequest = Request(loginRequest);
                    return true;
                case AuthPrompt::CHANGE_CURRENT:
                    m_currentRequest = Request(changePassRequest);
                    return true;
                case AuthPrompt::CHANGE_NEW:
                    m_currentRequest = Request(changePassNoOldRequest);
                    return true;
                default:
                    break;
            }
        }

        
        m_currentRequest.prompts.append(Prompt(detectPrompt(msg), QString::fromLocal8Bit(msg->msg), msg->msg_style == PAM_PROMPT_ECHO_OFF));

        return true;
    }