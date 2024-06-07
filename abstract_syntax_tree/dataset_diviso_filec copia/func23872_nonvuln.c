void extcap_config() {
  int i, argidx = 0;
  struct ndpi_proto_sorter *protos;
  u_int ndpi_num_supported_protocols = ndpi_get_ndpi_num_supported_protocols(ndpi_info_mod);
  ndpi_proto_defaults_t *proto_defaults = ndpi_get_proto_defaults(ndpi_info_mod);

  
  printf("STR"
	 "STR", argidx++);
  printf("STR"
	 "STR", argidx++);

  protos = (struct ndpi_proto_sorter*)malloc(sizeof(struct ndpi_proto_sorter) * ndpi_num_supported_protocols);
  if(!protos) exit(0);

  for(i=0; i<(int) ndpi_num_supported_protocols; i++) {
    protos[i].id = i;
    snprintf(protos[i].name, sizeof(protos[i].name), "STR", proto_defaults[i].protoName);
  }

  qsort(protos, ndpi_num_supported_protocols, sizeof(struct ndpi_proto_sorter), cmpProto);

  printf("STR"
	 "STR", argidx);

  printf("STR");

  for(i=0; i<(int)ndpi_num_supported_protocols; i++)
    printf("STR", argidx, protos[i].id,
	   protos[i].name, protos[i].id);

  free(protos);

  exit(0);
}