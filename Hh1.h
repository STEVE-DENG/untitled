#include<iostream>
using namespace std;
struct signode{                         //signode�ڵ㣬���������ڵ�//
    char c;                             //�ַ�//
    int weight;                         //Ȩ��//
    bool b;                             //�������Ƿ����//
    signode * parent;
    signode * left;
    signode * right;
    signode(){                          //��ʼ��//
        c=NULL;
        b=false;
        weight=0;
        parent=left=right=NULL;
    }
};
signode SN[256];
signode * forest[256];                      //ɭ�����鱣����ֵ��ַ�//  
int count=0;                                //�����ַ�����//  
float memo1=0,memo2=0;                    //ȫ�ֱ�����¼�����ַ����ͱ����0 1��//  

void init(signode * sig){                   //SN[]�����ʼ�������볣���ַ�//  
    sig[0].c='a';sig[1].c='b';sig[2].c='c';	sig[3].c='d';sig[4].c='e';
    sig[5].c='f';sig[6].c='g';sig[7].c='h';sig[8].c='i';sig[9].c='j';
    sig[10].c='k';sig[11].c='l';sig[12].c='m';sig[13].c='n';sig[14].c='o';
    sig[15].c='p';sig[16].c='q';sig[17].c='r';sig[18].c='s';sig[19].c='t';
    sig[20].c='u';sig[21].c='v';sig[22].c='w';sig[23].c='x';sig[24].c='y';
    sig[25].c='z';

    sig[26].c='A';sig[27].c='B';sig[28].c='C';sig[29].c='D';sig[30].c='E';
    sig[31].c='F';sig[32].c='G';sig[33].c='H';sig[34].c='I';sig[35].c='J';
    sig[36].c='K';sig[37].c='L';sig[38].c='M';sig[39].c='N';sig[40].c='O';
    sig[41].c='P';sig[42].c='Q';sig[43].c='R';sig[44].c='S';sig[45].c='T';
    sig[46].c='U';sig[47].c='V';sig[48].c='W';sig[49].c='X';sig[50].c='Y';
    sig[51].c='Z';

    sig[52].c='0';sig[53].c='1';sig[54].c='2';sig[55].c='3';sig[56].c='4';
    sig[57].c='5';sig[58].c='6';sig[59].c='7';sig[60].c='8';sig[61].c='9';

    sig[62].c='+';sig[63].c='-';sig[64].c='*';sig[65].c='/';sig[66].c=',';
    sig[67].c='.';sig[68].c='\''; sig[69].c='"';sig[70].c=':';sig[71].c=';';
    sig[72].c='<';sig[73].c='>';sig[74].c='=';sig[75].c='?';sig[76].c=' ';
    sig[77].c='(';sig[78].c=')';sig[79].c='[';sig[80].c=']';sig[81].c='{';
    sig[82].c='}';sig[83].c='!';sig[84].c='@';sig[85].c='#';sig[86].c='$';
    sig[87].c='%';sig[88].c='^';sig[89].c='&';sig[90].c='\\';sig[91].c=10;

}
void compress(){                                                  //ѹ������Ա�//  
    cout<<"ѹ��ǰ:"<<memo1*8<<"bit   ѹ����:"<<memo2<<"bit"<<endl;
    cout<<"ѹ����:"<<memo2/(memo1*8)<<endl;
}
struct hufnode{                                            //������������ձ�ڵ�//  
    signode * sig;
    int  code[100];                                         //�������������//
    int size;
    bool b;
    hufnode(){sig=NULL;size=0;b=true;}
};
hufnode hufNode[256];
void exchange(){                                        //������β��������������//
    int temp;
//    for(int i=0;hufNode[i].sig!=NULL;i++){
//        for(int s=0,b=hufNode[i].size-1;s<=b;s++,b--){
//            temp=hufNode[i].code[s];
//            hufNode[i].code[s]=hufNode[i].code[b];
//            hufNode[i].code[b] = temp;
//        }
//    }
    for(int i=1;hufNode[i].sig!=NULL;i++){
        for(int s=0,b=hufNode[i].size-1;s<=b;s++,b--){
            temp=hufNode[i].code[s];
            hufNode[i].code[s]=hufNode[i].code[b];
            hufNode[i].code[b] = temp;
        }
    }
}




class HFM{                                                      //��������//
private:
    signode * root;                                          //����������//
    signode * pt;                                         //����ʱ���ڱ�ָ��//
    int alleaf;
public:
    HFM(int all){root=pt=NULL;alleaf=all;}//all��ɭ�������ĸ���//
    ~HFM(){}
    signode * getroot(){return root;}
    signode * creat();                                        //������������//
    void hufcode();                                           //����//
    void savewithhufcode(FILE * inf,FILE * outf);           //�ù���������洢�ļ�//
    void hufdecode(FILE* ipf,FILE* opf);                      //����//
    void inorder(signode * sig);
    int maxc();                                        //��ȡ����������󳤶�//
};


