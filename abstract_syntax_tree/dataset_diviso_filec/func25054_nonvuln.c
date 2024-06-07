void CertificateRequest::Build()
{
    certificate_types_[0] = rsa_sign;
    certificate_types_[1] = dss_sign;

    typeTotal_ = 2;

    uint16 authCount = 0;
    uint16 authSz = 0;
  
    for (int j = 0; j < authCount; j++) {
        int sz = REQUEST_HEADER + MIN_DIS_SIZE;
        DistinguishedName dn;
        certificate_authorities_.push_back(dn = NEW_YS byte[sz]);

        opaque tmp[REQUEST_HEADER];
        c16toa(MIN_DIS_SIZE, tmp);
        memcpy(dn, tmp, sizeof(tmp));
  
        
        memcpy(dn, tmp, MIN_DIS_SIZE);
        authSz += sz;
    }

    set_length(SIZEOF_ENUM + typeTotal_ + REQUEST_HEADER + authSz);
}