        void do_write_general()
        {
            if (res.body.length() < res_stream_threshold_)
            {
                res_body_copy_.swap(res.body);
                buffers_.emplace_back(res_body_copy_.data(), res_body_copy_.size());

                do_write();

                if (need_to_start_read_after_complete_)
                {
                    need_to_start_read_after_complete_ = false;
                    start_deadline();
                    do_read();
                }
            }
            else
            {
                is_writing = true;
                asio::write(adaptor_.socket(), buffers_); 
                cancel_deadline_timer();
                if (res.body.length() > 0)
                {
                    std::string buf;
                    std::vector<asio::const_buffer> buffers;

                    while (res.body.length() > 16384)
                    {
                        
                        buf = res.body.substr(0, 16384);
                        res.body = res.body.substr(16384);
                        buffers.clear();
                        buffers.push_back(asio::buffer(buf));
                        do_write_sync(buffers);
                    }
                    
                    
                    buf = res.body;
                    res.body.clear();

                    buffers.clear();
                    buffers.push_back(asio::buffer(buf));
                    do_write_sync(buffers);
                }
                is_writing = false;
                if (close_connection_)
                {
                    adaptor_.shutdown_readwrite();
                    adaptor_.close();
                    CROW_LOG_DEBUG << this << "STR";
                    check_destroy();
                }

                res.end();
                res.clear();
                buffers_.clear();
            }
        }