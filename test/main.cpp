#include <string>
#include <fstream>
#include <json/json.h>

int main() {
    using namespace Json;
    
    StyledWriter writer;
    
    Value urls;
    urls["recommend"] = "http://www.songtaste.com/music";
    urls["category"] = "http://www.songtaste.com/music/cat";
    urls["catsong"] = "http://songtaste.com/music/catsong";
    urls["album"] = "http://www.songtaste.com/music/abu";
    urls["chart"] = "http://www.songtaste.com/music/chart";
    
    Value regexs;
    regexs["recommend"] = "MSL\\(\"(.*?)\", \"(\\d+)\", \"(.*?)\\s\", \"(\\d+)\", \"(.*?)\", \"(\\d+)\", \"(\\d+)\", \"(.*?)\", \"(.*?)\\s\"\\);";
    regexs["categorylist"] = "WL\\(\"(\\d{0,})\",\"(\\d{0, })\", \"(.*?)\",\"(\\d+)\", \"(\\d+)\"\\);";
    regexs["catsong"] = "song/(\\d{0,})/\">(.*?)</a>.*?\\s(\\d{0,})\\s</div>";
    
    Value root;
    root["URLS"] = urls;
    root["REGEXS"] = regexs;
    //
    std::string json;
    json.reserve(200);
    json = writer.write(root);
    
    std::ofstream out("config.json");
    out << json;
    out.close();
    
    return 0;
}
