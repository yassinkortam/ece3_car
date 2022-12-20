
#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif

/*
#ifndef ARXCONTAINER_H
#define ARXCONTAINER_H
#include <ArxContainer.h>
#endif
*/

//Creates a json object that can be converted to a string
class Json{
private:
    //arx::map <String, String> jsonData;
    String json = "{";
public:
    //Add key value pairs to the json object
    void push(String key, String value);
    //Remove key value pairs from the json object
    //void pop(String key);
    //Get the json string
    String stringify();
};

void Json::push(String key, String value){
    json += "\"" + key + "\":" + value + ",";
}

String Json::stringify(){
    json = json.substring(0, json.length() - 1);
    json += "}";
    return json;
}

/*
void Json::push(String key, String value){
    jsonData[key] = value;
}

void Json::pop(String key){
    jsonData.erase(key);
}

String Json::stringify(){
    json  = "{";
    for (int i = 0; i < jsonData.size(); i++) {
        json += "\"" + jsonData[i] + "\":\"" + jsonData[i] + "\"";
        if (i < jsonData.size() - 1) json += ',';
    }
    json += "}";
    return json;
}
*/