#include "framework/safaia/Safaia.h"
using namespace Safaia;

int main(){
    auto unitTest = UnitTest();

    // Unit Test Diagnostics
    auto setUnitTest = CaseSet("Unit Test Diagnostics");
    setUnitTest.add(ASSERT("Integer Equal", 42, 42, EQUAL));
    setUnitTest.add(ASSERT("Integer Not Equal", 12, 450, NOT_EQUAL));
    setUnitTest.add(ASSERT("Double Equal", 1.5, 1.5, EQUAL));
    setUnitTest.add(ASSERT("Double Not Equal", -1.5, 1.5, NOT_EQUAL));
    setUnitTest.add(ASSERT("String Equal", "Lolicon", "Lolicon", EQUAL));
    setUnitTest.add(ASSERT("String Not Equal", "foo", "bar", NOT_EQUAL));
    unitTest.add(setUnitTest);

    // Safaia Response Module Unit Test
    auto setResponse = CaseSet("Safaia Response Module Unit Test");
    auto response1 = Resp("Hello World");
    setResponse.add(ASSERT("Response Body", response1.body, "Hello World", EQUAL));
    setResponse.add(ASSERT("Response Status Code", response1.status_code, "200 OK", EQUAL));
    auto response2 = Resp(201, "Hello World");
    setResponse.add(ASSERT("Response Body", response2.body, "Hello World", EQUAL));
    setResponse.add(ASSERT("Response Status Code", response2.status_code, "201 Created", EQUAL));
    unitTest.add(setResponse);

    // Safaia Route Module Unit Test
    auto setRoute = CaseSet("Safaia Route Module Unit Test");
    auto route1 = Route("GET", "/", [](Req req){return Resp("Hello World");});
    setRoute.add(ASSERT("Route Method", route1.method, "GET", EQUAL));
    setRoute.add(ASSERT("Route Path", route1.path, "/", EQUAL));
    setRoute.add(ASSERT("Match Type", route1.is_regex, false, EQUAL));
    auto route2 = Route("POST", std::regex("/(.*)"), [](Req req){return Resp("Hello World");});
    setRoute.add(ASSERT("Route Method", route2.method, "POST", EQUAL));
    setRoute.add(ASSERT("Route Path", route2.path, "", EQUAL));
    setRoute.add(ASSERT("Match Type", route2.is_regex, true, EQUAL));
    unitTest.add(setRoute);

    // Safaia Framework Unit Test
    auto setSafaia = CaseSet("Safaia Framework Unit Test");
    auto server = Server();
    unitTest.add(setSafaia);

    unitTest.run();
    return 0;
}