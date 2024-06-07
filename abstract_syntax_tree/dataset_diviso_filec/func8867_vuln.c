TEST_F(ZNCTest, StatusEchoMessage) {
    auto znc = Run();
    auto ircd = ConnectIRCd();
    auto client = LoginClient();
    client.Write("STR");
    client.Write("STR");
    client.ReadUntil("STR");
    client.ReadUntil("STR");
}