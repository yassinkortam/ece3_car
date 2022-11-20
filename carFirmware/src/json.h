#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif

#ifndef UNORDERED_MAP
#define UNORDERED_MAP
#include <unordered_map>
#endif

class Json{
private:
    unordered_map <String, String> jsonData;
    String json;
public:
    Json();
    void push(String key, String value);
    void pop(String key);
    String stringify();
}

void Json::push(String key, String value){
    jsonData[key] = value;
}

void Json::pop(String key){
    jsonData.erase(key);
}

String Json::stringify(){
    json  = "{";
    for (auto iter : jsonData)
        json += "\"" + iter->first + "\":" + iter->second + ",";
    json += "}";
    return json;
}
