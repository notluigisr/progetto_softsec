const EC_METHOD *EC_POINT_method_of(const EC_POINT *point)
{
    return point->meth;
}