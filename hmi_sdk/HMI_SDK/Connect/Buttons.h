﻿#ifndef BUTTONSCLIENT_H
#define BUTTONSCLIENT_H

#include "json/json.h"

#include "Connect/Channel.h"

class Buttons : public Channel
{
public:
    Buttons();
    ~Buttons();
public:
    void onRequest(Json::Value &);

private:
};

#endif // BUTTONSCLIENT_H
