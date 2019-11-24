#include<stdio.h>
#include<math.h>
int used[26];
int num[26];
int cont,zero;
int adj[400000][4],p,q;
//int symbol[100000000];
int symbol[400000];
//int ans[362800];
int size,foo;
int pattern;

void swap(int *p,int *q){
    int temp;
    temp=*p;
    *p=*q;
    *q=temp;}

void PrintBit(int n){
    int i,m=0x80000000;
    for(i=1;i<=32;i++){
        if(n&m) printf("1");
        else printf("0");
        n=n<<1;
        if((i-5)%3==0) printf(" ");
    }
    printf("\n");
}


void func(int n){
    int i,j,zero;
    foo=0;
    for(i=0;i<n;i++){
        foo=foo*10+num[i]+1;}
}



void encode(int n){
    int i,j,zero,adjc=0;
    for(i=0;i<n;i++){
        //printf("%d",num[i]);
        if(num[i]==0) zero=i;}
    //printf("\n");
    func(n);
    symbol[cont]=foo;
    //printf("%d %d\n",foo,cont);
    //PrintBit(foo);
    p=zero/size;
    q=zero%size;

    if(p>0){
        swap(&num[zero],&num[(p-1)*size+q]);
        func(n);
        adj[cont][adjc]=foo;
        adjc++;
        swap(&num[zero],&num[(p-1)*size+q]);}
    if(p<size-1){
        swap(&num[zero],&num[(p+1)*size+q]);
        func(n);
        adj[cont][adjc]=foo;
        adjc++;
        swap(&num[zero],&num[(p+1)*size+q]);}
    if(q>0){
        swap(&num[zero],&num[(p)*size+q-1]);
        func(n);
        adj[cont][adjc]=foo;
        adjc++;
        swap(&num[zero],&num[(p)*size+q-1]);}
    if(q<size-1){
        swap(&num[zero],&num[(p)*size+q+1]);
        func(n);
        adj[cont][adjc]=foo;
        adjc++;
        swap(&num[zero],&num[(p)*size+q+1]);}
    if(adjc<4) adj[cont][adjc]=-1;
    //printf(" %d",foo);
    //printf("\n");
}


void permutations(int index,int n){
    int i,j;
    if(index==n){
     //   for(i=0;i<n;i++) printf("%d",num[i]);
     //   printf("\n");
        encode(n);
        cont++;
        return;}

    for(i=0;i<n;i++){
        if(used[i]==0){
            used[i]=1;
            num[index]=i;
            permutations(index+1,n);
            used[i]=0;
        }
    }
}



int visited[400000],i,j;
int front=0,last=0,u,w,pos1,pos2,pos3;


int binary_search(int n,int size,int prob[]){
    int low=0;
    int high=size-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(n>prob[mid]) low=mid+1;
        else if(n<prob[mid]) high=mid-1;
        else if(n==prob[mid]) return mid;
    }
    return -1;
}

int linear_search(int n,int size,int prob[]){
    for(i=0;i<size;i++){
        if(prob[i]==n) return i;}
        return -1;
}

int encoded[400000];
struct state{
    int parent;
    int distance;
};

struct state v[400000];

void push(int n){
    encoded[last]=n;
    last++;
}

void pop(){
    front++;}

int empty(){
    if(last==front) return 1;
    else return 0;}

void bfs(){
    push(pattern);
    pos1=binary_search(pattern,362880,symbol);
    visited[pos1]=1;
    v[0].distance=0;
    v[0].parent=0;

    while(!empty()){
        u=encoded[front];
        pos2=binary_search(u,362880,symbol);
        for(i=0;i<4 && adj[pos2][i]!=-1;i++){
            w=adj[pos2][i];
            pos3=binary_search(w,362880,symbol);
            if(visited[pos3]==0){
                visited[pos3]=1;
                v[last].parent=u;
                v[last].distance=v[front].distance+1;
                push(w);
                //printf("%d\n",encoded[last-1]);
            }
        }
        pop();
    }
}


int backtrack(int init){
    if(init==pattern) return 0;
    else{
        int a=linear_search(init,181440,encoded);
        //printf("%d\n",a);
        backtrack(v[a].parent);
        //printf("%d\n",init);
        }
}

int main(){
    int n,g,h,count=0;
    pattern=123456789;
    scanf("%d",&n);

    size=sqrt(n);
    freopen("output.txt","w",stdout);
    permutations(0,n);

/*
    printf("%d\n",symbol[234566]);
    printf("%d\n",adj[234566][0]);
    printf("%d\n",adj[234566][1]);
    printf("%d\n",adj[234566][2]);
    printf("%d\n",adj[234566][3]);
*/

    bfs();
    for(i=0;i<last;i++) printf("%d %d\n",encoded[i],v[i].distance);
    //printf("%d",binary_search(pattern));
    //backtrack(123456789);
    //for(i=0;i<last;i++) printf("%d %d %d\n",encoded[i],v[i].parent,v[i].distance);
    //printf("%d\n",encoded[150]);
    //printf("%d %d",front,last);
    /*while(1){
        printf("%d\n",init);
        if(init==pattern) break;

        int a=binary_search(init,181440,encoded);
        init=v[a].parent;
    }*/

    //printf("%d",linear_search(init,last,encoded));
}
