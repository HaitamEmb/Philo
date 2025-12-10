// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>

// typedef struct mutarg
// {
// 	pthread_mutex_t mut;
// 	void *x;
// } t_mutarg ;

// void *anotherfunc(void *x)
// {
// 	t_mutarg *s = (t_mutarg *)(x);
// 	pthread_mutex_lock(&s->mut);
// 	int y = 5;
// 	int *xp = (int*)(&s->x);
// 	while (y--)
// 	{
// 		int *p = (int*)(s->x)++;	
// 		printf("%i\n", *p);
// 	}
// 	pthread_mutex_unlock(&s->mut);
// 	return NULL;
// }

// int main()
// {
// 	pthread_t thread1;
// 	pthread_t thread2;

// 	int a = 0;
// 	int b = 5;

// 	pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
// 	t_mutarg x = {mut, &a};
// 	t_mutarg y = {mut, &b};

// 	// pthread_mutex_init(&mut, NULL);

// 	pthread_create(&thread1, NULL, &anotherfunc, (void*) &x);
// 	pthread_create(&thread2, NULL, &anotherfunc, (void*) &y);
// 	pthread_join(thread1, NULL);
// 	pthread_join(thread2, NULL);

// 	pthread_mutex_destroy(&mut);
// }

#include <pthread.h>
#include <stdio.h>

typedef struct mutarg {
    pthread_mutex_t *mut;
    int *x;
} t_mutarg;

void *anotherfunc(void *arg) {
    t_mutarg *s = (t_mutarg *)arg;

    pthread_mutex_lock(s->mut);
    for (int i = 0; i < 5; i++) {
        (*s->x)++;
        printf("Value: %d\n", *s->x);
    }
    pthread_mutex_unlock(s->mut);

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    int a = 0;
    int b = 5;

    pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

    t_mutarg x = {&mut, &a};
    t_mutarg y = {&mut, &b};

    pthread_create(&thread1, NULL, anotherfunc, &x);
    pthread_create(&thread2, NULL, anotherfunc, &y);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mut);

    printf("Final a: %d\n", a);
    printf("Final b: %d\n", b);

    return 0;
}
