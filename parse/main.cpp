#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <json/json.h>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <string>
#include <cstring>
#include <map>

using namespace std;

const string help = "Usage:\nparse audio";

typedef map<string,string> metaData;
typedef shared_ptr<metaData> MetaData;

static MetaData parse(const char *buf) {
    string org(buf);
    metaData *pdata = new metaData;
    boost::regex pattern("([a-z]+)\\s+:\\s(.*?)\\n");
    boost::smatch matches;
    
    std::string::const_iterator s = org.begin();
    std::string::const_iterator e = org.end();
    
    while (boost::regex_search(s, e, matches, pattern)) {
        (*pdata)[matches.str(1)] = matches.str(2);
        s = matches[2].second;
    }
    
    pattern.assign("Duration:\\s(.*?),\\sstart:\\s(.*?),\\sbitrate:\\s(.*?)\\n.+?Audio:\\s(.*?)\\n");
    
    s = org.begin();
    e = org.end();
    
    while (boost::regex_search(s, e, matches, pattern)) {
        (*pdata)["duration"] = matches.str(1);
        (*pdata)["start"] = matches.str(2);
        (*pdata)["bitrate"] = matches.str(3);
        (*pdata)["audio"] = matches.str(4);
        s = matches[4].second;
    }
    
    return MetaData(pdata);
}

int main(int argc, char *argv[]) {
    try {
        if (argc != 2) {
            cout << help << endl;
            exit(0);
        }
        
        string audio = boost::filesystem::system_complete(boost::filesystem::path(argv[1])).string();
        string command("ffmpeg -i ");
        command.append(audio);
        command.append(" 2>&1");
        
        FILE *pf = nullptr;
        char buffer[1024 * 5];
        memset(buffer, 0, sizeof(buffer));
        
#if defined (WIN32) || defined (_WIN32)
        pf = _popen(command.c_str(), "r");
#elif defined (linux)||defined (__linux__)
        pf = popen(command.c_str(), "r");
#endif
        if (!pf) {
            throw logic_error("cannot access ffmpeg");
        }
        
        fread(buffer, sizeof(char), sizeof(buffer), pf);
        
#if defined (WIN32) || defined (_WIN32)
        _pclose(pf);
#elif defined (linux)||defined (__linux__)
        pclose(pf);
#endif 
        pf = nullptr;       
        
        MetaData dataset = parse(buffer);
        Json::Value json;
        for(metaData::const_iterator it = dataset->cbegin();
            it != dataset->cend(); ++it){
            json[(*it).first] = (*it).second;
        }
        Json::FastWriter writer;
        
        cout << writer.write(json);
        
    } catch (const std::exception &err) {
        cout << err.what() << endl;
    }
    
    return 0;
}
