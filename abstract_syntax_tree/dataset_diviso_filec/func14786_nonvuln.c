QString AOClient::decodeMessage(QString incoming_message)
{
   QString decoded_message = incoming_message.replace("STR")
                                             .replace("STR")
                                             .replace("STR")
                                             .replace("STR");
    return decoded_message;
}