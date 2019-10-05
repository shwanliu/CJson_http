#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "jsonParse.hpp"
#include <iostream>
using namespace std;

#define IPSTR "192.168.1.114"
#define PORT 19000
#define BUFSIZE 1024

int main(int argc, char **argv)
{
        int value1 = 1;
        float value2 = 1.0f;
        std::string strJsonResult("{");
        strJsonResult.append(getKeyValue("imageGateTagCode",  "35027277001320300007")); 
        strJsonResult.append(",");
        strJsonResult.append(getKeyValue("appIdentityKey", "1234567890"));
        strJsonResult.append(",");

        std::string imageJsonData("{");
        imageJsonData.append(getKeyValue("deviceID",  "35027277001320300007")); 
        imageJsonData.append(",");
        imageJsonData.append(getKeyValue("localTime", "20181011202545"));
        imageJsonData.append(",");
        imageJsonData.append(getKeyValue("deviceTime","20181011202544")); 
        imageJsonData.append(",");
        imageJsonData.append(getKeyValue("locationName",""));
        imageJsonData.append(",");
        imageJsonData.append(getKeyValue("resolutionRatio","176X212")); 
        imageJsonData.append(",");
        imageJsonData.append(getKeyValue("longitude","0"));
        imageJsonData.append(",");
        imageJsonData.append(getKeyValue("latitude","0"));
        imageJsonData.append(",");
        imageJsonData.append(getKeyValue("qualityGrane","")); 
        imageJsonData.append(",");

        std::string facesInfo("{");
        facesInfo.append(getKeyValue("type","jpg"));
        facesInfo.append(",");
        facesInfo.append(getKeyValue("content","背景图片"));
        facesInfo.append(",");
        std::string  facePos("{");
        facePos.append(getKeyValue("leftTopX",22)); 
        facePos.append(",");
        facePos.append(getKeyValue("leftTopY", 60));
        facePos.append(",");
        facePos.append(getKeyValue("rightBottomX",117)); 
        facePos.append(",");
        facePos.append(getKeyValue("lrightBottomY",155));
        facePos.append("}");
        facesInfo.append(getKeyValueObject("facePos", facePos));
        facesInfo.append("}");

        imageJsonData.append(getKeyValueArray("faceImages",facesInfo)); 
        imageJsonData.append(",");

        std::string backgroundImage("{");
        backgroundImage.append(getKeyValue("type","jpg"));
        backgroundImage.append(",");
        backgroundImage.append(getKeyValue("content","背景图片"));
        backgroundImage.append(",");
        backgroundImage.append(getKeyValue("width",1920));
        backgroundImage.append(",");
        backgroundImage.append(getKeyValue("height",1080 ));
        backgroundImage.append("}");

        imageJsonData.append(getKeyValueObject("backgroundImage", backgroundImage));
        imageJsonData.append("}");
        strJsonResult.append(getKeyValueObject("imageJsonData", imageJsonData));
        strJsonResult.append("}");



        int sockfd, ret, i, h;
        struct sockaddr_in servaddr;
        char str1[4096], str2[4096], buf[BUFSIZE], *str;
        socklen_t len;
        fd_set   t_set1;
        struct timeval  tv;
 
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
                printf("创建网络连接失败,本线程即将终止---socket error!\n");
                exit(0);
        };
 
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(PORT);
        if (inet_pton(AF_INET, IPSTR, &servaddr.sin_addr) <= 0 ){
                printf("创建网络连接失败,本线程即将终止--inet_pton error!\n");
                exit(0);
        };
 
        if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
                printf("连接到服务器失败,connect error!\n");
                exit(0);
        }
        printf("与远端建立了连接\n");

        memset(str2, 0, 4096);
        strcpy(str2, strJsonResult.c_str());
        str=(char *)malloc(128);
        len = strlen(str2);
        sprintf(str, "%d", len);

        memset(str1, 0, 4096);

        strcat(str1, "POST /redis/rest/face/saveImageData.json HTTP/1.1\n");

        strcat(str1, "Host: www.webxml.com.cn\n");
        strcat(str1, "Content-Type: application/json\n");
        strcat(str1, "Content-Length: ");
        strcat(str1, str);
        strcat(str1, "\n\n");

        strcat(str1, str2);
        strcat(str1, "\r\n\r\n");
        printf("%s\n",str1);
 
        ret = write(sockfd,str1,strlen(str1));
        if (ret < 0) {
                printf("发送失败！错误代码是%d，错误信息是'%s'\n",errno, strerror(errno));
                exit(0);
        }else{
                printf("消息发送成功，共发送了%d个字节！\n\n", ret);
        }
 
        FD_ZERO(&t_set1);
        FD_SET(sockfd, &t_set1);
 
        while(1){
                sleep(2);
                tv.tv_sec= 0;
                tv.tv_usec= 0;
                h= 0;
                printf("--------------->1");
                h= select(sockfd +1, &t_set1, NULL, NULL, &tv);
                printf("--------------->2");
 
                //if (h == 0) continue;
                if (h < 0) {
                        close(sockfd);
                        printf("在读取数据报文时SELECT检测到异常，该异常导致线程终止！\n");
                        return -1;
                };
 
                if (h > 0){
                        memset(buf, 0, 4096);
                        i= read(sockfd, buf, 4095);
                        if (i==0){
                                close(sockfd);
                                printf("读取数据报文时发现远端关闭，该线程终止！\n");
                                return -1;
                        }
 
                        printf("%s\n", buf);
                }
        }
        close(sockfd);
 
 
        return 0;
}