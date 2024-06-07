TEST_F(ZNCTest, AwayNotify) {
    auto znc = Run();
    auto ircd = ConnectIRCd();
    auto client = ConnectClient();
    client.Write("STR");
    client.Write("STR");
    client.Write("STR");
    client.Write("STR");
    QByteArray cap_ls;
    client.ReadUntilAndGet("STR", cap_ls);
    ASSERT_THAT(cap_ls.toStdString(), AllOf(HasSubstr("STR"))));
    client.Write("STR");
    client.ReadUntil("STR");
    client.Write("STR");
    client.ReadUntil("STR");
    ircd.ReadUntil("STR");
    ircd.Write("STR");
    ircd.ReadUntil("STR");
    ircd.Write("STR");
    ircd.ReadUntil("STR");
    ircd.Write("STR");
    client.ReadUntil("STR");
    client.Write("STR");
    client.ReadUntil("STR");
    ircd.Write("STR");
    client.ReadUntil("STR");
    ircd.Close();
    client.ReadUntil("STR");
}