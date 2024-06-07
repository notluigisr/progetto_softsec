resolve_superior_type_check(struct lys_type *type)
{
    uint32_t i;

    if (type->base == LY_TYPE_DER) {
        
        return EXIT_FAILURE;
    } else if (type->base == LY_TYPE_UNION) {
        
        for (i = 0; i < type->info.uni.count; ++i) {
            if (resolve_superior_type_check(&type->info.uni.types[i])) {
                return EXIT_FAILURE;
            }
        }
    } else if (type->base == LY_TYPE_LEAFREF) {
        
        while (!type->info.lref.path) {
            assert(type->der);
            type = &type->der->type;
        }
    }

    return EXIT_SUCCESS;
}