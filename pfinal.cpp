#include <bits/stdc++.h>
#include <pthread.h>

using namespace std;

float summ;

pthread_mutex_t lockk;

typedef struct node
{
    int a, b, id;
} node;

void *go(void *p)
{
    node *x = (node *)p;
    float sum = 0;
    for (int i = x->a; i < x->b; i++)
    {
        float temp = 1.00 / (2 * i + 1);
        if (i % 2)
            temp *= -1;
        sum += temp;
    }
    sum *= 4;

    pthread_mutex_lock(&lockk);
    summ += sum;
    pthread_mutex_unlock(&lockk);

    printf("sum calculated from thread %d is %.10f\n", x->id, sum);
}

int main()
{
    pthread_mutex_init(&lockk, NULL);
    int num_of_thread, n;
    pthread_t *thread;
    printf("Number of thread: ");
    scanf("%d", &num_of_thread);

    printf("Number of term: ");
    scanf("%d", &n);

    node tmp[num_of_thread];
    int per_thread = n / num_of_thread;
    summ = 0;
    //int extra = n%num_of_thread;
    //printf("%d\n", per_thread);
    thread = (pthread_t *)malloc(num_of_thread * sizeof(pthread_t));

    int l = 0;
    for (int i = 0; i < num_of_thread; i++)
    {
        tmp[i].a = l;
        l = tmp[i].b = tmp[i].a + per_thread;
        tmp[i].id = i;
        pthread_create(&thread[i], NULL, go, (void *)(&tmp[i]));
    }

    for (int i = 0; i < num_of_thread; i++)
        pthread_join(thread[i], NULL);

    printf("Value of pi: %.10f\n", summ);
    free(thread);
    pthread_mutex_destroy(&lockk);
    return 0;
}