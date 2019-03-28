#include <iostream>
#include <jsoncpp/json/json.h>

using namespace std;


int main(void)
{
    Json::Value obj;
    Json::Value arr;
    Json::Value root;

    obj["1"] = "hello ";
    arr.append(obj);
    
    obj = "world ";
    arr.append(obj);
    
    obj = "hi ";
    arr.append(obj);
    
    obj = "world";
    arr.append(obj);

    root["introduce"] = arr;
    root["name"] = "lidawei";
    root["99"] = "I 99 years old";
//    root.append(arr);     // error!!, 'root' is not a json array
    
    string str = root.toStyledString();
    cout << root << endl;
    cout << str << endl;

    Json::FastWriter writer;
    std::string out = writer.write(root);
    cout << out << endl;

    cout << "---------------------------------------------------" << endl;

    Json::Reader reader;
    Json::Value res;
    if(false == reader.parse(out, res)) {
        cout << "parse [" << out << "] failed " << endl;
        return 0;
    }
    cout << "parse [" << out << "] success " << endl;
    cout << writer.write(res) << endl;

    return 0;
}
