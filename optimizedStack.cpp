#include <bits/stdc++.h>
#include <pthread.h>
using namespace std;

// This is the main() for all your purposes
void* thread_function(void* arg) 
{
    // Write your main() here
    return NULL;
}

int main() 
{
    pthread_t thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    // Set the stack size (in bytes) here.
    size_t stack_size=1024*1024*1024;   // Replace the 1024 with how much MB you want the stack space
    pthread_attr_setstacksize(&attr, stack_size);
    if(pthread_create(&thread,&attr,thread_function,NULL)!=0) 
    {
        cerr<<"Error creating thread\n";
        return 1;
    }
    pthread_join(thread, NULL);
    pthread_attr_destroy(&attr);
    return 0;
}
