#include "csapp.h"
//클라이언트와 통신하는 함수 echo 설정
void echo(int connfd);

int main(int argc, char **argv)
{
    int listenfd, connfd; //리스닝 소켓과 연결된 클라이언트 소켓 디스크립터 설정
    socklen_t clientlen; //클라이언트의 주소 길이로, 컴퓨터는 이걸 통해 주소를 판단할 수 있다.
    struct sockaddr_storage clientaddr; //클라이언트의 주소 정보를 저장하는 구조체
    char client_hostname[MAXLINE], client_port[MAXLINE]; //클라이언트 호스트 이름과 포트 번호 저장

    if (argc != 2){ //프로그램 실행 시 포트 번호를 인자로 입력하지 않은 경우
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(0);
    }

    listenfd = Open_listenfd(argv[1]); //주어진 포트 번호로 리스닝 소켓 열어서 파일 디스크립터 얻음
    while(1){
        clientlen = sizeof(struct sockaddr_storage); //클라이언트 주소 길이 초기화
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen); //클라이언트와 연결 받아들이고, 연결된 클라이언트 소켓 파일 디스크립터 얻음
        Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);//클라이언트 호스트 네임과 포트 번호 얻기
        printf("Connected to (%s, %s)\n", client_hostname, client_port);//출력
        echo(connfd); //에코 함수 실행
        Close(connfd); // 소켓 닫기
    }
    exit(0);
}
