#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <time.h>
typedef unsigned long long lint;
struct TreeNode
{
    /* data */
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};
typedef struct TreeNode Node;
//阶乘数组，存住，运行一次 
lint *Mul(lint len){
    lint *mulNum = NULL;
    mulNum = (lint*)malloc(sizeof(lint)*len);
    mulNum[0] = 1;
    for(lint i=1;i<len;i++){
        mulNum[i] = mulNum[i-1] * i;
    }
    return mulNum;
}

//计算指数
lint PowBit(int bit){
    int pow = 1;
    for(int i =0; i < bit; i++){
        pow *= 2;
    }
    return pow;
}

//构建树
void CreateTree(Node **p,lint mid,lint left,lint right){
    if(mid == left || mid == right || right == left){
        return;
    }
    lint left1 = ceil((mid + left)/2);
    lint right1 = ceil((mid + right)/2);
   // bool flag = FALSE;
    (*p) = (Node *)malloc(sizeof(Node));
    if(*p){
        if(mid == 1){
            (*p)->data = mid;
            (*p)->right = NULL; 
            (*p)->left = (Node *)malloc(sizeof(Node));
            (*p)->left->data = 0;
            (*p)->left->left = NULL;
            (*p)->left->right = NULL;
        }
        else{        
            (*p)->data = mid;
            (*p)->left = NULL;
            (*p)->right = NULL;             
            CreateTree(&(*p)->left, left1, left, mid);
            CreateTree(&(*p)->right, right1, mid, right);
        }
        
    }
    else{
        return;
    }
}

//树内存释放
void FreeTree(Node *foot){
    if(foot){
        FreeTree(foot->left);
        FreeTree(foot->right);
        free(foot);
    }
}

//树的前序遍历
void PrintInTree(Node *tree){
    if(tree){
        PrintInTree(tree->left);
        printf("\n%d;",tree->data);
        PrintInTree(tree->right);
    }
}

//编码
lint *Coding(lint mul[],lint code[],Node *Foot0,int len,lint ratio[]){
    len += 1;
    //lint *ratio = (lint *)malloc(sizeof(lint)*len);
    lint footData,sum,code_i,res=0;
    Node *Foot;
    memset(ratio, 0, sizeof(ratio)*len);
    // for(int i=0;i<len;i++){
    //     ratio[i] = 0;
    // }
    for(int i=len-2;i>=0;i--){
        code_i = code[i];
        Foot = Foot0;
        sum = 0;
        while(1){
            if(!Foot){
                break;
            }
            footData = Foot->data;
            if(code_i == footData){
                sum += ratio[footData];
                ratio[footData] += 1;
                res += (mul[len-2-i]*sum);
                break;
            }
            if(code_i > footData){
                sum += ratio[footData];
                Foot = Foot->right;
            }
            else{
                ratio[footData] += 1;
                Foot = Foot->left;
            }
        }       
    }
    ratio[len-1] = res;
    //free(ratio);
    return ratio;
}

//常规编码-排序
int rankCom(lint code[],int i){
    int num=0;
    int code_i = code[i];
    for(int j=0;j<i;j++){
        if(code[j]<code_i){
            num++;
        }
    }
    num = code[i] - num;
    return num;
}

//常规编码
lint *CodingCom(lint mul[],lint code[],int len,lint ratio[]){
    len += 1;
    //lint *ratio = (lint *)malloc(sizeof(lint)*len);
    ratio[0] = code[0];
    lint res = ratio[0] * mul[len-2];
    for(int i =1;i < len-2;i++){
        ratio[i] = rankCom(code,i);
        res += (ratio[i]*mul[len-2-i]) ;
    }
    ratio[len-1] = res;
    return ratio;
}

