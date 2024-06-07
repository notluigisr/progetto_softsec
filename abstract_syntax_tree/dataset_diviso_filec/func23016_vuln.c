        void start()
        {
            adaptor_.start([this](const asio::error_code& ec) {
                if (!ec)
                {
                    start_deadline();

                    do_read();
                }
                else
                {
                    CROW_LOG_ERROR << "STR" << ec.message();
                    check_destroy();
                }
            });
        }