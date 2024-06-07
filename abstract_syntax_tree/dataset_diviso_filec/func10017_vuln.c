int CephxSessionHandler::_calc_signature(Message *m, uint64_t *psig)
{
  const ceph_msg_header& header = m->get_header();
  const ceph_msg_footer& footer = m->get_footer();

  
  
  
  struct {
    __u8 v;
    __le64 magic;
    __le32 len;
    __le32 header_crc;
    __le32 front_crc;
    __le32 middle_crc;
    __le32 data_crc;
  } __attribute__ ((packed)) sigblock = {
    1, mswab(AUTH_ENC_MAGIC), mswab<uint32_t>(4*4),
    mswab<uint32_t>(header.crc), mswab<uint32_t>(footer.front_crc),
    mswab<uint32_t>(footer.middle_crc), mswab<uint32_t>(footer.data_crc)
  };

  char exp_buf[CryptoKey::get_max_outbuf_size(sizeof(sigblock))];

  try {
    const CryptoKey::in_slice_t in {
      sizeof(sigblock),
      reinterpret_cast<const unsigned char*>(&sigblock)
    };
    const CryptoKey::out_slice_t out {
      sizeof(exp_buf),
      reinterpret_cast<unsigned char*>(&exp_buf)
    };

    key.encrypt(cct, in, out);
  } catch (std::exception& e) {
    lderr(cct) << __func__ << "STR" << dendl;
    return -1;
  }

  *psig = *reinterpret_cast<__le64*>(exp_buf);

  ldout(cct, 10) << __func__ << "STR" << m->get_seq()
		 << "STR" << footer.front_crc
		 << "STR" << footer.middle_crc
		 << "STR" << footer.data_crc
		 << "STR" << *psig
		 << dendl;
  return 0;
}