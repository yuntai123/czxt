#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<iostream>
#include <ctime>
using namespace std;
int pagesize=1024; 
int ybx,dbx,fd;//ybxҳ���dbx�α��fd�ֶ��ж� 
int page[10],jz[10],dc[10],mw[10];//page��ţ�jz��ַ��dc�γ���mw��ַ+�γ� 

void pageinit();
void fdpageinit();
void randominit(int begin,int end,int size,int array[]);
int randompage(int begin,int end);
void show();
void showfd();
void fdjs();
void fyjs();
void menu();


void pagechoose(){//��ҳҳ���Сѡ�� 
	cout<<"������ÿҳ��С����0-1K��1-2K��2-4K��3-���ѡ��"<<endl;
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

void pageinit(){//�ֶ����� 
	for(int i=0;i<ybx;i++){
		cin>>page[i];
		//cout<<endl;
		for(int j=0;j<i;j++){
			if(page[i]==page[j]){
				cout<<"������Ŀ���������"<<j<<"��ҳ������Ŀ���ظ��������������"<<i<<"��ҳ���Ӧ�Ŀ�ţ�"<<endl;
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
		for(int j=0;j<i;j++){//��ͻ�������֡�1.��ַ�������γ��ڣ�ĩβ����2.ĩβ�ڣ���ַ����3.���߶��� 
			if( (jz[i]<=jz[j]&&mw[i]>=jz[j]) || (jz[i]<mw[j]&&mw[i]>mw[j])){
				flag=1;
			}
			if(flag==1){
				cout<<"������������������"<<i<<"�ŷֶΣ���ַ"<<jz[i]<<"���γ�"<<dc[i]<<"����ͻ�������������"<<j<<"�ŷֶζ�Ӧ�Ļ�ַ�Ͷγ���"<<endl;
				i--;
				flag=0;
			}
		}
		
	}
}

void randominit(int begin,int end,int size,int array[]){ //begin�����㣬end����յ㣬size���������array ��������λ�� 
	srand((unsigned)time(NULL));
	for(int i=0;i<size;i++){
		array[i] =(rand() % (end-begin+1))+ begin;
		for(int j=0;j<i;j++){
			if(array[i]==array[j])i--;
		} 
	}
	
}


int randompage(int begin,int end){//jizhiΪ1ʱ�����û�ַ���� ,��ʱbegin��1��ʼ�������0��ʼ 
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

void fdrandominit(int begin,int end,int size,int a[],int b[]){ //begin�����㣬end����յ㣬size���������array ��������λ�� 
	
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

void pagingmenu(int fd){//fd���ֶΣ��ж��Ƿ�Ϊ�ֶΣ���ҳ�ֶι���һ�׺��� 
	int choose;
	if(fd==1){//�ֶ� 
		cout<<"������α����������5��10֮�����������˵㣩"<<endl;
		cin>>dbx;
		cout<<"\n������ҳ����ÿ�ζ�Ӧ�Ļ�ַ�Ͷγ�����0-�ֶ����룻1-������ɣ�";
		cin>>choose;
		switch(choose){
			case 0:fdpageinit(); break;
			case 1:fdrandominit(1,100,dbx,jz,dc);break;
		}
	}
	else {//��ҳ 
		pagechoose();
		cout<<"������ҳ�����������5��10֮�����������˵㣩"<<endl;
		cin>>ybx;
		cout<<"\n������ҳ����ÿҳ��Ӧ�Ŀ�ţ���0-�ֶ����룻1-�������0��10֮��ķ��ظ�������Ϊ��ţ�";
		cin>>choose;
		switch(choose){
			case 0:pageinit(); break;
			case 1:randominit(0,10,10,page);break;
		}
	}
}

void show(){
	cout<<" ��ѡ���˷�ҳ��ʽ��������������£�"<<endl;
	cout<<"ÿҳ��С"<<pagesize/1024<<"K��ҳ��Ϊ"<<endl;
	cout<<"ҳ��\t���"<<endl; 
	for(int i=0;i<ybx;i++){
		cout<<i<<"\t"<<page[i]<<endl;
	}
	fyjs();
}
void showfd(){
	cout<<"��ѡ���˷ֶη�ʽ��������������£�"<<endl;
	cout<<"�κ�\t��ַ\t�γ�"<<endl;
	for(int i=0;i<dbx;i++){
		cout<<i<<"\t"<<jz[i]<<"\t"<<dc[i]<<endl;
	}
	fdjs();
}

void  fyjs(){
	cout<<"�뿪ʼ��ı��ݣ������߼���ַ��"<<endl;
	int ljdz,yh,yp,kh,wldz,flag=0;
	do{
	    if(flag>0)cout<<"������ĵ�ַ����������������룡"<<endl;
		cin>>ljdz;
		yh=ljdz/pagesize;
		flag++;
	}while(yh>ybx);
	yp=ljdz%pagesize;
	kh=page[yh];
	wldz=kh*pagesize+yp;
	cout<<"��ѡ���˷�ҳ��ʽ��������߼���ַΪ"<<ljdz<<"�����Ӧ��ҳ��Ϊ"<<yh<<"��ҳƫ��Ϊ"<<yp<<"���õ�ַ��Ӧ�Ŀ��Ϊ"<<kh<<"����ƫ��Ϊ"<<yp<<"�������ַΪ"<<wldz<<"��";
    cout<<"�Ƿ������(Y/N)"<<endl;
    char ss;
    cin>>ss;
    if(ss=='Y')menu();
    else ;
}

void fdjs(){
	cout<<"�뿪ʼ��ı��ݣ������߼���ַ��"<<endl;
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
	cout<<"��ѡ���˷�ҳ��ʽ��������߼���ַΪ"<<z<<"�����Ӧ�Ķκ�Ϊ"<<dh<<"����ƫ��Ϊ"<<dp<<"���õ�ַ��Ӧ�Ļ�ַΪ"<<jizhi<<"����ƫ��Ϊ"<<dp<<"�������ַΪ"<<wldz<<"��";
    
	cout<<"�Ƿ������(Y/N)"<<endl;
    char ss;
    cin>>ss;
    if(ss=='Y')menu();
    else ;
}

void menu(){
	system("cls");
	cout << "------------------��ҳ------------------------" << endl;
	cout << "*              1.��ҳ                         *" << endl;
	cout << "*              2.�ֶ�                         *" << endl;
	cout << "*              3.�˳�                         *" << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "��ѡ��";
	int choose=0;
		scanf("%d",&choose);
		switch(choose){
			case 1:pagingmenu(0);show();break;
				
			case 2:pagingmenu(1);showfd();break;
			    
			case 3:
			    return ; 
			default:printf("�����������������\n"); 
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
