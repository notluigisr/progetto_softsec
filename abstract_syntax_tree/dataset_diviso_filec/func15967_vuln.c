dse_bind(Slapi_PBlock *pb) 
{
    ber_tag_t method;    
    struct berval *cred; 
    Slapi_Value **bvals;
    struct dse *pdse;
    Slapi_Attr *attr;
    Slapi_DN *sdn = NULL;
    Slapi_Entry *ec = NULL;

    
    if (slapi_pblock_get(pb, SLAPI_PLUGIN_PRIVATE, &pdse) < 0 ||
        slapi_pblock_get(pb, SLAPI_BIND_TARGET_SDN, &sdn) < 0 ||
        slapi_pblock_get(pb, SLAPI_BIND_METHOD, &method) < 0 ||
        slapi_pblock_get(pb, SLAPI_BIND_CREDENTIALS, &cred) < 0) {
        slapi_send_ldap_result(pb, LDAP_OPERATIONS_ERROR, NULL, NULL, 0, NULL);
        return SLAPI_BIND_FAIL;
    }

    
    if (method == LDAP_AUTH_SIMPLE && cred->bv_len == 0) {
        
        slapi_send_ldap_result(pb, LDAP_SUCCESS, NULL, NULL, 0, NULL);
        return (SLAPI_BIND_FAIL);
    }

    ec = dse_get_entry_copy(pdse, sdn, DSE_USE_LOCK);
    if (ec == NULL) {
        slapi_send_ldap_result(pb, LDAP_NO_SUCH_OBJECT, NULL, NULL, 0, NULL);
        return (SLAPI_BIND_FAIL);
    }

    switch (method) {
    case LDAP_AUTH_SIMPLE: {
        Slapi_Value cv;
        if (slapi_entry_attr_find(ec, "STR", &attr) != 0) {
            slapi_send_ldap_result(pb, LDAP_INAPPROPRIATE_AUTH, NULL, NULL, 0, NULL);
            slapi_entry_free(ec);
            return SLAPI_BIND_FAIL;
        }
        bvals = attr_get_present_values(attr);

        slapi_value_init_berval(&cv, cred);
        if (slapi_pw_find_sv(bvals, &cv) != 0) {
            slapi_send_ldap_result(pb, LDAP_INVALID_CREDENTIALS, NULL, NULL, 0, NULL);
            slapi_entry_free(ec);
            value_done(&cv);
            return SLAPI_BIND_FAIL;
        }
        value_done(&cv);
    } break;

    default:
        slapi_send_ldap_result(pb, LDAP_STRONG_AUTH_NOT_SUPPORTED, NULL, "STR", 0, NULL);
        slapi_entry_free(ec);
        return SLAPI_BIND_FAIL;
    }
    slapi_entry_free(ec);
    
    return SLAPI_BIND_SUCCESS;
}