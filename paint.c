#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct point {
    int x, y;
} point;

typedef struct queue {
    int start, end, size;
    point **velements;
} queue;

/****************************
* implement functions below *
****************************/

queue *new_queue(int size) {
    queue* q = (queue*) malloc(sizeof(queue));
    q->end=0;
    q->size=size;
    q->start=0;
    q->velements=(point**)malloc(size*sizeof(point*));
    return q;
}

void delete_queue(queue *q) {
    for(int i=q->start; i!=q->end; i++)
    {
        free(q->velements[i]);
    }
    free(q->velements);
    free(q);
}

void put(queue *q, point *value) {
    q->velements[q->end]=value;
    q->end = (q->end+1)%q->size;

}

point *get(queue *q) {

        point* result = q->velements[q->start];
        q->start=(q->start+1)%q->size;
        return result;

}

bool is_empty(queue *q) {
    if(q->end==q->start) return true;
    return false;
}

void fill(int **image, int n, int x, int y, int color) {
    queue *points = new_queue(n*n);
    point* ptmp = (point*)malloc(sizeof(point));
    ptmp->x=x;
    ptmp->y=y;
    put(points, ptmp);
    while (!is_empty(points)) {

        ptmp=get(points);
        x = ptmp->x;
        y = ptmp->y;
        free(ptmp);
        if(x>=0 && x<n && y>=0 && y<n && image[x][y]==0)
        {

             image[x][y]=color;

             ptmp  = (point*)malloc(sizeof(point));
             ptmp->x=x+1;
             ptmp->y=y;
             put(points, ptmp);

             ptmp  = (point*)malloc(sizeof(point));
             ptmp->x=x-1;
             ptmp->y=y;
             put(points, ptmp);

             ptmp  = (point*)malloc(sizeof(point));
             ptmp->x=x;
             ptmp->y=y+1;
             put(points, ptmp);

             ptmp  = (point*)malloc(sizeof(point));
             ptmp->x=x;
             ptmp->y=y-1;
             put(points, ptmp);

        }

    }
    delete_queue(points);
}

int main() {
    int n, k;
    scanf("%d", &n);
    scanf("%d", &k);

    int **image = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        image[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            scanf("%d", &image[i][j]);
        }
    }

    int x, y, color;
    for (int i = 0; i < k; i++) {
        scanf("%d", &x);
        scanf("%d", &y);
        scanf("%d", &color);
        fill(image, n, x, y, color);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", image[i][j]);
        }
        printf("\n");
        free(image[i]);
    }
    free(image);
}

