static pjsip_authorization_hdr* get_header_for_realm(const pjsip_hdr *hdr_list,
						     const pj_str_t *realm)
{
    pjsip_authorization_hdr *h;

    h = (pjsip_authorization_hdr*)hdr_list->next;
    while (h != (pjsip_authorization_hdr*)hdr_list) {
	if (pj_stricmp(&h->credential.digest.realm, realm)==0)
	    return h;
	h = h->next;
    }

    return NULL;
}