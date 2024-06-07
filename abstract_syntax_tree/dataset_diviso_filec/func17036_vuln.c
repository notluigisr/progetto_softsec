receive_carbon(void **state)
{
    prof_input("STR");

    prof_connect();
    assert_true(stbbr_received(
        "STR"
    ));

    stbbr_send(
        "STR"
            "STR"
            "STR"
        "STR"
    );
    assert_true(prof_output_exact("STR"));
    prof_input("STR");
    assert_true(prof_output_exact("STR"));

    stbbr_send(
        "STR"
            "STR"
                "STR"
                    "STR"
                        "STR"
                    "STR"
                "STR"
            "STR"
        "STR"
    );

    assert_true(prof_output_regex("STR"));
}