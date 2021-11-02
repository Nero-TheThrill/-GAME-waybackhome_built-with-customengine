/*
*  File Name : JSONWRITER.h
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Make easy to load/save objects. 
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include <string>

#include <vector>
#include<fstream>

namespace rapidjson
{
    class JSONwriter
    {
    public:
        JSONwriter();
        ~JSONwriter();
        void WriteToFile(const std::string& path);
        void ClearFile(const std::string& path);

        const char* GetString() const;


        operator bool() const { return true; }

        JSONwriter& StartObject();
        JSONwriter& Member(const char* name);
        bool HasMember(const char* name) const;
        JSONwriter& EndObject();

        JSONwriter& StartArray(size_t* size = 0);
        JSONwriter& EndArray();

        JSONwriter& operator&(bool& b);
        JSONwriter& operator&(unsigned& u);
        JSONwriter& operator&(int& i);
        JSONwriter& operator&(double d);
        JSONwriter& operator&(std::string s);
        JSONwriter& SetNull();

        static const bool IsReader = false;
        static const bool IsWriter = !IsReader;

    private:
        JSONwriter(const JSONwriter&);
        JSONwriter& operator=(const JSONwriter&);
        void* Writer;
        void* Stream;
    };
}
