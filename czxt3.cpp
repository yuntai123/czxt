#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<iostream>
#include <ctime>
using namespace std;
int pagesize=1024; 
int ybx,dbx,fd;//ybx页表项，dbx段表项，fd分段判断 
int page[10],jz[10],dc[10],mw[10];//page块号，jz基址，dc段长，mw基址+段长 

void pageinit();
void fdpageinit();
void randominit(int begin,int end,int size,int array[]);
int randompage(int begin,int end);
void show();
void showfd();
void fdjs();
void fyjs();
void menu();


void pagechoose(){//分页页面大小选择 
	cout<<"请输入每页大小：（0-1K；1-2K；2-4K；3-随机选择）"<<endl;
	int choose;
	cin>>choose;
	switch(choose){
		case 0:pagesize=1*1024;break;
		case 1:pagesize=2*1024;break;
		case 2:pagesize=4*1024;break;
		case 3:pagesize=randompage(0,2);break;
		default:;
	}
}

void pageinit(){//手动输入 
	for(int i=0;i<ybx;i++){
		cin>>page[i];
		//cout<<endl;
		for(int j=0;j<i;j++){
			if(page[i]==page[j]){
				cout<<"您输入的块号有误，与第"<<j<<"号页面输入的块号重复，请重新输入第"<<i<<"号页面对应的块号！"<<endl;
				i--;
			}
		}
	}
}

void fdpageinit(){
	int flag=0;
	for(int i=0;i<dbx;i++){
		cin>>jz[i]>>dc[i];
		mw[i]=jz[i]+dc[i]; 
		for(int j=0;j<i;j++){//冲突，有三种。1.基址在其他段长内，末尾不在2.末尾在，基址不在3.二者都在 
			if( (jz[i]<=jz[j]&&mw[i]>=jz[j]) || (jz[i]<mw[j]&&mw[i]>mw[j])){
				flag=1;
			}
			if(flag==1){
				cout<<"您输入的数据有误，与第"<<i<<"号分段（基址"<<jz[i]<<"，段长"<<dc[i]<<"）冲突，请重新输入第"<<j<<"号分段对应的基址和段长！"<<endl;
				i--;
				flag=0;
			}
		}
		
	}
}

void randominit(int begin,int end,int size,int array[]){ //begin随机起点，end随机终点，size随机个数，array 随机数存放位置 
	srand((unsigned)time(NULL));
	for(int i=0;i<size;i++){
		array[i] =(rand() % (end-begin+1))+ begin;
		for(int j=0;j<i;j++){
			if(array[i]==array[j])i--;
		} 
	}
	
}


int randompage(int begin,int end){//jizhi为1时，调用基址生成 ,此时begin从1开始，否则从0开始 
	/*
	if(fd==1){
		return  ((rand() % (end-begin+1))+ begin)*1024;
	}
	else {*/
	srand((unsigned)time(NULL));
	int size[4]={1,2,4,8};
	return  size[(rand() % (end-begin+1))+ begin]*1024;
	//}
	
}

void fdrandominit(int begin,int end,int size,int a[],int b[]){ //begin随机起点，end随机终点，size随机个数，array 随机数存放位置 
	
	srand((unsigned)time(NULL));
	int temp[size];
	for(int i=0;i<size;i++){
		a[i]=((rand() % (end-begin+1))+ begin)*1024;
		b[i]=randompage(0,3);
		temp[i]=a[i]+b[i];
		for(int j=0;j<i;j++){
			if((a[i]<=a[j]&&temp[i]>=a[j]) || (a[i]<temp[j]&&temp[i]>temp[j]))
			i--;
		} 
	}
	
}

