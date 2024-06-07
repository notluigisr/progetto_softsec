    State()
        : remote_encode_complete_(false), remote_decode_complete_(false), local_complete_(false),
          has_1xx_headers_(false), created_filter_chain_(false), is_head_request_(false),
          is_grpc_request_(false), non_100_response_headers_encoded_(false),
          under_on_local_reply_(false), decoder_filter_chain_aborted_(false),
          encoder_filter_chain_aborted_(false), saw_downstream_reset_(false) {}