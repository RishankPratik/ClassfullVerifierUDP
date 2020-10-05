#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#define MAX 20
#define PORT 43454
#define SA struct sockaddr
int main()
{
char buff[MAX];
int ipclass, validity[10], dot[10], k=0, g=0, c=0, h=0, check=0, range, t, i;
char ipcs[20]="", ip[MAX], ipcopy[40]="", class[1], hosts[20]="", hostID[30]="", netID[20]="", ntfo[10]="", defaultmask[20];

int sockfd,len,n,r;
struct sockaddr_in servaddr,cli;
socklen_t servlen;

sockfd=socket(AF_INET,SOCK_DGRAM,0);
if(sockfd==-1)
{
printf("socket creation failed...\n");
exit(0);
}
else
printf("Socket successfully created..\n");
bzero(&servaddr,sizeof(len));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_port=htons(PORT);


len=sizeof(servaddr);


printf("Enter an IP Address: ");
scanf("%s",ip);
sendto(sockfd,ip,sizeof(ip),0,(SA *)&servaddr,len);


char val[MAX];
bzero(val,MAX);
recvfrom(sockfd,val,sizeof(val),0,(SA *)&servaddr,&len);
printf("%s\n",val);

bzero(class,1);
recvfrom(sockfd,class,sizeof(class),0,(SA *)&servaddr,&len);
printf("Class of %s is: %s \n",ip,class);
bzero(ip,sizeof(ip));

bzero(defaultmask,20);
recvfrom(sockfd,defaultmask,sizeof(defaultmask),0,(SA *)&servaddr,&len);
printf("Default Mask: %s\n",defaultmask);

if(class[0]=='D' || class[0]=='E')
{
char a[40]="",b[30]="";
bzero(a,40);
recvfrom(sockfd,a,sizeof(a),0,(SA *)&servaddr,&len);
printf("%s",a);
bzero(b,30);
recvfrom(sockfd,b,sizeof(b),0,(SA *)&servaddr,&len);
printf("%s",b);
bzero(hosts,20);
recvfrom(sockfd,hosts,sizeof(hosts),0,(SA *)&servaddr,&len);
printf("Number of hosts: %s\n",hosts);
}
else if(class[0]=='A' || class[0]=='B' || class[0]=='C')
{
bzero(netID,20);
recvfrom(sockfd,netID,sizeof(netID),0,(SA *)&servaddr,&len);
bzero(ntfo,10);
recvfrom(sockfd,ntfo,sizeof(ntfo),0,(SA *)&servaddr,&len);
printf("Starting Address: %s%s\n",netID,ntfo);

bzero(hostID,30);
recvfrom(sockfd,hostID,sizeof(hostID),0,(SA *)&servaddr,&len);
printf("Host ID: %s\n",hostID);

bzero(hosts,20);
recvfrom(sockfd,hosts,sizeof(hosts),0,(SA *)&servaddr,&len);
printf("Number of Hosts: %s\n",hosts);
}
else
close(sockfd);
}
