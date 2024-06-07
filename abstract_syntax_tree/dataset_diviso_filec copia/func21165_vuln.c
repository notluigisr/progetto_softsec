        void do_write()
        {
            
            is_writing = true;
            asio::async_write(
              adaptor_.socket(), buffers_,
              [&](const asio::error_code& ec, std::size_t ) {
                  is_writing = false;
                  res.clear();
                  res_body_copy_.clear();
                  if (!ec)
                  {
                      if (close_connection_)
                      {
                          adaptor_.shutdown_write();
                          adaptor_.close();
                          CROW_LOG_DEBUG << this << "STR";
                          check_destroy();
                      }
                  }
                  else
                  {
                      CROW_LOG_DEBUG << this << "STR";
                      check_destroy();
                  }
              });
        }