TEST_F(AccessControlTest, validate_topic_access_ok_no_partitions)
{
    topic_name = "STR";

    RTPSParticipantAttributes subscriber_participant_attr;
    fill_subscriber_participant_security_attributes(subscriber_participant_attr);
    check_local_datareader(subscriber_participant_attr, true);
    check_remote_datareader(subscriber_participant_attr, true);

    RTPSParticipantAttributes publisher_participant_attr;
    fill_publisher_participant_security_attributes(publisher_participant_attr);
    check_local_datawriter(publisher_participant_attr, true);
    check_remote_datawriter(publisher_participant_attr, true);
}