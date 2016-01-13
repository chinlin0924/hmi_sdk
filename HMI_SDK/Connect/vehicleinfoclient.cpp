﻿#include <Include/global_first.h>
#include <Connect/vehicleinfoclient.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include "json/json.h"

vehicleInfoClient::vehicleInfoClient() : Channel(700,"VehicleInfo")
{

}

vehicleInfoClient::~vehicleInfoClient()
{

}


void vehicleInfoClient::onRequest(Json::Value &request)
{
    std::string method = request["method"].asString();
    int  id = request["id"].asInt();
    if(method == "VehicleInfo.SubscribeVehicleData")
    {
        sendResult(id,"SubscribeVehicleData");
    }
    else if(method == "VehicleInfo.UnsubscribeVehicleData")
    {
        sendResult(id,"UnsubscribeVehicleData");
    }
    else if(method == "VehicleInfo.GetVehicleType")
    {
        sendResult(id,"GetVehicleType");
    }
    else if(method == "VehicleInfo.IsReady")
    {
        sendResult(id,"IsReady");
    }
    else if(method == "VehicleInfo.GetVehicleData")
    {
        Json::Value result;
        if(getVehicleData(request,result)){
        }
        else{
            sendError(id,result);
        }
    }
    else if(method == "VehicleInfo.ReadDID")
    {
        Json::Value result = vehicleInfoReadDIDResponse(request);
        sendResult(id,result);
    }
    else if(method == "VehicleInfo.GetDTCs")
    {
        Json::Value result = vehicleInfoGetDTCsResponse(request);
        sendResult(id,result);
    }
    else
    {
        Channel::onRequest(request);
    }
}



bool vehicleInfoClient::getVehicleData(Json::Value &message,Json::Value &result)
{
    Json::Value vehicle;
    Json::Value data;
    Json::Value params;
    int id;
    bool ret = false;

    params = message["params"];
    id = message["id"].asInt();

    vehicle = g_VehicleInfoJson["vehicle"];

    Json::Value::Members mem = params.getMemberNames();
    for (Json::Value::Members::iterator iter = mem.begin(); iter != mem.end(); iter++)
    {
        std::string infoitem = std::string(*iter);
        if (infoitem != "appID" && infoitem != "request")
        {
            Json::Value require = params[infoitem];
            if (!require.isBool())
                continue;
            if (!require.asBool())
                continue;

            if (vehicle.isMember(infoitem))
                data[infoitem] = vehicle[infoitem];
            ret = true;
        }
    }

    if(ret){
        SendGetVehicleDataResult(id, data);
    }
    else{
        result["message"] = "Params rpc, are not avaliable";
        result["code"] = 9;
        result["method"]="VehicleInfo.GetVehicleData";
    }

    return ret;
}


void vehicleInfoClient::SendGetVehicleDataResult(int id, Json::Value data)
{
    Json::Value root;
    Json::Value result;

    root["id"] = id;
    root["jsonrpc"] = "2.0";
    Json::Value::Members mem = data.getMemberNames();
    for (Json::Value::Members::iterator iter = mem.begin(); iter != mem.end(); iter++)
    {
            std::string infoitem = std::string(*iter);
            result[infoitem] = data[infoitem];
    }

    result["code"] = 0;
    result["method"] = "VehicleInfo.GetVehicleData";
    root["result"] = result;

    SendJson(root);
}

Json::Value vehicleInfoClient::vehicleInfoReadDIDResponse(Json::Value &request)
{
    Json::Value did;
    Json::Value didLocation;
    didLocation = request["params"]["didLocation"];

    did = g_VehicleInfoJson["did"];
    int size = int(didLocation.size());

    Json::Value arrayObj;
    Json::Value item;

    for (int i = 0; i < size; i++)
    {
        item["data"] = did[0];
        item["didLocation"] = didLocation[i];
        item["resultCode"] = "SUCCESS";
        arrayObj.append(item);
    }

    Json::Value result;
    result["code"] = 0;
    result["method"] = "VehicleInfo.ReadDID";
    result["didResult"] = arrayObj;
    return result;
}

Json::Value vehicleInfoClient::vehicleInfoGetDTCsResponse(Json::Value &request)
{
    Json::Value dtc;
    dtc = g_VehicleInfoJson["dtc"];

    Json::Value result;
    result["code"] = 0;
    result["ecuHeader"] = 2;
    result["method"] = "VehicleInfo.GetDTCs";
    result["dtc"] = dtc;
    return result;
}
