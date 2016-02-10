#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
int jepoll_create(int expected_fd);
int jepoll_wait(int fds[],int epfd,int max_events,int max_wait_time);
int jepoll_ctl_add(int fds[],int evnts[],int no_of_fds,int epfd);
int jepoll_ctl_add(int fds[],int evnts[],int no_of_fds,int epfd){
    struct epoll_event event;
    int i;
    for (i = 0; i < no_of_fds; i++) {
        event.data.fd=fds[i];
        event.events=evnts[i];
        epoll_ctl (epfd, EPOLL_CTL_ADD, fds[i], &event);
    }
}



int jepoll_create(int expected_fd){
    int epfd=epoll_create(expected_fd);
    return epfd;
}
int jepoll_wait(int fds[],int epfd,int max_events,int max_wait_time){
    struct epoll_event events[max_events];

    int nr_events=epoll_wait (epfd, events, max_events, max_wait_time);
    int i;
    for (i = 0; i < nr_events; i++) {
            fds[i]=events[i].data.fd;
    }
    return nr_events;
}
void hello(){
    printf("%s\n","hello world" );
}
