//
//  main.c
//  Multi Threading Test
//
//  Created by Hongjun Yun on 2020-07-16.
//  Copyright © 2020 Hongjun Yun. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
 
 
void* My(void* Para)
{
    int i;
    
    for(i=0;i<10;i++)
    {
        printf("I'm in thread \n");
        sleep(2);
    }
    return (void*)0;
}

int main()
{
    pthread_t child_thread;
    int thread_rst;
    void* s;

    thread_rst = pthread_create(&child_thread, NULL, My, NULL);
    
    while(1)
    {
        printf("I'm in main\n");
        
        sleep(1);
        pthread_join(child_thread, &s);
    }
    
    pthread_join(child_thread, &s);
    
    printf("%s\n",s);

    return 0;
}
