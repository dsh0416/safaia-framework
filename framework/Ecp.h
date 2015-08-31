/*
 * This is the HTML Rendering class of Safaia
 * Created By Delton Ding (dsh0416@gmail.com)
 * Create Time: 30 Aug 2015
 * Last Edited Time: 31 Aug 2015
 * */

#include <string>
#include <map>
#include <fstream>
#include <iostream>

#ifndef SAFAIA_FRAMEWORK_ECP_H
#define SAFAIA_FRAMEWORK_ECP_H

namespace Safaia{

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

    std::string ecp (std::string ecp_path, EcpAtom atom){

        // Read View File from Disk
        std::ifstream file;
        file.open(ecp_path);
        std::string temp_str;
        std::string view;
        while(file >> temp_str){
            view += temp_str;
            view += "\n";
        }
        file.close();

        for(auto it = atom.dic.begin(); it!=atom.dic.end(); it++){
            Safaia::replace_all(view, "<=$" + it->first + "=>", it->second);
        }

        return view;
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

}

#endif //SAFAIA_FRAMEWORK_ECP_H
