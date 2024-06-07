  FilterManager(FilterManagerCallbacks& filter_manager_callbacks, Event::Dispatcher& dispatcher,
                const Network::Connection& connection, uint64_t stream_id,
                Buffer::BufferMemoryAccountSharedPtr account, bool proxy_100_continue,
                uint32_t buffer_limit, FilterChainFactory& filter_chain_factory,
                const LocalReply::LocalReply& local_reply, Http::Protocol protocol,
                TimeSource& time_source, StreamInfo::FilterStateSharedPtr parent_filter_state,
                StreamInfo::FilterState::LifeSpan filter_state_life_span)
      : filter_manager_callbacks_(filter_manager_callbacks), dispatcher_(dispatcher),
        connection_(connection), stream_id_(stream_id), account_(std::move(account)),
        proxy_100_continue_(proxy_100_continue), buffer_limit_(buffer_limit),
        filter_chain_factory_(filter_chain_factory), local_reply_(local_reply),
        stream_info_(protocol, time_source, connection.connectionInfoProviderSharedPtr(),
                     parent_filter_state, filter_state_life_span) {}