/*
*  File Name : JSONWRITER.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Make easy to load/save objects. 
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include"JSONWRITER.h"
#include<iostream>
#include "filewritestream.h"
#include "prettywriter.h"


#define WRITER reinterpret_cast<PrettyWriter<StringBuffer>*>(Writer)
#define STREAM reinterpret_cast<StringBuffer*>(Stream)

namespace rapidjson
{
    JSONwriter::JSONwriter() : Writer(), Stream()
    {
        Stream = new StringBuffer;
        Writer = new PrettyWriter<StringBuffer>(*STREAM);
        std::cout << "JSONWRITER constructor called" << std::endl;
    }

    JSONwriter::~JSONwriter()
    {
        delete WRITER;
        delete STREAM;
    }

    void JSONwriter::WriteToFile(const std::string& path)
    {
        std::cout << "WIRTER" << std::endl;

        std::ofstream outStream(path, std::ios::app);
        outStream << STREAM->GetString() << std::endl;

        outStream.close();
    }

    void JSONwriter::ClearFile(const std::string& path)
    {
        std::ofstream outStream(path);
        outStream << "";

        outStream.close();
    }

    const char* JSONwriter::GetString() const {
        return STREAM->GetString();
    }

    JSONwriter& JSONwriter::StartObject() {
        WRITER->StartObject();
        return *this;
    }

    JSONwriter& JSONwriter::EndObject() {
        WRITER->EndObject();
        return *this;
    }

    JSONwriter& JSONwriter::Member(const char* name) {
        WRITER->String(name, static_cast<SizeType>(strlen(name)));
        return *this;
    }

    bool JSONwriter::HasMember(const char*) const {
        // This function is for JsonReader only.
        assert(false);
        return false;
    }

    JSONwriter& JSONwriter::StartArray(size_t*) {
        WRITER->StartArray();
        return *this;
    }

    JSONwriter& JSONwriter::EndArray() {
        WRITER->EndArray();
        return *this;
    }
    JSONwriter& JSONwriter::operator&(bool& b) {
        WRITER->Bool(b);
        return *this;
    }

    JSONwriter& JSONwriter::operator&(unsigned& u) {
        WRITER->Uint(u);
        return *this;
    }

    JSONwriter& JSONwriter::operator&(int& i) {
        WRITER->Int(i);
        return *this;
    }

    JSONwriter& JSONwriter::operator&(double d) {
        WRITER->Double(d);
        return *this;
    }

    JSONwriter& JSONwriter::operator&(std::string s) {
        WRITER->String(s.c_str(), static_cast<SizeType>(s.size()));
        return *this;
    }

    JSONwriter& JSONwriter::SetNull() {
        WRITER->Null();
        return *this;
    }
}

#undef STREAM
#undef WRITER