int EC_GROUP_order_bits(const EC_GROUP *group)
{
    return group->meth->group_order_bits(group);
}