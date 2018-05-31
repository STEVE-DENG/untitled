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
    init(SN);                                          //初始化字符数据库//
    input(f1);                                          //读入初始文件的字符//
    for(int i=0;forest[i]!=NULL;i++)
        cout<<forest[i]->c<<":"<<forest[i]->weight<<endl;        //输出字符及出现次数
     cout<<"出现字符种类 "<<count<<endl;                                                                                //输出字符种类//
//    count=0;
    HFM huffman(count);                                     //创建哈夫曼树实例
     huffman.creat();                                           //创建哈夫曼树

    huffman.hufcode();                                  //哈夫曼编码，此时为逆向//
    exchange();                                         //调整首尾对调哈夫曼编码//
     huffman.savewithhufcode(f1,f2);                        //用哈夫曼编码存储原文件//
    cout<<endl;

    cout<<"1.查看哈夫曼编码"<<endl;
    cout<<"2.哈夫曼解码"<<endl;
    cout<<"3.查看压缩率"<<endl;
    int choice;
    cin>>choice;
    while(choice>=1&&choice<=3){
        switch(choice){
            case 1:{
                for(int i=0;hufNode[i].sig!=NULL;i++){
                    cout<<"字符"<<hufNode[i].sig->c<<"的哈夫曼编码:";         //输出哈夫曼编码//
                    for(int j=0;j<hufNode[i].size;j++)cout<<hufNode[i].code[j];
                    cout<<endl;
                }
                cout<<"最大列数:"<<huffman.maxc()<<endl;
                break;
            }
            case 2:{
                fclose(f2);
                f2=fopen("C:\\Users\\Dell\\Documents\\pra2.txt","r");
                huffman.hufdecode(f2,f3);                                        //哈夫曼解码//
                cout<<endl;
                break;
            }
            case 3:{
                compress();                                                  //查看压缩情况//
                cout<<endl;
            }
        }
        cout<<"1.查看哈夫曼编码"<<endl;
        cout<<"2.哈夫曼解码"<<endl;
        cout<<"3.查看压缩率"<<endl;
        cin>>choice;
    }
    cout<<"*谢谢使用*"<<endl;                                            //退出操作//
    return 0;
}