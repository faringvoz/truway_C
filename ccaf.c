
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curl/curl.h>

int msleep(unsigned long milisec)   
{   
    struct timespec req={0};   
    time_t sec=(int)(milisec/1000);   
    milisec=milisec-(sec*1000);   
    req.tv_sec=sec;   
    req.tv_nsec=milisec*1000000L;   
    while(nanosleep(&req,&req)==-1)   
        continue;   
    return 1;   
}  

int main(void)
{	
	char cfl[6];
	char s[3]="10";
	int vs,i;
	snprintf(cfl, sizeof cfl, "%f", 34.12);
	for(i=1;i<6;i++){
		char dataT [60]= "{ \"timestamp\": \"2018-02-11T10:";
		strcat (dataT,s);
		strcat (dataT,":00.789Z\", \"value\": ");
		strcat (dataT, cfl);
		strcat (dataT, " }");
		vs = atoi (s);
		vs = vs+3;
		sprintf(s, "%d", vs);
		printf(" %s\n",dataT);

		CURL *curl;
		CURLcode res;
		struct curl_slist *headerlist=NULL;

		curl = curl_easy_init();
		if(curl) {

			curl_easy_setopt(curl, CURLOPT_URL, "https://api-m2x.att.com/v2/devices/da7f2862f07def7fe55ceba340ca17fa/streams/temperature/value");
			headerlist = curl_slist_append(headerlist, "X-M2X-KEY: d549d6e3654bbca4f4ee7e5d6babb4f9");
			headerlist = curl_slist_append(headerlist, "Content-Type: application/json");
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, dataT );

			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
		}
 		msleep(3000);
		
	}
	return 0;
}
