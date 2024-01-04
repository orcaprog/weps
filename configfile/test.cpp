#include <iostream>
#include <cstring>
#include <sys/epoll.h>
#include <unistd.h>

int main() {
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        return 1;
    }

    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event) == -1) {
        perror("epoll_ctl");
        return 1;
    }

    struct epoll_event events[10];
    int num_events = epoll_wait(epoll_fd, events, 10, -1);
    if (num_events == -1) {
        perror("epoll_wait");
        return 1;
    }

    for (int i = 0; i < num_events; ++i) {
        if (events[i].events & EPOLLIN) {
            std::cout << "Read event on stdin" << std::endl;
        }
    }

    close(epoll_fd);
    return 0;
}
