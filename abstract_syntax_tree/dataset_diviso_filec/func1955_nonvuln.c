bool HaarEvaluator::setWindow( Point pt, int scaleIdx )
{
    const ScaleData& s = getScaleData(scaleIdx);

    if( pt.x < 0 || pt.y < 0 ||
        pt.x + origWinSize.width >= s.szi.width ||
        pt.y + origWinSize.height >= s.szi.height )
        return false;

    pwin = &sbuf.at<int>(pt) + s.layer_ofs;
    const int* pq = (const int*)(pwin + sqofs);
    int valsum = CALC_SUM_OFS(nofs, pwin);
    unsigned valsqsum = (unsigned)(CALC_SUM_OFS(nofs, pq));

    double area = normrect.area();
    double nf = area * valsqsum - (double)valsum * valsum;
    if( nf > 0. )
    {
        nf = std::sqrt(nf);
        varianceNormFactor = (float)(1./nf);
        return area*varianceNormFactor < 1e-1;
    }
    else
    {
        varianceNormFactor = 1.f;
        return false;
    }
}