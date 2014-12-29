#include <string>
#include <fstream>
#include <json/json.h>

int main() {
    using namespace Json;
    
    StyledWriter writer;
    
    Value urls;
    urls["recommend"]   = "http://www.songtaste.com/music";
    urls["category" ]   = "http://www.songtaste.com/music/cat";
    urls["catsong"  ]   = "http://songtaste.com/music/catsong";
    urls["album"    ]   = "http://www.songtaste.com/music/abu";
    urls["chart"    ]   = "http://www.songtaste.com/music/chart";
    urls["down"     ]   = "http://songtaste.com/playmusic.php?song_id=";
    urls["time"     ]   = "http://songtaste.com/time.php";
    
    Value regexs;
    regexs["recommend"   ]  = "MSL\\(\"(.*?)\", \"(\\d+)\", \"(.*?)\\s\", \"(\\d+)\", \"(.*?)\", \"(\\d+)\", \"(\\d+)\", \"(.*?)\", \"(.*?)\\s\"\\);";
    regexs["categorylist"]  = "WL\\(\"(\\d{0,})\",\"(\\d{0, })\", \"(.*?)\",\"(\\d+)\", \"(\\d+)\"\\);";
    regexs["catsong"     ]  = "song/(\\d{0,})/\">(.*?)</a>.*?\\s(\\d{0,})\\s</div>";
    regexs["down"        ]  = "WrtSongLine\\(\"(\\d+)\", \"(.*?)\", \"(.*?)\\s\", \"(\\d{0,})\", \"(\\d{0,})\", \"(.*?)\", \"(.*?)\"\\);";
    
    Value parse;
    parse["first"]  = "([a-z]+)\\s+:\\s(.*?)\\n";
    parse["second"] = "Duration:\\s(.*?),\\sstart:\\s(.*?),\\sbitrate:\\s(.*?)\\n.+?Audio:\\s(.*?)\\n";
    
    //
    Value root;
    root["urls"     ]  = urls;
    root["regexs"   ]  = regexs;
    root["parse"    ]  = parse;
    root["useragent"]  = "Mozilla/5.0 (Windows NT 6.3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2171.95 Safari/537.36";
    //
    std::string json;
    json.reserve(200);
    json = writer.write(root);
    
    std::ofstream out("config.json");
    out << json;
    out.close();
    
    return 0;
}
