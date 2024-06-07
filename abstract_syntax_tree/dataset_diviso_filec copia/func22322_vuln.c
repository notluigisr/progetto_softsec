set_text_distance(gs_point *pdist, double dx, double dy, const gs_matrix *pmat)
{
    int code = gs_distance_transform_inverse(dx, dy, pmat, pdist);
    double rounded;

    if (code == gs_error_undefinedresult) {
        
        pdist->x = pdist->y = 0;
    } else if (code < 0)
        return code;
    
    if (fabs(pdist->x - (rounded = floor(pdist->x + 0.5))) < 0.0005)
        pdist->x = rounded;
    if (fabs(pdist->y - (rounded = floor(pdist->y + 0.5))) < 0.0005)
        pdist->y = rounded;
    return 0;
}