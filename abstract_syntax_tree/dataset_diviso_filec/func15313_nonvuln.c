const Network::Address::Instance& HttpConnectionManagerConfig::localAddress() {
  return *context_.localInfo().address();
}