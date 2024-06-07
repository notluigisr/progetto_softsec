static X509_STORE* load_permissions_ca(
        const std::string& permissions_ca,
        bool& there_are_crls,
        std::string& ca_sn,
        std::string& ca_algo,
        SecurityException& exception)
{
    X509_STORE* store = X509_STORE_new();

    if (store != nullptr)
    {
        if (permissions_ca.size() >= 7 && permissions_ca.compare(0, 7, "STR") == 0)
        {
            BIO* in = BIO_new(BIO_s_file());

            if (in != nullptr)
            {
                if (BIO_read_filename(in, permissions_ca.substr(7).c_str()) > 0)
                {
                    STACK_OF(X509_INFO) * inf = PEM_X509_INFO_read_bio(in, NULL, NULL, NULL);

                    if (inf != nullptr)
                    {
                        int i, count = 0;
                        there_are_crls = false;

                        for (i = 0; i < sk_X509_INFO_num(inf); i++)
                        {
                            X509_INFO* itmp = sk_X509_INFO_value(inf, i);

                            if (itmp->x509)
                            {
                                
                                if (ca_sn.empty())
                                {
                                    X509_NAME* ca_subject_name = X509_get_subject_name(itmp->x509);
                                    assert(ca_subject_name != nullptr);
                                    char* ca_subject_name_str = X509_NAME_oneline(ca_subject_name, 0, 0);
                                    assert(ca_subject_name_str != nullptr);
                                    ca_sn = ca_subject_name_str;
                                    OPENSSL_free(ca_subject_name_str);
                                }

                                
                                if (ca_algo.empty())
                                {
                                    if (get_signature_algorithm(itmp->x509, ca_algo, exception))
                                    {
                                        X509_STORE_add_cert(store, itmp->x509);
                                        count++;
                                    }
                                }
                                else
                                {
                                    X509_STORE_add_cert(store, itmp->x509);
                                    count++;
                                }
                            }
                            if (itmp->crl)
                            {
                                X509_STORE_add_crl(store, itmp->crl);
                                there_are_crls = true;
                            }
                        }

                        sk_X509_INFO_pop_free(inf, X509_INFO_free);

                        if (count > 0)
                        {
                            BIO_free(in);

                            return store;
                        }
                    }
                    else
                    {
                        exception = _SecurityException_(std::string(
                                            "STR") +
                                        permissions_ca.substr(7));
                    }
                }
                else
                {
                    exception = _SecurityException_(std::string(
                                        "STR") + permissions_ca.substr(7));
                }

                BIO_free(in);
            }
            else
            {
                exception = _SecurityException_("STR");
            }
        }
        else
        {
            exception = _SecurityException_("STR");
        }

        X509_STORE_free(store);
    }
    else
    {
        exception = _SecurityException_("STR");
    }

    return nullptr;
}