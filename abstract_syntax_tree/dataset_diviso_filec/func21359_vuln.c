  virtual bool ms_verify_authorizer(Connection *con,
				    int peer_type,
				    int protocol,
				    ceph::bufferlist& authorizer,
				    ceph::bufferlist& authorizer_reply,
				    bool& isvalid,
				    CryptoKey& session_key) { return false; }