signode * HFM::creat(){
    signode * pp=NULL;
    for(int i=0;i<count;i++)forest[i]->b=false;    //Ϊhufcode������׼������˺����޹�
     while(count>1){
    int min=10000;
    int min1,min2;
    for(int i=0;forest[i]!=NULL;i++){  //��������forѭ��ѡ����ǰɭ���е���С�����ڵ�
         if(forest[i]->weight<min){min=forest[i]->weight;min1=i;}            //
    }                                                              //
    min=10000;                                                   //
    for(int i=0;forest[i]!=NULL&&i!=min1;i++){                            //
        if(forest[i]->weight<min){min=forest[i]->weight;min2=i;}           //
    }
    for(int i=min1+1;forest[i]!=NULL;i++){                                //
        if(forest[i]->weight<min){min=forest[i]->weight;min2=i;}         //
    }                                                             //�����ҵ�min1 min2
    pp=new signode();                         //�����ɽڵ㣬ȨֵΪ����С�ڵ�Ȩֵ֮��//
    pp->left=forest[min1];
    pp->right=forest[min2];
    forest[min2]->b=true;                   //Ϊhufcode������׼������˺����޹�//
    pp->weight=forest[min1]->weight+forest[min2]->weight;
    forest[min1]->parent=pp;
    forest[min2]->parent=pp;
    forest[min1]=pp;                                          //�����ɽڵ����ɭ��
          for(int i=min2;forest[i]!=NULL;i++)forest[i]=forest[i+1];       //min2��Ľڵ�����ǰ��//
    count--;
}
root=pp;
return pp;
}
void HFM::hufcode(){                                                //���������룬������hufNode�ڵ�����鵱��//
    inorder(root);
    for(int i=1;hufNode[i].sig!=NULL;i++){//��i��ѭ����0��Ϊ��1
        printf("%d\n", hufNode[i].sig->c);
        signode * gud=hufNode[i].sig;
        while(gud->parent!=NULL){
            if(gud->parent->left==gud)hufNode[i].code[hufNode[i].size++]=0;
            else if(gud->parent->right==gud)hufNode[i].code[hufNode[i].size++]=1;
            gud=gud->parent;
        }
    }
}
void HFM::savewithhufcode(FILE * inf,FILE * outf){                        //�ù���������洢�ļ�//
    rewind(inf);                                                          //�ص��ļ���ʼ��ֹ�ļ�δ�رյ��µĴ���//
    char ch=fgetc(inf);

    for(int i=1;i<count;i++) {//��i��ѭ����0��Ϊ��1    ������������ı�
        printf("hufNode[i].sig->cΪ%d  %c\n",hufNode[i].sig->c,hufNode[i].sig->c);
        for (int k = 0; k < hufNode[i].size; k++) {
            printf("%d",hufNode[i].code[k]);
        }
        printf("\n");
    }

    while(!feof(inf)){
        if(hufNode[1].sig->c==ch){
            for(int k=0;k<hufNode[1].size;k++){
                if(hufNode[1].code[k]==0){fputc(48,outf);memo2++;}        //48,49�ֱ����ַ�0,1��ASCII��//
                else if(hufNode[1].code[k]==1){fputc(49,outf);memo2++;}
            }
        }
        for(int i=1;hufNode[i].sig->c!=ch;i++){//��i��ѭ����0��Ϊ��1

            if(hufNode[i+1].sig->c==ch) {
            for(int k=0;k<hufNode[i+1].size;k++){
                printf("%d",hufNode[i+1].code[k]);
                if(hufNode[i+1].code[k]==0){fputc(48,outf);memo2++;}        //48,49�ֱ����ַ�0,1��ASCII��//
                else if(hufNode[i+1].code[k]==1){fputc(49,outf);memo2++;}
            }
        }

        }
        ch=fgetc(inf);
    }

}

void HFM::inorder(signode * sig){
    if(sig->left==NULL&&sig->right==NULL){
        hufNode[count++].sig=sig;
        return ;
    }
    else {
        inorder(sig->left);
        inorder(sig->right);
    }
}


int HFM::maxc(){
    int ma=0;                                                //��������//
    for(int i=0;i<alleaf;i++){
        if(hufNode[i].size>ma)ma=hufNode[i].size;
    }
    return ma;
}
void HFM::hufdecode(FILE* ipf,FILE* opf){                //���룬�ɹ������뵽�ַ�//
    signode* pt=root;
    char ch=fgetc(ipf);
    while(!feof(ipf)){                                   //�ж����޵��ļ�β/
        if(ch=='0'){
            if(pt->left==NULL){
                cout<<pt->c;
                fputc(pt->c,opf);
                pt=root;
            }
            pt=pt->left;
        }
        else if(ch=='1'){                                  //ע���ַ�0,1������0,1�ǲ�ͬ��//
            if(pt->right==NULL){
                cout<<pt->c;
                fputc(pt->c,opf);
                pt=root;
            }
            pt=pt->right;
        }
        ch=fgetc(ipf);
    }
    cout<<pt->c;
    fputc(pt->c,opf);
    fclose(ipf);
    fclose(opf);
}
void input(FILE * f){
    char ch=fgetc(f);
    while(!feof(f)){                            //feof(f1)�ж��ļ��Ƿ��������������ֵΪ��//
        putchar(ch);                        //����Ļ�����һ���ַ�//
        memo1++;
        for(int i=0;SN[i].c!=NULL;i++){     //�鿴�ļ������޸��ַ�Ȩ��//
            if(SN[i].c==ch){
                if(SN[i].b==false){           //�����һ�γ��־ͼ���ɭ��,����ʲôҲ����//
                    SN[i].b=true;
                    forest[count++]=&SN[i];
                }
                SN[i].weight++;              //����Ȩ��//
            }
        }
        ch=fgetc(f);
    }
    cout<<endl;
}