void pagingmenu(int fd){//fd即分段，判断是否为分段，分页分段公用一套函数 
	int choose;
	if(fd==1){//分段 
		cout<<"请输入段表项个数：（5到10之间整数，含端点）"<<endl;
		cin>>dbx;
		cout<<"\n请输入页表中每段对应的基址和段长：（0-手动输入；1-随机生成）";
		cin>>choose;
		switch(choose){
			case 0:fdpageinit(); break;
			case 1:fdrandominit(1,100,dbx,jz,dc);break;
		}
	}
	else {//分页 
		pagechoose();
		cout<<"请输入页表项个数：（5到10之间整数，含端点）"<<endl;
		cin>>ybx;
		cout<<"\n请输入页表中每页对应的块号：（0-手动输入；1-随机生成0至10之间的非重复整数作为块号）";
		cin>>choose;
		switch(choose){
			case 0:pageinit(); break;
			case 1:randominit(0,10,10,page);break;
		}
	}
}

void show(){
	cout<<" 您选择了分页方式，输入的数据如下："<<endl;
	cout<<"每页大小"<<pagesize/1024<<"K，页表为"<<endl;
	cout<<"页号\t块号"<<endl; 
	for(int i=0;i<ybx;i++){
		cout<<i<<"\t"<<page[i]<<endl;
	}
	fyjs();
}
void showfd(){
	cout<<"您选择了分段方式，输入的数据如下："<<endl;
	cout<<"段号\t基址\t段长"<<endl;
	for(int i=0;i<dbx;i++){
		cout<<i<<"\t"<<jz[i]<<"\t"<<dc[i]<<endl;
	}
	fdjs();
}

void  fyjs(){
	cout<<"请开始你的表演（输入逻辑地址）"<<endl;
	int ljdz,yh,yp,kh,wldz,flag=0;
	do{
	    if(flag>0)cout<<"您输入的地址已溢出，请重新输入！"<<endl;
		cin>>ljdz;
		yh=ljdz/pagesize;
		flag++;
	}while(yh>ybx);
	yp=ljdz%pagesize;
	kh=page[yh];
	wldz=kh*pagesize+yp;
	cout<<"您选择了分页方式，输入的逻辑地址为"<<ljdz<<"，其对应的页号为"<<yh<<"，页偏移为"<<yp<<"；该地址对应的块号为"<<kh<<"，块偏移为"<<yp<<"，物理地址为"<<wldz<<"。";
    cout<<"是否继续？(Y/N)"<<endl;
    char ss;
    cin>>ss;
    if(ss=='Y')menu();
    else ;
}

void fdjs(){
	cout<<"请开始你的表演（输入逻辑地址）"<<endl;
	int ljdz,dh,dp,jizhi,wldz;
	cin>>ljdz;
	int temp=ljdz,i,z=ljdz;
	for(i=0;i<dbx;i++){
		ljdz-=dc[i];
		if(ljdz<0)break;
		temp=ljdz;
	}
	dh=i;
	dp=temp;
	jizhi=jz[i];
	wldz=jz[i]+dp;
	cout<<"您选择了分页方式，输入的逻辑地址为"<<z<<"，其对应的段号为"<<dh<<"，段偏移为"<<dp<<"；该地址对应的基址为"<<jizhi<<"，段偏移为"<<dp<<"，物理地址为"<<wldz<<"。";
    
	cout<<"是否继续？(Y/N)"<<endl;
    char ss;
    cin>>ss;
    if(ss=='Y')menu();
    else ;
}

void menu(){
	system("cls");
	cout << "------------------分页------------------------" << endl;
	cout << "*              1.分页                         *" << endl;
	cout << "*              2.分段                         *" << endl;
	cout << "*              3.退出                         *" << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "请选择：";
	int choose=0;
		scanf("%d",&choose);
		switch(choose){
			case 1:pagingmenu(0);show();break;
				
			case 2:pagingmenu(1);showfd();break;
			    
			case 3:
			    return ; 
			default:printf("输入出错，请重新输入\n"); 
		}
}
int main(){
	/*randominit(0,10,10,page);
	for(int i=0;i<10;i++){
		cout<<page[i]<<" ";
	}
	dbx=5;
	fdpageinit();*/
	menu();
	return 0;
} 
