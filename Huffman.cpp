#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include"Hh1.h"
using namespace std;

FILE * f1=fopen("C:\\Users\\Dell\\Documents\\pra1.txt","r");
FILE * f2=fopen("C:\\Users\\Dell\\Documents\\pra2.txt","w");
FILE * f3=fopen("C:\\Users\\Dell\\Documents\\pra4.huf","w");

int main(){
    init(SN);                                          //��ʼ���ַ����ݿ�//
    input(f1);                                          //�����ʼ�ļ����ַ�//
    for(int i=0;forest[i]!=NULL;i++)
        cout<<forest[i]->c<<":"<<forest[i]->weight<<endl;        //����ַ������ִ���
     cout<<"�����ַ����� "<<count<<endl;                                                                                //����ַ�����//
//    count=0;
    HFM huffman(count);                                     //������������ʵ��
     huffman.creat();                                           //������������

    huffman.hufcode();                                  //���������룬��ʱΪ����//
    exchange();                                         //������β�Ե�����������//
     huffman.savewithhufcode(f1,f2);                        //�ù���������洢ԭ�ļ�//
    cout<<endl;

    cout<<"1.�鿴����������"<<endl;
    cout<<"2.����������"<<endl;
    cout<<"3.�鿴ѹ����"<<endl;
    int choice;
    cin>>choice;
    while(choice>=1&&choice<=3){
        switch(choice){
            case 1:{
                for(int i=0;hufNode[i].sig!=NULL;i++){
                    cout<<"�ַ�"<<hufNode[i].sig->c<<"�Ĺ���������:";         //�������������//
                    for(int j=0;j<hufNode[i].size;j++)cout<<hufNode[i].code[j];
                    cout<<endl;
                }
                cout<<"�������:"<<huffman.maxc()<<endl;
                break;
            }
            case 2:{
                fclose(f2);
                f2=fopen("C:\\Users\\Dell\\Documents\\pra2.txt","r");
                huffman.hufdecode(f2,f3);                                        //����������//
                cout<<endl;
                break;
            }
            case 3:{
                compress();                                                  //�鿴ѹ�����//
                cout<<endl;
            }
        }
        cout<<"1.�鿴����������"<<endl;
        cout<<"2.����������"<<endl;
        cout<<"3.�鿴ѹ����"<<endl;
        cin>>choice;
    }
    cout<<"*ллʹ��*"<<endl;                                            //�˳�����//
    return 0;
}