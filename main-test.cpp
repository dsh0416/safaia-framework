#include "framework/safaia/Safaia.h"
using namespace Safaia;

int main(){
    auto unitTest = UnitTest();

    // Unit Test Diagnostics
    auto secUnitTest = UnitTest();
    auto tstUnitTestSuc = CaseSet("Unit Test Success Example");
    tstUnitTestSuc.add(ASSERT("Integer Equal", 42, 42, EQUAL));
    tstUnitTestSuc.add(ASSERT("Integer Not Equal", 12, 450, NOT_EQUAL));
    tstUnitTestSuc.add(ASSERT("Double Equal", 1.5, 1.5, EQUAL));
    tstUnitTestSuc.add(ASSERT("Double Not Equal", -1.5, 1.5, NOT_EQUAL));
    tstUnitTestSuc.add(ASSERT("String Equal", "Lolicon", "Lolicon", EQUAL));
    tstUnitTestSuc.add(ASSERT("String Not Equal", "foo", "bar", NOT_EQUAL));
    secUnitTest.add(tstUnitTestSuc);
    int sec = secUnitTest.run();
    std::cout << std::endl;

    auto failUnitTest = UnitTest();
    auto tstUnitTestFail = CaseSet("Unit Test Failure Example");
    tstUnitTestFail.add(ASSERT("Integer Equal", 42, 42, NOT_EQUAL));
    tstUnitTestFail.add(ASSERT("Integer Not Equal", 12, 450, EQUAL));
    tstUnitTestFail.add(ASSERT("Double Equal", 1.5, 1.5, NOT_EQUAL));
    tstUnitTestFail.add(ASSERT("Double Not Equal", -1.5, 1.5, EQUAL));
    tstUnitTestFail.add(ASSERT("String Equal", "Lolicon", "Lolicon", NOT_EQUAL));
    tstUnitTestFail.add(ASSERT("String Not Equal", "foo", "bar", EQUAL));
    failUnitTest.add(tstUnitTestFail);
    int fail = failUnitTest.run();
    std::cout << std::endl;

    auto setUnitTest = CaseSet("Unit Test Diagnostics");
    setUnitTest.add(ASSERT("Example Failure Unit Test Result", fail, 0, NOT_EQUAL));
    setUnitTest.add(ASSERT("Example Success Unit Test Result", sec, 0, EQUAL));
    unitTest.add(setUnitTest);

    // Safaia Request Module Unit Test
    auto setRequest = CaseSet("Safaia Request Module Unit Test");
    auto request1 = Req("GET /login.html HTTP/1.1\r\nHost: 127.0.0.1\nConnection: keep-alive\nCache-Control: no-cache\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\nUpgrade-Insecure-Requests: 1\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/46.0.2490.80 Safari/537.36\nReferer: http://127.0.0.1/\nAccept-Encoding: gzip, deflate, sdch\nAccept-Language: zh-CN,zh;q=0.8,en-US;q=0.6,en;q=0.4,ja;q=0.2\r\n\r\nTest Body");
    setRequest.add(ASSERT("Request Method", request1.method, "GET", EQUAL));
    setRequest.add(ASSERT("Request Url", request1.request_url, "/login.html", EQUAL));
    setRequest.add(ASSERT("Protocol", request1.protocol, "HTTP/1.1", EQUAL));
    setRequest.add(ASSERT("Fast Header", request1.host, "127.0.0.1", EQUAL));
    setRequest.add(ASSERT("Standard Header", request1.header["Connection"], "keep-alive", EQUAL));
    setRequest.add(ASSERT("Body", request1.body, "Test Body\n", EQUAL));
    unitTest.add(setRequest);

    // Safaia Response Module Unit Test
    auto setResponse = CaseSet("Safaia Response Module Unit Test");
    auto response1 = Resp("Hello World");
    setResponse.add(ASSERT("Response Body", response1.body, "Hello World", EQUAL));
    setResponse.add(ASSERT("Response Status Code", response1.status_code, "200 OK", EQUAL));
    auto response2 = Resp(201, "Hello World");
    setResponse.add(ASSERT("Response Body", response2.body, "Hello World", EQUAL));
    setResponse.add(ASSERT("Response Status Code", response2.status_code, "201 Created", EQUAL));
    unitTest.add(setResponse);
    auto response3 = Resp(999, "Hello Internal Error");
    setResponse.add(ASSERT("Parse Status Code Error", response3.status_code, "500 Internal Server Error", EQUAL));

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

    return unitTest.run();
}