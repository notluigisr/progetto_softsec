OPJ_BOOL opj_tcd_mct_decode ( opj_tcd_t *p_tcd )
{
        opj_tcd_tile_t * l_tile = p_tcd->tcd_image->tiles;
        opj_tcp_t * l_tcp = p_tcd->tcp;
        opj_tcd_tilecomp_t * l_tile_comp = l_tile->comps;
        OPJ_UINT32 l_samples,i;

        if (! l_tcp->mct) {
                return OPJ_TRUE;
        }

        l_samples = (OPJ_UINT32)((l_tile_comp->x1 - l_tile_comp->x0) * (l_tile_comp->y1 - l_tile_comp->y0));

        if (l_tile->numcomps >= 3 ){
                
                if ((l_tile->comps[0].x1 - l_tile->comps[0].x0) * (l_tile->comps[0].y1 - l_tile->comps[0].y0) < (OPJ_INT32)l_samples ||
                    (l_tile->comps[1].x1 - l_tile->comps[1].x0) * (l_tile->comps[1].y1 - l_tile->comps[1].y0) < (OPJ_INT32)l_samples ||
                    (l_tile->comps[2].x1 - l_tile->comps[2].x0) * (l_tile->comps[2].y1 - l_tile->comps[2].y0) < (OPJ_INT32)l_samples) {
                        fprintf(stderr, "STR");
                        return OPJ_FALSE;
                }
                else if (l_tcp->mct == 2) {
                        OPJ_BYTE ** l_data;

                        if (! l_tcp->m_mct_decoding_matrix) {
                                return OPJ_TRUE;
                        }

                        l_data = (OPJ_BYTE **) opj_malloc(l_tile->numcomps*sizeof(OPJ_BYTE*));
                        if (! l_data) {
                                return OPJ_FALSE;
                        }

                        for (i=0;i<l_tile->numcomps;++i) {
                                l_data[i] = (OPJ_BYTE*) l_tile_comp->data;
                                ++l_tile_comp;
                        }

                        if (! opj_mct_decode_custom(
                                                                        (OPJ_BYTE*) l_tcp->m_mct_decoding_matrix,
                                                                        
                                                                        l_samples,
                                                                        
                                                                        l_data,
                                                                        
                                                                        l_tile->numcomps,
                                                                        
                                                                        p_tcd->image->comps->sgnd)) {
                                opj_free(l_data);
                                return OPJ_FALSE;
                        }

                        opj_free(l_data);
                }
                else {
                        if (l_tcp->tccps->qmfbid == 1) {
                                opj_mct_decode(     l_tile->comps[0].data,
                                                        l_tile->comps[1].data,
                                                        l_tile->comps[2].data,
                                                        l_samples);
                        }
                        else {
                            opj_mct_decode_real((OPJ_FLOAT32*)l_tile->comps[0].data,
                                                (OPJ_FLOAT32*)l_tile->comps[1].data,
                                                (OPJ_FLOAT32*)l_tile->comps[2].data,
                                                l_samples);
                        }
                }
        }
        else {
                
                fprintf(stderr,"STR",l_tile->numcomps);
        }

        return OPJ_TRUE;
}