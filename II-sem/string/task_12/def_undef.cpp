#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "def_undef.hpp"

void def_undef(std::ifstream &fA, std::ofstream &fB)
{
    std::map<std::string, std::string> define;
    std::string curr; //текущая строка в данном файле
    std::string def = "#define ";
    std::string undef = "#undefine ";

    while (std::getline(fA, curr))
    {
        if (curr.find(def) != std::string::npos)
        {
            std::string core;   //то, что нужно заменять
            std::string change; //то, на что нужно заменить
            int pos = curr.find(def) + def.size();
            while (curr[pos] != ' ')
            {
                core += curr[pos];
                ++pos;
            }

            while (curr[pos] == ' ')
                ++pos;

            while (pos < curr.size())
            {
                change += curr[pos];
                ++pos;
            }
            define[core] = change;
        }
        else
        {
            if (curr.find(undef) != std::string::npos)
            {
                std::string curr_undef;
                int pos_undef = curr.find(undef) + undef.size();

                while (pos_undef < curr.size())
                {
                    curr_undef += curr[pos_undef];
                    ++pos_undef;
                }
                define.erase(curr_undef);
            }
            else
            {
                for (auto i : define)
                {
                    if (curr.find(i.first) != std::string::npos)
                    {
                        curr.replace(curr.find(i.first), i.first.size(), i.second);
                    }
                }
                fB << curr << std::endl;
            }
        }
    }
}