TEST(RoleParsingTest, BuildRoleBSON) {
    RoleGraph graph;
    RoleName roleA("STR");
    RoleName roleB("STR");
    RoleName roleC("STR");
    ActionSet actions;
    actions.addAction(ActionType::find);
    actions.addAction(ActionType::insert);

    ASSERT_OK(graph.createRole(roleA));
    ASSERT_OK(graph.createRole(roleB));
    ASSERT_OK(graph.createRole(roleC));

    ASSERT_OK(graph.addRoleToRole(roleA, roleC));
    ASSERT_OK(graph.addRoleToRole(roleA, roleB));
    ASSERT_OK(graph.addRoleToRole(roleB, roleC));

    ASSERT_OK(graph.addPrivilegeToRole(
        roleA, Privilege(ResourcePattern::forAnyNormalResource(), actions)));
    ASSERT_OK(graph.addPrivilegeToRole(
        roleB, Privilege(ResourcePattern::forExactNamespace(NamespaceString("STR")), actions)));
    ASSERT_OK(
        graph.addPrivilegeToRole(roleC, Privilege(ResourcePattern::forClusterResource(), actions)));
    ASSERT_OK(graph.recomputePrivilegeData());


    
    mutablebson::Document doc;
    ASSERT_OK(AuthorizationManager::getBSONForRole(&graph, roleA, doc.root()));
    BSONObj roleDoc = doc.getObject();

    ASSERT_EQUALS("STR"].String());
    ASSERT_EQUALS("STR"].String());
    ASSERT_EQUALS("STR"].String());

    vector<BSONElement> privs = roleDoc["STR"].Array();
    ASSERT_EQUALS(1U, privs.size());
    ASSERT_EQUALS("STR"].String());
    ASSERT_EQUALS("STR"].String());
    ASSERT(privs[0].Obj()["STR"].eoo());
    vector<BSONElement> actionElements = privs[0].Obj()["STR"].Array();
    ASSERT_EQUALS(2U, actionElements.size());
    ASSERT_EQUALS("STR", actionElements[0].String());
    ASSERT_EQUALS("STR", actionElements[1].String());

    vector<BSONElement> roles = roleDoc["STR"].Array();
    ASSERT_EQUALS(2U, roles.size());
    ASSERT_EQUALS("STR"].String());
    ASSERT_EQUALS("STR"].String());
    ASSERT_EQUALS("STR"].String());
    ASSERT_EQUALS("STR"].String());

    
    doc.reset();
    ASSERT_OK(AuthorizationManager::getBSONForRole(&graph, roleB, doc.root()));
    roleDoc = doc.getObject();

    ASSERT_EQUALS("STR"].String());
    ASSERT_EQUALS("STR"].String());
    ASSERT_EQUALS("STR"].String());

    privs = roleDoc["STR"].Array();
    ASSERT_EQUALS(1U, privs.size());
    ASSERT_EQUALS("STR"].String());
    ASSERT_EQUALS("STR"].String());
    ASSERT(privs[0].Obj()["STR"].eoo());
    actionElements = privs[0].Obj()["STR"].Array();
    ASSERT_EQUALS(2U, actionElements.size());
    ASSERT_EQUALS("STR", actionElements[0].String());
    ASSERT_EQUALS("STR", actionElements[1].String());

    roles = roleDoc["STR"].Array();
    ASSERT_EQUALS(1U, roles.size());
    ASSERT_EQUALS("STR"].String());
    ASSERT_EQUALS("STR"].String());

    
    doc.reset();
    ASSERT_OK(AuthorizationManager::getBSONForRole(&graph, roleC, doc.root()));
    roleDoc = doc.getObject();

    ASSERT_EQUALS("STR"].String());
    ASSERT_EQUALS("STR"].String());
    ASSERT_EQUALS("STR"].String());

    privs = roleDoc["STR"].Array();
    ASSERT_EQUALS(1U, privs.size());
    ASSERT(privs[0].Obj()["STR"].Bool());
    ASSERT(privs[0].Obj()["STR"].eoo());
    ASSERT(privs[0].Obj()["STR"].eoo());
    actionElements = privs[0].Obj()["STR"].Array();
    ASSERT_EQUALS(2U, actionElements.size());
    ASSERT_EQUALS("STR", actionElements[0].String());
    ASSERT_EQUALS("STR", actionElements[1].String());

    roles = roleDoc["STR"].Array();
    ASSERT_EQUALS(0U, roles.size());
}