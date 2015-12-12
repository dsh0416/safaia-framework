#include "framework/safaia/Safaia.h"
using namespace Safaia;

int main(){
    auto server = Server();
    auto unit_test = UnitTest();

    auto set = CaseSet("Hello Test");
    set.add(ASSERT("num", 1, 1, EQUAL));
    set.add(ASSERT("bool", true, false, NOT_EQUAL));
    set.add(ASSERT("string", "hello", "hello", EQUAL));
    set.add(ASSERT("plus", 1 + 1, 2, EQUAL));
    set.add(ASSERT("not_eq", 1, 2, NOT_EQUAL));
    unit_test.add(set);

    unit_test.run();
    return 0;
}