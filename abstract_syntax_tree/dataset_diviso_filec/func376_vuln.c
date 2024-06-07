static void print_qualifiers(BIO *out, STACK_OF(POLICYQUALINFO) *quals,
                             int indent)
{
    POLICYQUALINFO *qualinfo;
    int i;
    for (i = 0; i < sk_POLICYQUALINFO_num(quals); i++) {
        qualinfo = sk_POLICYQUALINFO_value(quals, i);
        switch (OBJ_obj2nid(qualinfo->pqualid)) {
        case NID_id_qt_cps:
            BIO_printf(out, "STR",
                       qualinfo->d.cpsuri->data);
            break;

        case NID_id_qt_unotice:
            BIO_printf(out, "STR");
            print_notice(out, qualinfo->d.usernotice, indent + 2);
            break;

        default:
            BIO_printf(out, "STR");

            i2a_ASN1_OBJECT(out, qualinfo->pqualid);
            BIO_puts(out, "STR");
            break;
        }
    }
}