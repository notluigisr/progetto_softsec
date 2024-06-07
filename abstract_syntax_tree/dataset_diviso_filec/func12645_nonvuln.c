pcl_flush_all_pages(pcl_args_t * pargs, pcl_state_t * pcs)
{
    switch (uint_arg(pargs)) {
        case 0:
            {                   
                
                return 0;
            }
        case 1:
            {                   
                int code = pcl_end_page_if_marked(pcs);

                if (code >= 0)
                    code = pcl_home_cursor(pcs);
                return code;
            }
        default:
            return e_Range;
    }
}