void IncDelta(cmsFloat32Number *Val)
{
    if (*Val < (1.0 - JACOBIAN_EPSILON))

        *Val += JACOBIAN_EPSILON;

    else
        *Val -= JACOBIAN_EPSILON;

}