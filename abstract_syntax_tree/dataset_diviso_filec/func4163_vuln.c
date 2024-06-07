boost::optional<SaplingOutgoingPlaintext> SaplingOutgoingPlaintext::decrypt(
    const SaplingOutCiphertext &ciphertext,
    const uint256& ovk,
    const uint256& cv,
    const uint256& cm,
    const uint256& epk
)
{
    auto pt = AttemptSaplingOutDecryption(ciphertext, ovk, cv, cm, epk);
    if (!pt) {
        return boost::none;
    }

    
    CDataStream ss(SER_NETWORK, PROTOCOL_VERSION);
    ss << pt.get();

    SaplingOutgoingPlaintext ret;
    ss >> ret;

    assert(ss.size() == 0);

    return ret;
}