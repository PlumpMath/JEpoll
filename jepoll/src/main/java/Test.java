import java.lang.reflect.Field;

/**
 * Created by suresh on 10/2/16.
 */
import jnr.ffi.LibraryLoader;
public class Test {
    public static interface LibC {
        int jepoll_create(int expected_fd);
        void hello();
        int jepoll_wait(int fds[],int epfd,int max_events,int max_wait_time);
        int jepoll_ctl_add(int fds[],int evnts[],int no_of_fds,int epfd);
    }

    public static void main(String[] args) {
        LibC libc = LibraryLoader.create(LibC.class).load("/home/suresh/codes/Git/JEpoll/JEpoll/libjepoll.so");
        System.out.println("calling epoll create");
        int epfd = libc.jepoll_create(10);
        System.out.println("calling epoll wait");
        int fds[]=new int[10];int evnts[]=new int[10];
        fds[0]=1;
        evnts[0]=0x004; //epollout
        libc.jepoll_ctl_add(fds, evnts, 1, epfd);
        System.out.println(libc.jepoll_wait(fds, epfd,10,5000)); //fds is now filled with ready files
        System.out.println("i am from java but data collected from c that is "+fds[0]);

    }

}
