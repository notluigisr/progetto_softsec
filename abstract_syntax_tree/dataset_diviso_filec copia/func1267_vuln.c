    }

    
    State()
      : m_magic(HTTP_TRANSACT_MAGIC_ALIVE), state_machine(NULL), http_config_param(NULL), force_dns(false),
        updated_server_version(HostDBApplicationInfo::HTTP_VERSION_UNDEFINED), is_revalidation_necessary(false),
        request_will_not_selfloop(false),       
        source(SOURCE_NONE),
        pre_transform_source(SOURCE_NONE),
        req_flavor(REQ_FLAVOR_FWDPROXY),
        pending_work(NULL),
        cdn_saved_next_action(SM_ACTION_UNDEFINED),
        cdn_saved_transact_return_point(NULL),
        cdn_remap_complete(false),
        first_dns_lookup(true),
        parent_params(NULL),
        cache_lookup_result(CACHE_LOOKUP_NONE),
        backdoor_request(false),
        cop_test_page(false),
        next_action(SM_ACTION_UNDEFINED),
        api_next_action(SM_ACTION_UNDEFINED),
        transact_return_point(NULL),
        is_upgrade_request(false),
        post_remap_upgrade_return_point(NULL),
        upgrade_token_wks(NULL),
        is_websocket(false),
        did_upgrade_succeed(false),
        internal_msg_buffer(NULL),
        internal_msg_buffer_type(NULL),
        internal_msg_buffer_size(0),
        internal_msg_buffer_fast_allocator_size(-1),
        internal_msg_buffer_index(0),
        icp_lookup_success(false),
        scheme(-1),
        next_hop_scheme(scheme),
        orig_scheme(scheme),
        method(0),
        cause_of_death_errno(-UNKNOWN_INTERNAL_ERROR),
        client_request_time(UNDEFINED_TIME),
        request_sent_time(UNDEFINED_TIME),
        response_received_time(UNDEFINED_TIME),
        plugin_set_expire_time(UNDEFINED_TIME),
        state_machine_id(0),
        first_stats(),
        current_stats(NULL),
        negative_caching(false),
        srv_lookup(false),
        www_auth_content(CACHE_AUTH_NONE),
        client_connection_enabled(true),
        acl_filtering_performed(false),
        fp_tsremap_os_response(NULL),
        remap_plugin_instance(0),
        http_return_code(HTTP_STATUS_NONE),
        api_txn_active_timeout_value(-1),
        api_txn_connect_timeout_value(-1),
        api_txn_dns_timeout_value(-1),
        api_txn_no_activity_timeout_value(-1),
        cache_req_hdr_heap_handle(NULL),
        cache_resp_hdr_heap_handle(NULL),
        api_release_server_session(false),
        api_cleanup_cache_read(false),
        api_server_response_no_store(false),
        api_server_response_ignore(false),
        api_http_sm_shutdown(false),
        api_modifiable_cached_resp(false),
        api_server_request_body_set(false),
        api_req_cacheable(false),
        api_resp_cacheable(false),
        api_server_addr_set(false),
        api_update_cached_object(UPDATE_CACHED_OBJECT_NONE),
        api_lock_url(LOCK_URL_FIRST),
        saved_update_next_action(SM_ACTION_UNDEFINED),
        saved_update_cache_action(CACHE_DO_UNDEFINED),
        stale_icp_lookup(false),
        url_map(),
        pCongestionEntry(NULL),
        congest_saved_next_action(SM_ACTION_UNDEFINED),
        congestion_control_crat(0),
        congestion_congested_or_failed(0),
        congestion_connection_opened(0),
        reverse_proxy(false), url_remap_success(false), remap_redirect(NULL), filter_mask(0), already_downgraded(false),
        pristine_url(),
        api_skip_all_remapping(false),
        range_setup(RANGE_NONE),
        num_range_fields(0),
        range_output_cl(0),
        ranges(NULL),
        txn_conf(NULL),
        transparent_passthrough(false),
        range_in_cache(false)
    {
      int i;
      char *via_ptr = via_string;

      for (i = 0; i < MAX_VIA_INDICES; i++) {
        *via_ptr++ = ' ';
      }

      via_string[VIA_CLIENT] = VIA_CLIENT_STRING;
      via_string[VIA_CACHE] = VIA_CACHE_STRING;
      via_string[VIA_SERVER] = VIA_SERVER_STRING;
      via_string[VIA_CACHE_FILL] = VIA_CACHE_FILL_STRING;
      via_string[VIA_PROXY] = VIA_PROXY_STRING;
      via_string[VIA_ERROR] = VIA_ERROR_STRING;
      via_string[VIA_ERROR_TYPE] = VIA_ERROR_NO_ERROR;
      via_string[VIA_DETAIL_SEPARATOR] = VIA_DETAIL_SEPARATOR_STRING;
      via_string[VIA_DETAIL_TUNNEL_DESCRIPTOR] = VIA_DETAIL_TUNNEL_DESCRIPTOR_STRING;
      via_string[VIA_DETAIL_CACHE_DESCRIPTOR] = VIA_DETAIL_CACHE_DESCRIPTOR_STRING;
      via_string[VIA_DETAIL_ICP_DESCRIPTOR] = VIA_DETAIL_ICP_DESCRIPTOR_STRING;
      via_string[VIA_DETAIL_PP_DESCRIPTOR] = VIA_DETAIL_PP_DESCRIPTOR_STRING;
      via_string[VIA_DETAIL_SERVER_DESCRIPTOR] = VIA_DETAIL_SERVER_DESCRIPTOR_STRING;
      via_string[MAX_VIA_INDICES] = '\0';
