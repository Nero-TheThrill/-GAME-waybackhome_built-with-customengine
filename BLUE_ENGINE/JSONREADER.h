/*
*  File Name : JSONREADER.h
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Make easy to load/save objects. 
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include <string>

namespace rapidjson
{
    class JSONreader
    {
    public:
        JSONreader(const char* json);
        ~JSONreader();
        operator bool() const { return !Error; }

        JSONreader& StartObject();
        JSONreader& Member(const char* name);
        bool HasMember(const char* name) const;
        JSONreader& EndObject();

        JSONreader& StartArray(size_t* size = 0);
        JSONreader& EndArray();

        JSONreader& operator&(bool& b);
        JSONreader& operator&(unsigned& u);
        JSONreader& operator&(int& i);
#ifdef _WIN64
        JSONreader& operator&(size_t& u);
#endif
        JSONreader& operator&(double& d);
        JSONreader& operator&(std::string& s);

        void InitializeAudio();

        void InitializeObject();

        JSONreader& SetNull();

        static const bool IsReader = true;
        static const bool IsWriter = !IsReader;
    private:
        JSONreader(const JSONreader&);
        JSONreader& operator=(const JSONreader&);
        void Next();
        void* document;              ///< DOM result of parsing.
        void* Stack;                 ///< Stack for iterating the DOM
        bool Error;                  ///< Whether an error has occurred.

    };
}
