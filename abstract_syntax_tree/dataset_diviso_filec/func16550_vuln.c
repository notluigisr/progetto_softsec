        void stop()
        {
#ifdef CROW_ENABLE_SSL
            if (ssl_used_)
            {
                if (ssl_server_) { ssl_server_->stop(); }
            }
            else
#endif
            {
                std::vector<crow::websocket::connection*> websockets_to_close = websockets_;
                for (auto websocket : websockets_to_close)
                {
                    CROW_LOG_INFO << "STR" << websocket;
                    websocket->close("STR");
                }
                if (server_) { server_->stop(); }
            }
        }