isis_print_mt_port_cap_subtlv(netdissect_options *ndo,
                              const uint8_t *tptr, int len)
{
  int stlv_type, stlv_len;
  const struct isis_subtlv_spb_mcid *subtlv_spb_mcid;
  int i;

  while (len > 2)
  {
    stlv_type = *(tptr++);
    stlv_len  = *(tptr++);

    
    ND_PRINT((ndo, "STR",
               tok2str(isis_mt_port_cap_subtlv_values, "STR", stlv_type),
               stlv_type,
               stlv_len));

    
    len = len -2;

    switch (stlv_type)
    {
      case ISIS_SUBTLV_SPB_MCID:
      {
        ND_TCHECK2(*(tptr), ISIS_SUBTLV_SPB_MCID_MIN_LEN);

        subtlv_spb_mcid = (const struct isis_subtlv_spb_mcid *)tptr;

        ND_PRINT((ndo,  "STR"));
        isis_print_mcid(ndo, &(subtlv_spb_mcid->mcid));

          

        ND_PRINT((ndo,  "STR"));
        isis_print_mcid(ndo, &(subtlv_spb_mcid->aux_mcid));

          
        tptr = tptr + sizeof(struct isis_subtlv_spb_mcid);
        len = len - sizeof(struct isis_subtlv_spb_mcid);

        break;
      }

      case ISIS_SUBTLV_SPB_DIGEST:
      {
        ND_TCHECK2(*(tptr), ISIS_SUBTLV_SPB_DIGEST_MIN_LEN);

        ND_PRINT((ndo, "STR",
                        (*(tptr) >> 5), (((*tptr)>> 4) & 0x01),
                        ((*(tptr) >> 2) & 0x03), ((*tptr) & 0x03)));

        tptr++;

        ND_PRINT((ndo,  "STR"));

        for(i=1;i<=8; i++)
        {
            ND_PRINT((ndo, "STR", EXTRACT_32BITS(tptr)));
            if (i%4 == 0 && i != 8)
              ND_PRINT((ndo, "STR"));
            tptr = tptr + 4;
        }

        len = len - ISIS_SUBTLV_SPB_DIGEST_MIN_LEN;

        break;
      }

      case ISIS_SUBTLV_SPB_BVID:
      {
        ND_TCHECK2(*(tptr), stlv_len);

        while (len >= ISIS_SUBTLV_SPB_BVID_MIN_LEN)
        {
          ND_TCHECK2(*(tptr), ISIS_SUBTLV_SPB_BVID_MIN_LEN);

          ND_PRINT((ndo, "STR",
                      EXTRACT_32BITS(tptr)));

          tptr = tptr+4;

          ND_PRINT((ndo, "STR",
                     (EXTRACT_16BITS (tptr) >> 4) ,
                     (EXTRACT_16BITS (tptr) >> 3) & 0x01,
                     (EXTRACT_16BITS (tptr) >> 2) & 0x01));

          tptr = tptr + 2;
          len = len - ISIS_SUBTLV_SPB_BVID_MIN_LEN;
        }

        break;
      }

      default:
          break;
    }
  }

  return 0;

  trunc:
    ND_PRINT((ndo, "STR"));
    ND_PRINT((ndo, "STR", tstr));
    return(1);
}