#include "csapp.h"
//argc = argument count로, 이 프로그램을 실행했을 때 전달되는 인수의 갯수
//즉 main()함수에 전달되는 데이터의 갯수를 의미한다.
//char *argv[]. char **argv
//이렇게 받는 이유는 argument가 TCP, IP, PORT, 총 3개이기 떄문이구나
//그러면 *argv[0]이 TCP *argv[1]이 IP, *argv[2]가 PORT를 가리키게됨.
int main(int argc, char **argv)
{
    int clientfd;
    char *host, *port, buf[MAXLINE];
    rio_t rio;

//파일 실행 시 인자 3개를 제대로 넘겨주지 않았을 경우 -> 오류 처리해주기
if (argc != 3) {
    fprintf(stderr, "usage: %s <host> <port> \n", argv[0]); //안내 메세지
    exit(0); //어플리케이션 종료
}
    host = argv[1]; // 두 번째 인자를 host에 저장
    port = argv[2]; // 세 번쨰 인자를 host에 저장

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);

    while (Fgets(buf, MAXLINE, stdin) != NULL) {
    Rio_writen(clientfd, buf, strlen(buf));
    Rio_readlineb(&rio, buf, MAXLINE);
    Fputs(buf, stdout);
    }
    Close(clientfd);
    exit(0);
}