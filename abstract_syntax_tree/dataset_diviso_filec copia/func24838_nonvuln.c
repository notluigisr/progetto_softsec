int geoAppendIfWithinRadius(geoArray *ga, double lon, double lat, double radius, double score, sds member) {
    double distance, xy[2];

    if (!decodeGeohash(score,xy)) return C_ERR; 
    
    if (!geohashGetDistanceIfInRadiusWGS84(lon,lat, xy[0], xy[1],
                                           radius, &distance))
    {
        return C_ERR;
    }

    
    geoPoint *gp = geoArrayAppend(ga);
    gp->longitude = xy[0];
    gp->latitude = xy[1];
    gp->dist = distance;
    gp->member = member;
    gp->score = score;
    return C_OK;
}