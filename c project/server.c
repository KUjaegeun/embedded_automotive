#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#define BUFSIZ 200
char stage[5] = {'0','0','1','0','0'};
void start(int , int);

int main(int argc,char**argv){
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;

	int srvfd,clntfd[2]={-1,-1},clntlen[2],counting=0;
	char rBuff1[BUFSIZ],rBuff2[BUFSIZ],wBuff[BUFSIZ],mapBuff[BUFSIZ]={'2','0'};
	struct sockaddr_in srvAddr,userAddr[2];
	memset(rBuff1,0,sizeof(rBuff1));
	memset(rBuff2,0,sizeof(rBuff2));
	printf("2p %c\n",rBuff2[0]);
	srvfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(srvfd == -1)printf("fd error\n");
	printf("srvfd pass\n");//
	memset(&srvAddr,0,sizeof(srvAddr));
	srvAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	srvAddr.sin_family=AF_INET;
	srvAddr.sin_port=htons(atoi(argv[1]));

	if(bind(srvfd,(struct sockaddr*)&srvAddr,sizeof(srvAddr))==-1)
		printf("bind error\n");
	printf("bind pass\n");
	if(listen(srvfd,5)<0)
		printf("listen error\n");
	printf("listen pass\n");
	for(int i=0;i<2;i++) clntlen[i]=sizeof(userAddr[i]);
	while(1)
	{
		printf("%d waiting\n",counting+1);
		if(clntfd[counting]==-1){
			printf("if error pass\n");
			clntfd[counting]=accept(srvfd,(struct sockAddr*)&userAddr[counting],&clntlen[counting]);
		}
		printf("accept pass\n");
		if(clntfd[counting]==-1){
			printf("연결실패");
			continue;
		}
		send(clntfd[counting],0,1,0);
		if(setsockopt(clntfd[counting],SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv))<0)
			printf("타임설정 실패\n");
		counting++;
		if(counting==2)break;
		printf("%d connected\n",counting);

	}
	printf("start before\n");
	printf("2p %c\n",rBuff2[0]);
	while(1){
		if(rBuff1[0] != '8'){
			send(clntfd[0],"1",1,0);
			printf("send함\n");
			recv(clntfd[0],rBuff1,sizeof(rBuff1),0);
			printf("1p %c\n",rBuff1[0]);
			printf("2p가짜  %c\n",rBuff2[0]);
		}
		if(rBuff2[0] !='8'){
			printf("2p send전\n");
			send(clntfd[1],"1",1,0);
			printf("2p send후\n");
			recv(clntfd[1],rBuff2,sizeof(rBuff2),0);
			printf("2p %c\n",rBuff2[0]);
		}
		if(rBuff1[0] == '8' && rBuff2[0] == '8'){
			printf("빠져나간다~~\n");
			break;
		}
	}
	start(clntfd[0],clntfd[1]);
	printf("초기 좌표값 전송 완료\n");
	tv.tv_sec = 0;
	tv.tv_usec = 400;
	for(int i = 0 ;i<2;i++)
		setsockopt(clntfd[i],SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));
	while(1){//시작
		memset(rBuff1,0,sizeof(rBuff1));
		memset(rBuff2,0,sizeof(rBuff2));
		recv(clntfd[0],rBuff1,sizeof(rBuff1),0);
		printf("rBuff1[0] = %c \n",rBuff1[0]);
		recv(clntfd[1],rBuff2,sizeof(rBuff2),0);
		printf("rBuff2[0] = %c \n",rBuff2[0]);
		//player1
		if(rBuff1[0] == '0'){
			printf("2번에게 키입력 전달 전\n");
			send(clntfd[1],rBuff1,sizeof(rBuff1),0);
			printf("2번에게 키입력 전달 성공\n");
		}
		else if(rBuff1[0] == '1'){
			printf("test\n");
			if(rBuff1[1] =='1' && rBuff1[2] == '1'){
				printf("1번이 이겼다.\n");
				for(int i=0;i<5;i++){
					if(stage[i] == '1' && i!=4){
						stage[i] = '0';
						stage[i+1] = '1';
						break;
					}
					else if(stage[4] == '1'){
						stage[4] = '0';
					}
				}
				for(int i = 0; i<5; i++){
					mapBuff[i+2] = stage[i];
					printf("%c ", mapBuff[i+2]);
				}
				for(int i = 0; i<2; i++)
					send(clntfd[i],mapBuff,sizeof(mapBuff),0);
			}
		
		}
		//player2
		if(rBuff2[0] == '0'){
			printf("1번에게 전송 전\n");
			send(clntfd[0],rBuff2,sizeof(rBuff2),0);
			printf("1번에게 전송성공\n");
		}
		else if(rBuff2[0] == '1'){
			if(rBuff2[1] == '1' && rBuff2[2] == '2'){
				printf("2번이 이겼다.\n");
				for(int i =0;i<5;i++){
					if(stage[i] == '1'&&i!=0){
						stage[i] = '0';
						stage[i-1] = '1';
						break;
					}
					else if(stage[0] == '1'){
						stage[0] = '0';
					}	
				}
			}
			for(int i=0;i<5;i++) {
				mapBuff[i+2] = stage[i];
				printf("%c ",mapBuff[i+2]);
				}
			for(int i=0;i<2;i++)
				send(clntfd[i],mapBuff,sizeof(mapBuff),0);
		}
	}	
		
		
}	
void start(int clntfd1,int clntfd2){
	char startx[BUFSIZ];
	char readBuff1[BUFSIZ],readBuff2[BUFSIZ];
	memset(readBuff1,0,sizeof(readBuff1));
	memset(readBuff2,0,sizeof(readBuff2));
	while(1){
	printf("스타트 진입\n");
	startx[0] = '3';
	printf("memcpy error\n");
	send(clntfd1,startx,1,0);	
	startx[0] = '4';
	send(clntfd2,startx,1,0);
	recv(clntfd1,readBuff1,1,0);
	recv(clntfd2,readBuff2,1,0);
	printf("readBuff1:%c \n",readBuff1[0]);
	printf("readBuff2:%c \n",readBuff2[0]);
	if(readBuff1[0] == 'a' && readBuff2[0] == 'b'){
		break;
	}
	}
}
