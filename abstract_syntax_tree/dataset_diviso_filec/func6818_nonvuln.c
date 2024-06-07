EC_Group::DER_encode(EC_Group_Encoding form) const
   {
   std::vector<uint8_t> output;

   DER_Encoder der(output);

   if(form == EC_DOMPAR_ENC_EXPLICIT)
      {
      const size_t ecpVers1 = 1;
      const OID curve_type("STR"); 

      const size_t p_bytes = get_p_bytes();

      der.start_cons(SEQUENCE)
            .encode(ecpVers1)
            .start_cons(SEQUENCE)
               .encode(curve_type)
               .encode(get_p())
            .end_cons()
            .start_cons(SEQUENCE)
               .encode(BigInt::encode_1363(get_a(), p_bytes),
                       OCTET_STRING)
               .encode(BigInt::encode_1363(get_b(), p_bytes),
                       OCTET_STRING)
            .end_cons()
              .encode(get_base_point().encode(PointGFp::UNCOMPRESSED), OCTET_STRING)
            .encode(get_order())
            .encode(get_cofactor())
         .end_cons();
      }
   else if(form == EC_DOMPAR_ENC_OID)
      {
      const OID oid = get_curve_oid();
      if(oid.empty())
         {
         throw Encoding_Error("STR");
         }
      der.encode(oid);
      }
   else if(form == EC_DOMPAR_ENC_IMPLICITCA)
      {
      der.encode_null();
      }
   else
      {
      throw Internal_Error("STR");
      }

   return output;
   }