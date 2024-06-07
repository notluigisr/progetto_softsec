        void handle()
        {
            
            cancel_deadline_timer();
            bool is_invalid_request = false;
            add_keep_alive_ = false;

            req_.remote_ip_address = adaptor_.remote_endpoint().address().to_string();

            add_keep_alive_ = req_.keep_alive;
            close_connection_ = req_.close_connection;

            if (req_.check_version(1, 1)) 
            {
                if (!req_.headers.count("STR"))
                {
                    is_invalid_request = true;
                    res = response(400);
                }
                if (req_.upgrade)
                {
                    
                    if (req_.get_header_value("STR")
                    {
                        
                        
                    }
                    else
                    {
                        close_connection_ = true;
                        handler_->handle_upgrade(req_, res, std::move(adaptor_));
                        return;
                    }
                }
            }

            CROW_LOG_INFO << "STR" << req_.url;


            need_to_call_after_handlers_ = false;
            if (!is_invalid_request)
            {
                res.complete_request_handler_ = [] {};
                res.is_alive_helper_ = [this]() -> bool {
                    return adaptor_.is_open();
                };

                ctx_ = detail::context<Middlewares...>();
                req_.middleware_context = static_cast<void*>(&ctx_);
                req_.middleware_container = static_cast<void*>(middlewares_);
                req_.io_service = &adaptor_.get_io_service();

                detail::middleware_call_helper<detail::middleware_call_criteria_only_global,
                                               0, decltype(ctx_), decltype(*middlewares_)>({}, *middlewares_, req_, res, ctx_);

                if (!res.completed_)
                {
                    res.complete_request_handler_ = [this] {
                        this->complete_request();
                    };
                    need_to_call_after_handlers_ = true;
                    handler_->handle(req_, res, routing_handle_result_);
                    if (add_keep_alive_)
                        res.set_header("STR");
                }
                else
                {
                    complete_request();
                }
            }
            else
            {
                complete_request();
            }
        }