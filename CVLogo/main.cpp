//
//  main.cpp
//  CVLogo
//
//  Created by 储仲尧 on 9/29/15.
//  Copyright © 2015 FUDAN. All rights reserved.
//

/*
#include "ViewController.h"
#include "VideoController.h"
#include "RandomFernsClassifier.h"
#include "NNClassifier.h"
#include "Detector.h"
#include "TLD.h"
#include "TLDSystemStruct.h"
#include "include/json.hpp"
#include "NetworkHandler.hpp"

using namespace std;
using namespace cv;

using json = nlohmann::json;

char *FETCH_NEW_TASKS_URL = "http://localhost:8080/VideoInfo/getfilmtaginfobystate.do?state=0";
char *GET_FILE_INFO_URL = "http://localhost:8080/VideoInfo/getmoviefilebyid.do";
char *POST_RESULTS_URL = "http://localhost:8080/VideoInfo/setfilmtag.do";
char *UPDATE_STATE_URL = "http://localhost:8080/VideoInfo/updatefilmtaginfobyid.do";

void track(json task) {
    // get file path
    string fileInfo;
    string url = string(GET_FILE_INFO_URL) + "?movie_file_id=";
    url += task["movieId"].get<string>();
    string _res;
    while(!net::get(url.c_str(), _res)) {
        sleep(5);
    }
    
    json res = json::parse(_res);
    string filename = res["filePath"];
    
    //    cerr << filename << endl;
    
    // track
    vector<json> results;
    
    VideoController videoController(filename);
    //    ViewController viewController(&videoController);
    
    videoController.jumpToFrameNum(task["adFrame"]);
    videoController.readNextFrame();
    
    Point2i inTl(task["adX"], task["adY"]);
    Point2i inBr(task["adX"].get<int>() + task["adWidth"].get<int>(), task["adY"].get<int>() + task["adHeight"].get<int>());
    Rect rect(inTl, inBr);
    
    //    cerr << "Input Rect : " <<  rect << endl;
    
    //    viewController.refreshCache();
    //    viewController.drawRect(rect, COLOR_BLUE);
    //    viewController.showCache();
    //    waitKey();
    
    TLD tld(videoController.getCurrFrame(), rect);
    
    int status = TLD_TRACK_SUCCESS;
    while(videoController.frameNumber() < 15 && status == TLD_TRACK_SUCCESS && videoController.readNextFrame())
    {
        cerr << "Frame #" << videoController.frameNumber() << endl;
        tld.setNextFrame(videoController.getCurrFrame());
        
        Rect bbTrack;
        TYPE_DETECTOR_RET bbDetect;
        
        clock_t st = clock();
        
        status = tld.track();
        
        clock_t ed = clock();
        cerr << "Time : " << (double)(ed - st) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
        
        //        viewController.refreshCache();
        //        viewController.drawRect(tld.getBB(), COLOR_GREEN, 2);
        //        viewController.showCache();
        
        results.push_back({
            {"adX", tld.getBB().tl().x},
            {"adY", tld.getBB().tl().y},
            {"adWidth", tld.getBB().width},
            {"adHeight", tld.getBB().height},
            {"adFrame", videoController.frameNumber() - 1}
        });
        
        cerr << endl;
    }
    
    //    cerr << results << endl;
    //    cerr << "list=" + json(results).dump() << endl;
    
    // POST result
    url = string(POST_RESULTS_URL) + "?ad_info_id=" + task["adInfoId"].get<string>();
    
    while(!net::post(url.c_str(), "list=" + json(results).dump())) {
        sleep(5);
    }
}

void updateState(string ad_info_id, char state) {
    string data = "";
    string url = string(UPDATE_STATE_URL) + "?" + "ad_info_id=" + ad_info_id + "&" + "state=" + state;
    //    cerr << url << " " << data << endl;
    
    while(!net::post(url.c_str(), data)) {
        sleep(5);
    }
}

void fetchNewTasks() {
    string _res;
    while(!net::get(FETCH_NEW_TASKS_URL, _res)) {
        sleep(5);
    }
    
    json res = json::parse(_res);
    
    for(auto task : res["list"]) {
        updateState(task["adInfoId"], '1');
        
        track(task);
        
        updateState(task["adInfoId"], '2');
    }
}

int main(int argc, char *argv[])
{
    //testOnTLDDataset();
    //testOnTLDDatasetAndOutputToFile();
    //    testOnVideo();
    //    testOnCamera();
    //trajectory();
    //stabilize();
    
    while(1) {
        fetchNewTasks();
        sleep(15);
    }
    return 0;
}
*/

#include <iostream>
#include <opencv2/opencv.hpp>
#include <curl/curl.h>

using namespace std;
using namespace cv;

int main(int argvs,char* argv[]){
    char* url;
    url="http://ivory.edwardchor.com/CVLogo/generator.php";
    CURL *curl;
    CURLcode res;
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL,url);
        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");
        /* Perform the request, res will get the return code */
        //res = curl_easy_perform(curl);
        curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        cout<<endl;
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}