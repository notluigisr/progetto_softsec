    bool ms_verify_authorizer(Connection *con, int peer_type,
			      int protocol, bufferlist& authorizer_data, bufferlist& authorizer_reply,
			      bool& isvalid, CryptoKey& session_key) override {
      isvalid = true;
      return true;
    }