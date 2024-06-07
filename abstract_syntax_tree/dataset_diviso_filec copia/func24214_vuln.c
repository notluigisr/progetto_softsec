proto_register_blip(void)
{
	static hf_register_info hf[] = {
	{ &hf_blip_message_number,
		{ "STR", FT_UINT64, BASE_DEC,
			NULL, 0x0, NULL, HFILL }
	},
	{ &hf_blip_frame_flags,
		{ "STR", FT_UINT8, BASE_HEX | BASE_EXT_STRING,
			&flag_combos_ext, 0x0, NULL, HFILL }
	},
	{ &hf_blip_properties_length,
		{ "STR", FT_UINT64, BASE_DEC,
			NULL, 0x0, NULL, HFILL }
	},
	{ &hf_blip_properties,
		{ "STR", FT_STRING, STR_UNICODE,
			NULL, 0x0, NULL, HFILL }
		},
	{ &hf_blip_message_body,
		{ "STR", FT_STRING, STR_UNICODE,
			NULL, 0x0, NULL, HFILL }
	},
	{ &hf_blip_ack_size,
		{ "STR", FT_UINT64, BASE_DEC,
			NULL, 0x0, NULL, HFILL }
	},
	{ &hf_blip_checksum,
		{ "STR", FT_UINT32, BASE_DEC,
			NULL, 0x0, NULL, HFILL }
	}
	};

	
	static gint *ett[] = {
		&ett_blip
	};

	proto_blip = proto_register_protocol("STR");

	proto_register_field_array(proto_blip, hf, array_length(hf));
	proto_register_subtree_array(ett, array_length(ett));

	blip_handle = register_dissector("STR", dissect_blip, proto_blip);
}