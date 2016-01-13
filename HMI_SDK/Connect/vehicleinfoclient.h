﻿#ifndef VEHICLEINFOCLIENT_H
#define VEHICLEINFOCLIENT_H

#include <json/json.h>

#include "ISocketManager.h"
#include "Channel.h"

class vehicleInfoClient : public Channel
{
public:
    vehicleInfoClient();
    ~vehicleInfoClient();
virtual ID_CHN_TYPE ChannelType(){return ID_CHN_VEHICLE;}
protected:
    void onRequest(Json::Value &);

private:
    bool getVehicleData(Json::Value &,Json::Value &result);
    Json::Value vehicleInfoGetDTCsResponse(Json::Value &);
    Json::Value vehicleInfoReadDIDResponse(Json::Value &);
    void SendGetVehicleDataResult(int id, Json::Value data);

};

#endif // VEHICLEINFOCLIENT_H
