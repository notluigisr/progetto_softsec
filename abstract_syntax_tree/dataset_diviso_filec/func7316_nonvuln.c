_PUBLIC_ enum ndr_err_code ndr_push_dns_string(struct ndr_push *ndr,
					       int ndr_flags,
					       const char *s)
{
	return ndr_push_dns_string_list(ndr,
					&ndr->dns_string_list,
					ndr_flags,
					s,
					false);
}