//解码时候，左节点树木，存住，只运行一次
/*lint *CodeLeft(lint mul[],lint code[],Node *Foot0,lint len){
    lint *ratio = (lint *)malloc(sizeof(lint)*len);
    lint footData,sum,code_i;
    Node *Foot;
    for(lint i=0;i<len;i++){
        ratio[i] = 0;
    }
    for(lint i=len-1;i>=0;i--){
        code_i = code[i];
        Foot = Foot0;
        sum = 0;
        while(1){
            if(!Foot){
                break;
            }
            footData = Foot->data;
            if(code_i == footData){
                sum += ratio[footData];
                ratio[footData] += 1;
                break;
            }
            if(code_i > footData){
                sum += ratio[footData];
                Foot = Foot->right;
            }
            else{
                ratio[footData] += 1;
                Foot = Foot->left;
            }
        }       
    }
    return ratio;
}
*/

//解码商运算，返回商的数组
lint *DivCode(lint code_re,int len,lint mul[],lint quo[]){
    //lint *quo = (lint *)malloc(sizeof(lint)*len);
    for(int i=len-1;i>=1;i--){
        quo[len-1-i] = code_re / mul[i];
        code_re = code_re % mul[i];
    }
    quo[len-1] = 0;
    return quo;
}

//解码，返回解码后的数组
lint *Encoding(int len,lint mul[],lint leftCopy[],Node *Foot,lint quo[],lint exit[]){
    lint *divNum,*returnCode;
    Node *Foot0 = NULL;
    lint foot;
    //exit = (lint*)malloc(sizeof(lint)*len);
    returnCode = (lint*)malloc(sizeof(lint)*len);
    divNum = DivCode(leftCopy[len],len,mul,quo);
    memset(exit,1,sizeof(exit)*len);
    for(int i=0;i<len;i++){
        divNum[i] += 1;
        Foot0 =Foot;
        foot = Foot0->data;
        lint sumLeft = leftCopy[foot];
        while(1){
            if(divNum[i]>sumLeft){
                Foot0 = Foot0->right ;
                foot = Foot0->data;
                sumLeft += leftCopy[foot];
            }
            else if(divNum[i] < sumLeft || (divNum[i] == sumLeft & exit[foot] == 0)){
                sumLeft -= leftCopy[foot];
                leftCopy[foot] -= 1;
                Foot0 = Foot0->left ;
                foot = Foot0->data;
                sumLeft += leftCopy[foot];
            }
            else{
                returnCode[i] = foot;
                exit[foot] = 0;
                leftCopy[foot] -= 1;
                break;
            }
        }
    }
    // free(divNum);
    // free(exit);
    //free(leftCopy);
    return returnCode;
}

int main(){
    Node * Foot = NULL;
    lint *mulNum,*divNum,*codingArray,*enCoding;
    int bit,len;
    lint mid;
    double dur;
    clock_t start,end;
    //输入的位数
    printf("请输入比特位数：");
    scanf("%d",&bit);
    start = clock();
    //输入的矩阵列表 
    lint code[]={13, 7, 3, 2, 4, 14, 10, 9, 12, 6, 0, 11, 1, 15, 8, 5};
    mid = PowBit(bit - 1);
    len = PowBit(bit);
    //申请内存;ratio数系数;quo商系数;exit初始态
    lint *ratio = (lint *)malloc(sizeof(lint)*len);
    lint *quo = (lint *)malloc(sizeof(lint)*len);
    lint *exit = (lint*)malloc(sizeof(lint)*len);
    //计算阶乘
    mulNum = Mul(len);
    //构造树
    CreateTree(&Foot,mid, 0, len);
    //树的中序遍历
    // PrintInTree(Foot);
    //编码;Coding优化的；CodingCom优化的
    int m = 1000000;
    while(m--){
        codingArray = Coding(mulNum,code,Foot,len,ratio);
        //codingArray = CodingCom(mulNum,code,len,ratio);
    }
    printf("\n编码：%llu\n",codingArray[len]);
    end = clock();
    dur = (double)(end - start);
    printf("耗时:%f\n",(dur/CLOCKS_PER_SEC));
    printf("11");
    //解码
    enCoding = Encoding(len,mulNum,codingArray,Foot,quo,exit);
    for(int i = 0;i<len;i++){
        printf("%d;",enCoding[i]);
    }
    //释放内存
    FreeTree(Foot);
    free(mulNum);
    free(exit);
    free(quo);
    free(enCoding);
    return 0;
}