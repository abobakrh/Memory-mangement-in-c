#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
char replacement_approach [200];
int Frame_num = 0;
int page_count = 0;
int pages[200];
int i = 0;
int pagefault_index;
int flag = 0;
int x = 0;
int fr = 0;
// queue implementation
struct Queue
{
    int front, rear, size;
    unsigned capacity;
    int* array;
};

// function to create a queue of given capacity.
// It initializes size of queue as 0
struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;  // This is important, see the enqueue
    queue->array = (int*) malloc(queue->capacity * sizeof(int));
    return queue;
}

// Queue is full when size becomes equal to the capacity
int isFull(struct Queue* queue)
{  return (queue->size == queue->capacity);  }

// Queue is empty when size is 0
int isEmpty(struct Queue* queue)
{  return (queue->size == 0); }

// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue* queue, int item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)%queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    //printf("%d enqueued to queue\n", item);
}

// Function to remove an item from queue.
// It changes front and size
int dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1)%queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Function to get front of queue
int front(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->front];
}

// end of queue implementation



void initialize(int fr_arr[],int fcount)
{
    int i = 0;
    for(i=0;i<fcount;i++)
        fr_arr[i] = -1 ;

}

void print_array(int arr[],int counter)
{
    size_t n = counter;
    int j = 0;


    if(flag == 1) printf("%02d F   ",pages[x++]);
    else printf("%02d     ",pages[x++]);
    for(j=0;j<n;j++)
    {
        if(arr[j] != -1)
        printf("%02d ",arr[j]);
        else printf("");
    }
    printf("\n");



}

int frame_search(int fr_arr[],int fcount,int d)
{
    int i = 0;
    int found = 0;
    for(i=0;i<fcount;i++)
    {
        if(fr_arr[i] == d)
        {
            found = 1;
            break;
        }

    }
    return found ;
}

int hasroom(int arr[],int arr_count)
{
    int i  = 0;
    int hasrooms = 0;
    for(i=0;i<arr_count;i++)
    {
        if(arr[i] == -1)
        {
           hasrooms = 1 ;
            break;
        }
    }
    return hasrooms;
}

int index_finder(int fr_arr[],int fcount,int key)
{
    int i = 0;
    int f = -1;
    for(i=0;i<fcount;i++)
    {
        if(key == fr_arr[i])
        {
            f = i ;
        }
    }
    return f ;
}

