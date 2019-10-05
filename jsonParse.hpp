#include <iostream>
using namespace std;
/**
 * 拼接int
 */
std::string getKeyValue(std::string sKey, int iValue)
{
    char szDoubleQutoes[] = "\"";
    char szColon[] = ":";
    char szValue[50] = { 0 };

    std::string strResult;

    strResult.append(szDoubleQutoes);
    strResult.append(sKey);
    strResult.append(szDoubleQutoes);

    strResult.append(szColon);
    sprintf(szValue, "%d", iValue);
    strResult.append(szValue);

    return strResult;
}
/**
 * 拼接float，保留3位
 */
std::string getKeyValue(std::string sKey, float fValue)
{
    char szDoubleQutoes[] = "\"";
    char szColon[] = ":";
    char szValue[50] = { 0 };

    std::string strResult;

    strResult.append(szDoubleQutoes);
    strResult.append(sKey);
    strResult.append(szDoubleQutoes);

    strResult.append(szColon);
    sprintf(szValue, "%0.3f", fValue);
    strResult.append(szValue);

    return strResult;
}
/**
 * 拼接string
 */
std::string getKeyValue(std::string sKey, std::string sValue)
{
    char szDoubleQutoes[] = "\"";
    char szColon[] = ":";
    std::string strResult;

    strResult.append(szDoubleQutoes);
    strResult.append(sKey);
    strResult.append(szDoubleQutoes);

    strResult.append(szColon);
    strResult.append(szDoubleQutoes);
    strResult.append(sValue);
    strResult.append(szDoubleQutoes);

    return strResult;
}

/**
 * 拼接object
 */
std::string getKeyValueObject(std::string sKey, std::string sObject)
{
    char szDoubleQutoes[] = "\"";
    char szColon[] = ":";
    std::string strResult;

    strResult.append(szDoubleQutoes);
    strResult.append(sKey);
    strResult.append(szDoubleQutoes);

    strResult.append(szColon);
    strResult.append(sObject);

    return strResult;
}
/**
 * 拼接array
 */
std::string getKeyValueArray(std::string sKey, std::string sArray)
{
    char szDoubleQutoes[] = "\"";
    char szColon[] = ":";
    std::string strResult;

    strResult.append(szDoubleQutoes);
    strResult.append(sKey);
    strResult.append(szDoubleQutoes);

    strResult.append(szColon);
    strResult.append("[");
    strResult.append(sArray);
    strResult.append("]");

    return strResult;
}


// {
//     "imageGateTagCode": "35027277001320300007",
//     "appIdentityKey": "1234567890",
//      "imageJsonData": "{ 
//             "deviceID": "35027277001320300007", 
//             "localTime": "20181011202545", 
//             "deviceTime": "20181011202544",
//              "locationName": "", 
//              "resolutionRatio": "176X212", 
//              "longitude": "0", "latitude": "0",
//              "qualityGrane": "", 
//              "faceImages": [
//                             { 
//                                 "type": "jpg", 
//                                 "content": "人脸图片",
//                                 "facePos":
//                                     {  
//                                         "leftTopX": 22, 
//                                         "leftTopY": 60, 
//                                         "rightBottomX": 117, 
//                                         "rightBottomY": 155 } 
//                             }
//                         ],
//              "backgroundImage": { 
//                  "type": "jpg",
//                  "content": "背景图片",
//                  "width": 1920, 
//                 "height": 1080 
//                 } 
//         }"
// }

// int main() 
// {
//     int value1 = 1;
//     float value2 = 1.0f;
//     std::string strJsonResult("{");
//     strJsonResult.append(getKeyValue("imageGateTagCode",  "35027277001320300007")); 
//     strJsonResult.append(",");
//     strJsonResult.append(getKeyValue("appIdentityKey", "1234567890"));
//     strJsonResult.append(",");

//     std::string imageJsonData("{");
//     imageJsonData.append(getKeyValue("deviceID",  "35027277001320300007")); 
//     imageJsonData.append(",");
//     imageJsonData.append(getKeyValue("localTime", "20181011202545"));
//     imageJsonData.append(",");
//     imageJsonData.append(getKeyValue("deviceTime","20181011202544")); 
//     imageJsonData.append(",");
//     imageJsonData.append(getKeyValue("locationName",""));
//     imageJsonData.append(",");
//     imageJsonData.append(getKeyValue("resolutionRatio","176X212")); 
//     imageJsonData.append(",");
//     imageJsonData.append(getKeyValue("longitude","0"));
//     imageJsonData.append(",");
//     imageJsonData.append(getKeyValue("latitude","0"));
//     imageJsonData.append(",");
//     imageJsonData.append(getKeyValue("qualityGrane","")); 
//     imageJsonData.append(",");

//     std::string facesInfo("{");
//     facesInfo.append(getKeyValue("type","jpg"));
//     facesInfo.append(",");
//     facesInfo.append(getKeyValue("content","背景图片"));
//     facesInfo.append(",");
//     std::string  facePos("{");
//     facePos.append(getKeyValue("leftTopX",22)); 
//     facePos.append(",");
//     facePos.append(getKeyValue("leftTopY", 60));
//     facePos.append(",");
//     facePos.append(getKeyValue("rightBottomX",117)); 
//     facePos.append(",");
//     facePos.append(getKeyValue("lrightBottomY",155));
//     facePos.append("}");
//     facesInfo.append(getKeyValueObject("facePos", facePos));
//     facesInfo.append("}");

//     imageJsonData.append(getKeyValueArray("faceImages",facesInfo)); 
//     imageJsonData.append(",");

//     std::string backgroundImage("{");
//     backgroundImage.append(getKeyValue("type","jpg"));
//     backgroundImage.append(",");
//     backgroundImage.append(getKeyValue("content","背景图片"));
//     backgroundImage.append(",");
//     backgroundImage.append(getKeyValue("width",1920));
//     backgroundImage.append(",");
//     backgroundImage.append(getKeyValue("height",1080 ));
//     backgroundImage.append("}");

//     imageJsonData.append(getKeyValueObject("backgroundImage", backgroundImage));
//     imageJsonData.append("}");
//     strJsonResult.append(getKeyValueObject("imageJsonData", imageJsonData));


//     strJsonResult.append("}");
//     cout<<strJsonResult<<endl;
// }