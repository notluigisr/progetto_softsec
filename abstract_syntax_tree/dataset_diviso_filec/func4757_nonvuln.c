void j2k_dump (opj_j2k_t* p_j2k, OPJ_INT32 flag, FILE* out_stream)
{
        
        if ( (flag & OPJ_JP2_INFO) || (flag & OPJ_JP2_IND)){
                fprintf(out_stream, "STR");
                return;
        }

        
        if (flag & OPJ_IMG_INFO){
                if (p_j2k->m_private_image)
                        j2k_dump_image_header(p_j2k->m_private_image, 0, out_stream);
        }

        
        if (flag & OPJ_J2K_MH_INFO){
                opj_j2k_dump_MH_info(p_j2k, out_stream);
        }
        
        if (flag & OPJ_J2K_TCH_INFO){
          OPJ_UINT32 l_nb_tiles = p_j2k->m_cp.th * p_j2k->m_cp.tw;
          OPJ_UINT32 i;
          opj_tcp_t * l_tcp = p_j2k->m_cp.tcps;
          for (i=0;i<l_nb_tiles;++i) {
            opj_j2k_dump_tile_info( l_tcp,(OPJ_INT32)p_j2k->m_private_image->numcomps, out_stream);
            ++l_tcp;
          }
        }

        
        if (flag & OPJ_J2K_TH_INFO){

        }

        
        if (flag & OPJ_J2K_MH_IND){
                opj_j2k_dump_MH_index(p_j2k, out_stream);
        }

        
        if (flag & OPJ_J2K_TH_IND){

        }

}