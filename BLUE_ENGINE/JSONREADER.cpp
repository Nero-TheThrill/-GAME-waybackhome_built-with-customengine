/*
*  File Name : JSONREADER.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Make easy to load/save objects.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include"JSONREADER.h"
#include <iostream>
#include "filereadstream.h"
#include <stack>
#include "TestLevel1.h"
#include "error/en.h"
#include "error/error.h"
#include "document.h"
#include "TreeController.h"
#include "SeedController.h"
#include "RustKeyController.h"
#include "BoxController.h"
#include "LogController.h"
#include "RiverController.h"
#include "Portal.h"
#include "WallController.h"
#include "WallController1.h"
#include "WallController2.h"
#include "WallController3.h"
#include "SpikeController.h"
#include "Archiver.h"
#include "AxeController.h"
#include "BlastFurnaceController.h"
#include "PoisonplantController.h"
#include "DoorController.h"
#include "Credit.h"
#include "VineController.h"
#include "WoodBoardController.h"
#include "TorchController.h"
#include "PuddleController.h"

namespace rapidjson
{
    struct JsonReaderStackItem {
        enum State {
            BeforeStart,    //!< An object/array is in the stack but it is not yet called by StartObject()/StartArray().
            Started,        //!< An object/array is called by StartObject()/StartArray().
            Closed          //!< An array is closed after read all element, but before EndArray().
        };

        JsonReaderStackItem(const Value* value, State state) : value(value), state(state), index() {}

        const Value* value;
        State state;
        SizeType index;   // For array iteration
    };

    typedef std::stack<JsonReaderStackItem> JsonReaderStack;

    //  JSONreader* JSONREADER = nullptr;
#define DOCUMENT reinterpret_cast<Document*>(document)
#define STACK (reinterpret_cast<JsonReaderStack*>(Stack))
#define TOP (STACK->top())
#define CURRENT (*TOP.value)
    JSONreader::JSONreader(const char* json) : document(), Stack(), Error(false) {
        document = new Document;
        DOCUMENT->Parse(json);
        if (DOCUMENT->HasParseError())
        {
            fprintf(stderr, "\nError(offset %u): %s\n",
                (unsigned)DOCUMENT->GetErrorOffset(),
                GetParseError_En(DOCUMENT->GetParseError()));
            Error = true;
        }
        else {
            Stack = new JsonReaderStack;
            STACK->push(JsonReaderStackItem(DOCUMENT, JsonReaderStackItem::BeforeStart));
        }
    }
    JSONreader::~JSONreader() {
        delete DOCUMENT;
        delete STACK;
    }

    // Archive concept
    JSONreader& JSONreader::StartObject() {
        if (!Error) {
            if (CURRENT.IsObject() && TOP.state == JsonReaderStackItem::BeforeStart)
                TOP.state = JsonReaderStackItem::Started;
            else
                Error = true;
        }
        return *this;
    }

    JSONreader& JSONreader::EndObject() {
        if (!Error) {
            if (CURRENT.IsObject() && TOP.state == JsonReaderStackItem::Started)
                Next();
            else
                Error = true;
        }
        return *this;
    }

    JSONreader& JSONreader::Member(const char* name) {
        if (!Error) {
            if (CURRENT.IsObject() && TOP.state == JsonReaderStackItem::Started) {
                Value::ConstMemberIterator memberItr = CURRENT.FindMember(name);
                if (memberItr != CURRENT.MemberEnd())
                    STACK->push(JsonReaderStackItem(&memberItr->value, JsonReaderStackItem::BeforeStart));
                else
                    Error = true;
            }
            else
                Error = true;
        }
        return *this;
    }

    bool JSONreader::HasMember(const char* name) const {
        if (!Error && CURRENT.IsObject() && TOP.state == JsonReaderStackItem::Started)
            return CURRENT.HasMember(name);
        return false;
    }

    JSONreader& JSONreader::StartArray(size_t* size) {
        if (!Error) {
            if (CURRENT.IsArray() && TOP.state == JsonReaderStackItem::BeforeStart) {
                TOP.state = JsonReaderStackItem::Started;
                if (size)
                    *size = CURRENT.Size();

                if (!CURRENT.Empty()) {
                    const Value* value = &CURRENT[TOP.index];
                    STACK->push(JsonReaderStackItem(value, JsonReaderStackItem::BeforeStart));
                }
                else
                    TOP.state = JsonReaderStackItem::Closed;
            }
            else
                Error = true;
        }
        return *this;
    }

    JSONreader& JSONreader::EndArray() {
        if (!Error) {
            if (CURRENT.IsArray() && TOP.state == JsonReaderStackItem::Closed)
                Next();
            else
                Error = true;
        }
        return *this;
    }

    JSONreader& JSONreader::operator&(bool& b) {
        if (!Error) {
            if (CURRENT.IsBool()) {
                b = CURRENT.GetBool();
                Next();
            }
            else
                Error = true;
        }
        return *this;
    }

    JSONreader& JSONreader::operator&(unsigned& u) {
        if (!Error) {
            if (CURRENT.IsUint()) {
                u = CURRENT.GetUint();
                Next();
            }
            else
                Error = true;
        }
        return *this;
    }

    JSONreader& JSONreader::operator&(int& i) {
        if (!Error) {
            if (CURRENT.IsInt()) {
                i = CURRENT.GetInt();
                Next();
            }
            else
                Error = true;
        }
        return *this;
    }

#ifdef _WIN64
    JSONreader& JSONreader::operator&(size_t& u)
    {
        if (!Error) {
            if (CURRENT.IsUint()) {
                u = CURRENT.GetUint();
                Next();
            }
            else
                Error = true;
        }
        return *this;
    }
#endif

    JSONreader& JSONreader::operator&(double& d) {
        if (!Error) {
            if (CURRENT.IsNumber()) {
                d = CURRENT.GetDouble();
                Next();
            }
            else
                Error = true;
        }
        return *this;
    }


    JSONreader& JSONreader::operator&(std::string& s) {
        if (!Error) {
            if (CURRENT.IsString()) {
                s = CURRENT.GetString();
                Next();
            }
            else
                Error = true;
        }
        return *this;
    }

    void JSONreader::InitializeAudio()
    {
        size_t arrsize = 0;
        StartObject();
        std::string type;
        Member("ArrayName") & type;
        if (type == "AudioArray")
        {
            Member("ArraySize")& arrsize;
            Member("Audio");
            StartArray(&arrsize);
            for (size_t i = 0; i < arrsize; i++)
            {
                StartObject();
                std::string audiopath;
                std::string audioname;
                bool loop;
                bool startpause;
                Member("AudioPath") & audiopath;
                Member("AudioName") & audioname;
                Member("AudioLoop") & loop;
                Member("AudioStartpause") & startpause;
                AUDIO_MANAGER->CreateSound(audiopath.c_str(), audioname, loop, startpause);
            }
        }
    }

    void JSONreader::InitializeObject()
    {
        size_t arrsize = 0;
        StartObject();
        std::string type;
        Member("ArrayName") & type;
        if (type == "ObjectArray")
        {
            Member("ArraySize")& arrsize;
            Member("Objects");
            StartArray(&arrsize);
            for (size_t i = 0; i < arrsize; i++)
            {
                double x, y, z;
                int current_state;
                StartObject();
                std::string objname;
                Member("ObjectName") & objname;
                Member("ObjectTranslationX") & x;
                Member("ObjectTranslationY") & y;
                Member("ObjectTranslationZ") & z;
                Member("CurrentState") & current_state;
                if (objname == "Tree")
                {
                    BLUE::TreeController* tree = new BLUE::TreeController();
                    tree->Spawn(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
                    BLUE::OBJECT_CONTROLLER->AddController(tree);
                    if (static_cast<BLUE::CurrentState>(current_state) == BLUE::PAST)
                    {
                        tree->ChangeToPast(true);
                    }
                    else if (static_cast<BLUE::CurrentState>(current_state) == BLUE::FUTURE)
                    {
                        tree->ChangeToFuture(true);
                    }
                }
                if (objname == "Seed")
                {
                    BLUE::SeedController* seed = new BLUE::SeedController();
                    seed->Spawn(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
                    BLUE::OBJECT_CONTROLLER->AddController(seed);
                    if (static_cast<BLUE::CurrentState>(current_state) == BLUE::PAST)
                    {
                        seed->ChangeToPast(true);
                    }
                    else if (static_cast<BLUE::CurrentState>(current_state) == BLUE::FUTURE)
                    {
                        seed->ChangeToFuture(true);
                    }
                }
                if (objname == "Key")
                {
                    BLUE::RustKeyController* key = new BLUE::RustKeyController();
                    key->Spawn(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
                    BLUE::OBJECT_CONTROLLER->AddController(key);
                    if (static_cast<BLUE::CurrentState>(current_state) == BLUE::PAST)
                    {
                        key->ChangeToPast(true);
                    }
                    else if (static_cast<BLUE::CurrentState>(current_state) == BLUE::FUTURE)
                    {
                        key->ChangeToFuture(true);
                    }
                }
                if (objname == "Box")
                {
                    BLUE::BoxController* box = new BLUE::BoxController();
                    box->Spawn(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
                    BLUE::OBJECT_CONTROLLER->AddController(box);
                    if (static_cast<BLUE::CurrentState>(current_state) == BLUE::PAST)
                    {
                        box->ChangeToPast(true);
                    }
                    else if (static_cast<BLUE::CurrentState>(current_state) == BLUE::FUTURE)
                    {
                        box->ChangeToFuture(true);
                    }
                }
                if (objname == "Log")
                {
                    BLUE::LogController* log = new BLUE::LogController();
                    log->Spawn(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
                    BLUE::OBJECT_CONTROLLER->AddController(log);
                    if (static_cast<BLUE::CurrentState>(current_state) == BLUE::PAST)
                    {
                        log->ChangeToPast(true);
                    }
                    else if (static_cast<BLUE::CurrentState>(current_state) == BLUE::FUTURE)
                    {
                        log->ChangeToFuture(true);
                    }
                }
                if (objname == "River")
                {
                    BLUE::RiverController* river = new BLUE::RiverController();
                    river->Spawn(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
                    BLUE::OBJECT_CONTROLLER->AddController(river);
                    if (static_cast<BLUE::CurrentState>(current_state) == BLUE::PAST)
                    {
                        river->ChangeToPast(true);
                    }
                    else if (static_cast<BLUE::CurrentState>(current_state) == BLUE::FUTURE)
                    {
                        river->ChangeToFuture(true);
                    }
                }
                if (objname == "Portal")
                {
                    BLUE::Portal* portal = new BLUE::Portal();
                    portal->Spawn(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
                    BLUE::OBJECT_CONTROLLER->AddController(portal);
                    if (static_cast<BLUE::CurrentState>(current_state) == BLUE::PAST)
                    {
                        portal->ChangeToPast(true);
                    }
                    else if (static_cast<BLUE::CurrentState>(current_state) == BLUE::FUTURE)
                    {
                        portal->ChangeToFuture(true);
                    }
                }
                if (objname == "Wall")
                {
                    double width, height;
                    Member("ObjectScaleX") & width;
                    Member("ObjectScaleY") & height;
                    BLUE::Wall* wall = new BLUE::Wall();
                    wall->Spawn(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
                    wall->SetWallScale(static_cast<float>(width), static_cast<float>(height));
                    BLUE::OBJECT_CONTROLLER->AddController(wall);
                    if (static_cast<BLUE::CurrentState>(current_state) == BLUE::PAST)
                    {
                        wall->ChangeToPast(true);
                    }
                    else if (static_cast<BLUE::CurrentState>(current_state) == BLUE::FUTURE)
                    {
                        wall->ChangeToFuture(true);
                    }
                }
				if (objname == "Wall1")
				{
					double width, height;
					Member("ObjectScaleX") & width;
					Member("ObjectScaleY") & height;
					BLUE::Wall1* wall = new BLUE::Wall1();
					wall->Spawn(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
					wall->SetWall1Scale(static_cast<float>(width), static_cast<float>(height));
					BLUE::OBJECT_CONTROLLER->AddController(wall);
					if (static_cast<BLUE::CurrentState>(current_state) == BLUE::PAST)
					{
						wall->ChangeToPast(true);
					}
					else if (static_cast<BLUE::CurrentState>(current_state) == BLUE::FUTURE)
					{
						wall->ChangeToFuture(true);
					}
				}
				if (objname == "Wall2")
				{
					double width, height;
					Member("ObjectScaleX") & width;
					Member("ObjectScaleY") & height;
					BLUE::Wall2* wall = new BLUE::Wall2();
					wall->Spawn(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
					wall->SetWall2Scale(static_cast<float>(width), static_cast<float>(height));
					BLUE::OBJECT_CONTROLLER->AddController(wall);
					if (static_cast<BLUE::CurrentState>(current_state) == BLUE::PAST)
					{
						wall->ChangeToPast(true);
					}
					else if (static_cast<BLUE::CurrentState>(current_state) == BLUE::FUTURE)
					{
						wall->ChangeToFuture(true);
					}
				}
				if (objname == "Wall3")
				{
					double width, height;
					Member("ObjectScaleX") & width;
					Member("ObjectScaleY") & height;
					BLUE::Wall3* wall = new BLUE::Wall3();
					wall->Spawn(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
					wall->SetWall3Scale(static_cast<float>(width), static_cast<float>(height));
					BLUE::OBJECT_CONTROLLER->AddController(wall);
					if (static_cast<BLUE::CurrentState>(current_state) == BLUE::PAST)
					{
						wall->ChangeToPast(true);
					}
					else if (static_cast<BLUE::CurrentState>(current_state) == BLUE::FUTURE)
					{
						wall->ChangeToFuture(true);
					}
				}
                if (objname == "Spike")
                {
                    BLUE::SpikeController* spike = new BLUE::SpikeController();
                    spike->Spawn(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
                    BLUE::OBJECT_CONTROLLER->AddController(spike);
                    if (static_cast<BLUE::CurrentState>(current_state) == BLUE::PAST)
                    {
                        spike->ChangeToPast(true);
                    }
                    else if (static_cast<BLUE::CurrentState>(current_state) == BLUE::FUTURE)
                    {
                        spike->ChangeToFuture(true);
                    }
                }
                if (objname == "Axe")
                {
                    BLUE::AxeController* axe = new BLUE::AxeController();
                    axe->Spawn(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
                    BLUE::OBJECT_CONTROLLER->AddController(axe);
                    if (static_cast<BLUE::CurrentState>(current_state) == BLUE::PAST)
                    {
                        axe->ChangeToPast(true);
                    }
                    else if (static_cast<BLUE::CurrentState>(current_state) == BLUE::FUTURE)
                    {
                        axe->ChangeToFuture(true);
                    }
                }
                if (objname == "BlastFurnace")
                {
                    BLUE::BlastFurnaceController* blastfurnace = new BLUE::BlastFurnaceController();
                    blastfurnace->Spawn(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
                    BLUE::OBJECT_CONTROLLER->AddController(blastfurnace);
                    if (static_cast<BLUE::CurrentState>(current_state) == BLUE::PAST)
                    {
                        blastfurnace->ChangeToPast(true);
                    }
                    else if (static_cast<BLUE::CurrentState>(current_state) == BLUE::FUTURE)
                    {
                        blastfurnace->ChangeToFuture(true);
                    }
                }
                if (objname == "PoisonPlant")
                {
                    double dirx, diry;
                    Member("ObjectDirectionX") & dirx;
                    Member("ObjectDirectionY") & diry;
                    BLUE::PoisonplantController* poisonplant = new BLUE::PoisonplantController();
                    poisonplant->Spawn(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), glm::vec2(dirx, diry));
                    BLUE::OBJECT_CONTROLLER->AddController(poisonplant);
                    if (static_cast<BLUE::CurrentState>(current_state) == BLUE::PAST)
                    {
                        poisonplant->ChangeToPast(true);
                    }
                    else if (static_cast<BLUE::CurrentState>(current_state) == BLUE::FUTURE)
                    {
                        poisonplant->ChangeToFuture(true);
                    }
                }
                if (objname == "Door")
                {
                    double ctype;
                    Member("ObjectItemType") & ctype;
                    BLUE::DoorController* door = new BLUE::DoorController();
                    door->Spawn(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
                    door->SetItemType(static_cast<BLUE::ControllerType>(static_cast<int>(ctype)));
                    BLUE::OBJECT_CONTROLLER->AddController(door);
                    if (static_cast<BLUE::CurrentState>(current_state) == BLUE::PAST)
                    {
                        door->ChangeToPast(true);
                    }
                    else if (static_cast<BLUE::CurrentState>(current_state) == BLUE::FUTURE)
                    {
                        door->ChangeToFuture(true);
                    }
                }
                if (objname == "Vine")
                {
                    BLUE::VineController* vine = new BLUE::VineController();
                    vine->Spawn(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
                    BLUE::OBJECT_CONTROLLER->AddController(vine);
                    if (static_cast<BLUE::CurrentState>(current_state) == BLUE::PAST)
                    {
                        vine->ChangeToPast(true);
                    }
                    else if (static_cast<BLUE::CurrentState>(current_state) == BLUE::FUTURE)
                    {
                        vine->ChangeToFuture(true);
                    }
                }
				if (objname == "WoodBoard")
				{
					BLUE::WoodBoardController* board = new BLUE::WoodBoardController();
					board->Spawn(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
					BLUE::OBJECT_CONTROLLER->AddController(board);
					if (static_cast<BLUE::CurrentState>(current_state) == BLUE::PAST)
					{
						board->ChangeToPast(true);
					}
					else if (static_cast<BLUE::CurrentState>(current_state) == BLUE::FUTURE)
					{
						board->ChangeToFuture(true);
					}
				}
				if (objname == "Torch")
				{
					BLUE::TorchController* torch = new BLUE::TorchController();
					torch->Spawn(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
					BLUE::OBJECT_CONTROLLER->AddController(torch);
					if (static_cast<BLUE::CurrentState>(current_state) == BLUE::PAST)
					{
						torch->ChangeToPast(true);
					}
					else if (static_cast<BLUE::CurrentState>(current_state) == BLUE::FUTURE)
					{
						torch->ChangeToFuture(true);
					}
				}
				if (objname == "Puddle")
				{
					BLUE::PuddleController* puddle = new BLUE::PuddleController();
					puddle->Spawn(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
					BLUE::OBJECT_CONTROLLER->AddController(puddle);
					if (static_cast<BLUE::CurrentState>(current_state) == BLUE::PAST)
					{
						puddle->ChangeToPast(true);
					}
					else if (static_cast<BLUE::CurrentState>(current_state) == BLUE::FUTURE)
					{
						puddle->ChangeToFuture(true);
					}
				}
                EndObject();
            }
            EndArray();
        }
        EndObject();
    }




    JSONreader& JSONreader::SetNull() {
        // This function is for JsonWriter only.
        Error = true;
        return *this;
    }

    void JSONreader::Next() {
        if (!Error) {
            assert(!STACK->empty());
            STACK->pop();

            if (!STACK->empty() && CURRENT.IsArray()) {
                if (TOP.state == JsonReaderStackItem::Started) { // Otherwise means reading array item pass end
                    if (TOP.index < CURRENT.Size() - 1) {
                        const Value* value = &CURRENT[++TOP.index];
                        STACK->push(JsonReaderStackItem(value, JsonReaderStackItem::BeforeStart));
                    }
                    else
                        TOP.state = JsonReaderStackItem::Closed;
                }
                else
                    Error = true;
            }
        }
    }


}

#undef DOCUMENT
#undef STACK
#undef TOP
#undef CURRENT