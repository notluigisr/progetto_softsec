proto_register_kafka_expert_module(const int proto) {
    expert_module_t* expert_kafka;
    static ei_register_info ei[] = {
            { &ei_kafka_request_missing,
                    { "STR", EXPFILL }},
            { &ei_kafka_unknown_api_key,
                    { "STR", EXPFILL }},
            { &ei_kafka_unsupported_api_version,
                    { "STR", EXPFILL }},
            { &ei_kafka_bad_string_length,
                    { "STR", EXPFILL }},
            { &ei_kafka_bad_bytes_length,
                    { "STR", EXPFILL }},
            { &ei_kafka_bad_array_length,
                    { "STR", EXPFILL }},
            { &ei_kafka_bad_record_length,
                    { "STR", EXPFILL }},
            { &ei_kafka_bad_varint,
                    { "STR", EXPFILL }},
            { &ei_kafka_bad_message_set_length,
                    { "STR", EXPFILL }},
            { &ei_kafka_unknown_message_magic,
                    { "STR", EXPFILL }},
            { &ei_kafka_pdu_length_mismatch,
                    { "STR", EXPFILL }},
    };
    expert_kafka = expert_register_protocol(proto);
    expert_register_field_array(expert_kafka, ei, array_length(ei));
}