void fifo(struct Queue* queue,int fr_arr[],int fcount)
{
    int index = 0;
    int pagefault = 0;
    int u = 0;
    for(i=0;i<page_count;i++)
    {

        if(frame_search(fr_arr,fcount,pages[i]) == 0 && hasroom(fr_arr,fcount) == 1)  //if i didn't find the page among the frames
        {
            //printf("page %d gdida w fih mkan w i dlw2ty b %d \n",pages[i],i);
            if(fr > fcount-1)
            {
                fr = 0;
            }
            fr_arr[fr++] = pages[i];
            int yu = fr-1;
            enqueue(queue,fr_arr[yu]);
            flag = 0;
            print_array(fr_arr,fcount);
        }
        else if(frame_search(fr_arr,fcount,pages[i]) == 0 && hasroom(fr_arr,fcount) == 0) // if there is not place left in frames and element is new then we replace the oldest
        {

            index = index_finder(fr_arr,fcount,front(queue));
            dequeue(queue);
            fr_arr[index] = pages[i];
            enqueue(queue,fr_arr[index]);
            pagefault++;
            flag = 1;
            print_array(fr_arr,fcount);
        }
        else
        {
            //printf("page %d mwgoda m4 h3ml 7aga \n",pages[i]);
            flag = 0;
            print_array(fr_arr,fcount);
        }
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",pagefault);
}

int optimal_replace(int fr_arr[],int fcount,int start_index)
{
    int maximum_index = -1; // basecase not found
    int i = 0 ;
    int k = 0 ;
    int flag1 = 0;
    int highest = -1;
    for(i=0;i<fcount;i++)
    {
        flag1 = 0;

        for(k=start_index+1;k<page_count;k++)
        {

            if(fr_arr[i] == pages[k])
            {
                flag1 = 1; // found the frame element among the pages if this is zero then it wasn't found
                if(k > highest)
                {
                   highest = k;
                   maximum_index = i;
                }
                break;
            }
             // find nearest index of element to replace of 1st frame element then jump to second frame element get nearest and so on
        }

        if(flag1 == 0)
        {
            maximum_index = i;
            break;
        }
             // if the frame wasn't going to be used again replace it

    }
    return maximum_index;
}

void optimal(int fr_arr[],int fcount)
{

    int i = 0 ;
    for(i=0;i<page_count;i++)
    {

        if(frame_search(fr_arr,fcount,pages[i]) == 0 && hasroom(fr_arr,fcount) == 1)
        {

            if(fr > fcount-1) {fr = 0;}
            fr_arr[fr++] = pages[i];
            flag = 0;
            print_array(fr_arr,fcount);
        }
        else if (frame_search(fr_arr,fcount,pages[i]) == 0 && hasroom(fr_arr,fcount) == 0)
        {
            //replacement

            int t = optimal_replace(fr_arr,fcount,i);

            fr_arr[t] = pages[i];
            pagefault_index++;
            flag = 1;
            print_array(fr_arr,fcount);
        }
        else
        {

            flag = 0;
            print_array(fr_arr,fcount);
        }
    }
     printf("-------------------------------------\n");
     printf("Number of page faults = %d\n",pagefault_index);
}

int lru_replace(int fr_arr[],int fcount,int start_index)
{
    int flag1 = 0;
    int i = 0;
    int k = 0;
    int distancearray[200];
    int minimum = 9999999999;
    int index_toreplace ;
    for(i=0;i<fcount;i++)
    {
        flag1 = 0;
        for(k=start_index-1;k>=0;k--)
        {
            if(pages[k] == fr_arr[i])
            {
                distancearray[i] = k;
                flag1 = 1;
                break;
            }
            else
            {
                flag1 = 0;
            }
        }
        if(flag1 == 0)
            distancearray[i] = -1 ; // not found
    }
    for(i=0;i<fcount;i++)
    {
        if(distancearray[i] < minimum)
        {
            minimum = distancearray[i];
            index_toreplace = i;
        }
    }

    return index_toreplace;
}



void LRU(int fr_arr[],int fcount)
{

    int i = 0 ;
    for(i=0;i<page_count;i++)
    {

        if(frame_search(fr_arr,fcount,pages[i]) == 0 && hasroom(fr_arr,fcount) == 1)
        {
            //printf("page %d gdida w fih mkan \n",pages[i]);
            if(fr > fcount-1) {fr = 0;}
            fr_arr[fr++] = pages[i];
            flag = 0;
            print_array(fr_arr,fcount);
        }
        else if (frame_search(fr_arr,fcount,pages[i]) == 0 && hasroom(fr_arr,fcount) == 0)
        {
            //replacement

            int t = lru_replace(fr_arr,fcount,i);
            //printf("page %d gdida bs mfii4 mkan h7otha f frame %d\n",pages[i],t);
            fr_arr[t] = pages[i];
            pagefault_index++;
            flag = 1;
            print_array(fr_arr,fcount);
        }
        else
        {
            //printf("page %d mwgoda m4 h3ml 7aga \n",pages[i]);
            flag = 0;
            print_array(fr_arr,fcount);
        }
    }
     printf("-------------------------------------\n");
     printf("Number of page faults = %d\n",pagefault_index);
}


int main()
{
    scanf("%d",&Frame_num);
    int frame_arr[Frame_num];
    initialize(frame_arr,Frame_num);
    scanf("%s",&replacement_approach);
    int y ;
    scanf("%d",&y);
    while(y != -1)
    {
        pages[page_count++] = y;
        scanf("%d",&y);
    }
    struct Queue* queue = createQueue(200);

    if(!strcmp(replacement_approach,"FIFO"))
        {
            fputs("Replacement Policy = FIFO",stdout);
            printf("\n");
            printf("-------------------------------------\n");
            printf("Page   Content of Frames\n");
            printf("----   -----------------\n");
            fifo(queue,frame_arr,Frame_num);
        }


    else if(!strcmp(replacement_approach,"OPTIMAL"))
        {
            fputs("Replacement Policy = OPTIMAL",stdout);
            printf("\n");
            printf("-------------------------------------\n");
            printf("Page   Content of Frames\n");
            printf("----   -----------------\n");
            optimal(frame_arr,Frame_num);
        }

    else if(!strcmp(replacement_approach,"LRU"))
        {
            fputs("Replacement Policy = LRU",stdout);
            printf("\n");
            printf("-------------------------------------\n");
            printf("Page   Content of Frames\n");
            printf("----   -----------------\n");
            LRU(frame_arr,Frame_num);
        }

    else if(!strcmp(replacement_approach,"CLOCK"))
        {

        }

    else
    {
        printf("wrong choice exiting...\n");
        exit(1);
    }
    return 0;
}
