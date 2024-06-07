void moof_box_del(GF_Box *s)
{
	GF_MovieFragmentBox *ptr = (GF_MovieFragmentBox *)s;
	if (ptr == NULL) return;

	gf_list_del(ptr->TrackList);
	if (ptr->PSSHs) gf_list_del(ptr->PSSHs);
	if (ptr->mdat) gf_free(ptr->mdat);
	
	if (ptr->emsgs) {
		while (1) {
			GF_Box *emsg = gf_list_pop_front(ptr->emsgs);
			if (!emsg) break;
			gf_isom_box_del(emsg);
		}
		gf_list_del(ptr->emsgs);
	}
	gf_free(ptr);
}