#include <iostream>
#include <vector>
#include <string>
#include <sstream>

namespace Safaia{

    enum ASSERT_RES{
        EQUAL,
        NOT_EQUAL
    };

    const std::string str_reset = "\033[0m";
    const std::string str_green = "\033[32m";
    const std::string str_yellow = "\033[33m";
    const std::string str_red = "\033[1m\033[31m";

    class ASSERT{
    public:

        std::string name;
        std::string result;
        bool passed = false;

        ASSERT(std::string name, int reality, int expected, int assert){
            if (assert == EQUAL){
                this->name = name;
                std::stringstream ss;
                ss << reality << " == " << expected << " ";
                if (reality == expected){
                    ss << str_green << "Passed" << str_reset;
                    passed = true;
                } else {
                    ss << str_red << "Failed" << str_reset;
                }
                result = ss.str();
            } else if(assert == NOT_EQUAL){
                this->name = name;
                std::stringstream ss;
                ss << reality << " != " << expected << " ";
                if (reality != expected){
                    ss << str_green << "Passed" << str_reset;
                    passed = true;
                } else {
                    ss << str_red << "Failed" << str_reset;
                }
                result = ss.str();
            }
        }

        ASSERT(std::string name, double reality, double expected, int assert){
            if (assert == EQUAL){
                this->name = name;
                std::stringstream ss;
                ss << reality << " == " << expected << " ";
                if (reality == expected){
                    ss << str_green << "Passed" << str_reset;
                    passed = true;
                } else {
                    ss << str_red << "Failed" << str_reset;
                }
                result = ss.str();
            } else if(assert == NOT_EQUAL){
                this->name = name;
                std::stringstream ss;
                ss << reality << " != " << expected << " ";
                if (reality != expected){
                    ss << str_green << "Passed" << str_reset;
                    passed = true;
                } else {
                    ss << str_red << "Failed" << str_reset;
                }
                result = ss.str();
            }
        }

        ASSERT(std::string name, std::string reality, std::string expected, int assert){
            if (assert == EQUAL){
                this->name = name;
                std::stringstream ss;
                ss << reality << " == " << expected << " ";
                if (reality == expected){
                    ss << str_green << "Passed" << str_reset;
                    passed = true;
                } else {
                    ss << str_red << "Failed" << str_reset;
                }
                result = ss.str();
            } else if(assert == NOT_EQUAL){
                this->name = name;
                std::stringstream ss;
                ss << reality << " != " << expected << " ";
                if (reality != expected){
                    ss << str_green << "Passed" << str_reset;
                    passed = true;
                } else {
                    ss << str_red << "Failed" << str_reset;
                }
                result = ss.str();
            }
        }
    };

    class CaseSet{
    public:
        std::string name;
        std::vector<Safaia::ASSERT> test_cases;

        CaseSet(std::string name){
            this->name = name;
        }

        CaseSet(){
            this->name = "";
        }

        void add(ASSERT test){
            this->test_cases.push_back(test);
        }
    };


    class UnitTest{
        std::vector<CaseSet> case_sets;

    public:
        UnitTest(){ }

        void add(CaseSet caseSet){
            case_sets.push_back(caseSet);
        }

        int run(){
            int total = 0;
            int passed = 0;

            for(int i=0; i<case_sets.size(); i++){
                std::cout << "Test Set[" << i << "] " << case_sets[i].name << ":" << std::endl;
                total += case_sets[i].test_cases.size();

                int set_passed = 0;
                for (int j=0; j<case_sets[i].test_cases.size(); j++){
                    std::cout << "    Test[" << j << "] " << case_sets[i].test_cases[j].name << ": "
                    << case_sets[i].test_cases[j].result << std::endl;
                    if(case_sets[i].test_cases[j].passed) {passed ++; set_passed ++;};
                }
                if (set_passed == case_sets[i].test_cases.size()){
                    std::cout << "Set[" << i << "] " << case_sets[i].name << " Finished: " <<
                            str_green << set_passed << " Passed / " << case_sets[i].test_cases.size() << " Total" <<
                            str_reset << std::endl;
                } else {
                    std::cout << "Set[" << i << "] " << case_sets[i].name << " Finished: " <<
                            str_red << set_passed << " Passed / " << case_sets[i].test_cases.size() << " Total" <<
                            str_reset << std::endl;
                }
            }

            if (passed == total){
                std::cout << "Test Finished: " <<
                        str_green << passed << " Passed / " << total << " Total" << str_reset << std::endl;
                return 0;
            } else {
                std::cout << "Test Finished: " <<
                        str_red << passed << " Passed / " << total << " Total" << str_reset << std::endl;
                return 1;
            }
        }
    };

}
