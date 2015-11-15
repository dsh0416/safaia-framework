#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <unordered_map>

#ifndef SAFAIA_FRAMEWORK_ECP_H
#define SAFAIA_FRAMEWORK_ECP_H

namespace Safaia{

    std::unordered_map<std::string, std::string> ecp_cache;
    bool enable_ecp_cache = false;

    std::string& replace_all(std::string& str,const std::string& old_value,const std::string& new_value)
    {
        while(true)
        {
            unsigned long pos=0;
            if((pos=str.find(old_value,0))!=std::string::npos)
                str.replace(pos,old_value.length(),new_value);
            else break;
        }
        return str;
    }

    class EcpAtom {
    public:

        std::map<std::string,std::string> dic;
        EcpAtom(){
        }

        void store(std::string key, std::string val){
            dic.insert(std::pair<std::string,std::string>(key,val));
        }

    };

    std::string ecp (std::string ecp_path, EcpAtom atom){

        std::string view;
        if (enable_ecp_cache){
            auto cache_got = ecp_cache.find(ecp_path);

            if (cache_got == ecp_cache.end()){
                // Cache not found
                // Read View File from Disk
                std::ifstream file;
                file.open(ecp_path);
                std::string temp_str;

                while(getline(file, temp_str)){
                    view += temp_str;
                    view += "\n";
                }
                file.close();

                // Add to cache
                ecp_cache[ecp_path] = view;
            } else {
                // Cache Found
                view = cache_got->second;
            }
        } else {
            // Read View File from Disk
            std::ifstream file;
            file.open(ecp_path);
            std::string temp_str;

            while(getline(file, temp_str)){
                view += temp_str;
                view += "\n";
            }
            file.close();
        }


        for(auto it = atom.dic.begin(); it!=atom.dic.end(); it++){
            Safaia::replace_all(view, "<=$" + it->first + "=>", it->second);
        }

        return view;
    }



}

#endif //SAFAIA_FRAMEWORK_ECP_H
