#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#define MAX 20
#define PORT 43454
#define SA struct sockaddr
void func(int sockfd)
{
char buff[MAX];
int ipclass, validity[10], dot[10], k=0, g=0, c=0, h=0, check=0, range, t, i;
char ipcs[20]="", ip[MAX], ipcopy[40]="", class[1], hostID[30]="",hosts[20]="", netID[20]="", ntfo[10]="", defaultmask[20];
int n,clen;
struct sockaddr_in cli;
clen=sizeof(cli);


bzero(ip,MAX);
recvfrom(sockfd,ip,sizeof(ip),0,(SA *)&cli,&clen);


strcpy(ipcopy,ip);
char * token = strtok(ip, ".");
    
    while(token != NULL) 
    {
        sscanf(token,"%d",&t);
        validity[g++]=t;
        token = strtok(NULL, ".");
    }
    
    if(g==4)
    {
        for(i=0;i<4;i++)
        {
            if(validity[i]>=0 && validity[i]<=255)
            check++;
            else
            {
                check=0;
                break;
            }
        }
    }
    else
    {
        check=0;
    }

    if(check==4)
    {
        char val[MAX]="VALID IP";
        sendto(sockfd,val,sizeof(val),0,(SA *)&cli,sizeof(cli));
	bzero(val,MAX);
        
        for(i=0;i<strlen(ipcopy);i++)
        {
            if(ipcopy[i]=='.')
            {
                dot[k++]=i;
            }
        }

        ipclass=validity[0];
        if(ipclass<128)
        {
            class[0]='A';
            strcpy(defaultmask,"255.0.0.0");
            h=dot[0]+1;
            strcpy(ntfo,"0.0.0");
            strcpy(hosts,"16777214");
            
        }
        if(ipclass>127 && ipclass<192)
        {
            class[0]='B';
            strcpy(defaultmask,"255.255.0.0");
            h=dot[1]+1;
            strcpy(ntfo,"0.0");
            strcpy(hosts,"65534");
            
        }
        if(ipclass>191 && ipclass<224)
        {
            class[0]='C';
            strcpy(defaultmask,"255.255.255.0");
            h=dot[2]+1;
            strcpy(ntfo,"0");
            strcpy(hosts,"254");
            
        }
        if(ipclass>223 && ipclass<240)
        {
            class[0]='D';
            strcpy(defaultmask,"not defined");
            strcpy(hosts,"not defined");
            h=-1;
        }
        if(ipclass>239 && ipclass<256)
        {
            class[0]='E';
            strcpy(defaultmask,"not defined");
            strcpy(hosts,"not defined");
            h=-1;
        }	
	
	sendto(sockfd,class,sizeof(class),0,(SA *)&cli,sizeof(cli));
	bzero(class,1);

        sendto(sockfd,defaultmask,sizeof(defaultmask),0,(SA *)&cli,sizeof(cli));
	bzero(defaultmask,20);
        
        if(h==-1)
        { char a[40] = "Starting Address: not defined\n";
        char b[30] = "HostID: not defined\n";
            
            sendto(sockfd,a,sizeof(a),0,(SA *)&cli,sizeof(cli));
	bzero(a,40);
            
            sendto(sockfd,b,sizeof(b),0,(SA *)&cli,sizeof(cli));
	bzero(b,30);
	sendto(sockfd,hosts,sizeof(hosts),0,(SA *)&cli,sizeof(cli));
	bzero(hosts,20);
        }
        else
        {
            memset(netID, '\0', sizeof(netID));
            strncpy(netID, ipcopy, h);
            sendto(sockfd,netID,sizeof(netID),0,(SA *)&cli,sizeof(cli));
	bzero(netID,20);
	sendto(sockfd,ntfo,sizeof(ntfo),0,(SA *)&cli,sizeof(cli));
	bzero(ntfo,10);
            while (c<strlen(ipcopy)) 
            {
              hostID[c] = ipcopy[h+c];
              c++;
            }
        hostID[c] = '\0';
        sendto(sockfd,hostID,sizeof(hostID),0,(SA *)&cli,sizeof(cli));
	bzero(hostID,30);
	sendto(sockfd,hosts,sizeof(hosts),0,(SA *)&cli,sizeof(cli));
	bzero(hosts,20);
        }
    }
    else{
    char val[MAX]="INVALID IP";
    sendto(sockfd,val,sizeof(val),0,(SA *)&cli,sizeof(cli));
    bzero(val,MAX);
    }


}
int main()
{
int sockfd;
struct sockaddr_in servaddr;
sockfd=socket(AF_INET,SOCK_DGRAM,0);
if(sockfd==-1)
{
printf("socket creation failed...\n");
exit(0);
}
else
printf("Socket successfully created..\n");
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(PORT);
if((bind(sockfd,(SA *)&servaddr,sizeof(servaddr)))!=0)
{
printf("socket bind failed...\n");
exit(0);
}
else
printf("Socket successfully binded..\n");
func(sockfd);
close(sockfd);
}
