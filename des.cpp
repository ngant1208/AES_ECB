#include<iostream>
#include<string>
#include<cmath>
#include<cstring>
using namespace std;

string binary="";
string copy_p;
string per_choice2;
string hex2bin(string hexnum){
    int i=0;
    while(hexnum[i])
    {
        switch(hexnum[i])
        {
            case '0':binary.append("0000");break;
            case '1':binary.append("0001");break;
            case '2':binary.append("0010");break;
            case '3':binary.append("0011");break;
            case '4':binary.append("0100");break;
            case '5':binary.append("0101");break;
            case '6':binary.append("0110");break;
            case '7':binary.append("0111");break;
            case '8':binary.append("1000");break;
            case '9':binary.append("1001");break;
            case 'a':binary.append("1010");break;
            case 'b':binary.append("1011");break;
            case 'c':binary.append("1100");break;
            case 'd':binary.append("1101");break;
            case 'e':binary.append("1110");break;
            case 'f':binary.append("1111");break;
        }
        i++;
    }
        return binary;
}
/******hàm convert bin2hex****************/
string bin2hex(string c){
    int  dec;
    string hx="";
    int k=c.length(),i=0;
    string a;
    while ( i<=k-4)
    {
         dec=0;
         a=c.substr(i,4);
         for (int j = 3; j >=0; j--)
         {
             if(a[j]=='1'){dec=dec+pow(2,(3-j));}
         }
        if(dec>=10){
               string  t="abcdef";
               string s1=t.substr(dec-10,1);
               hx.append(s1);}
        else{
               string  t="0123456789";
               string s1=t.substr(dec,1);
               hx.append(s1);
           }
           i=i+4;
    }
    return hx;
}
/**************** ham hoan vi khoi tạo*************************/
string initial_per(string &p){
    copy_p=p.substr(0);
    for(int j=0;j<=7;j++){
        for(int i=7;i>=4;i--){
            p[i*8+j]=copy_p[(63-8*j)-(2*(7-i)+1)];
        }
        for (int i = 3; i >= 0; i--){
            p[i*8+j]=copy_p[(63-8*j)-2*(3-i)];
        }
    }
    return p;
}
/****************hoán vị mở rộng E************************/
string  Expansion(string Ri){
    int k=0;
    string Ri_exp=Ri.append("0000000000000000");
    for (int i = 0; i < 8; i++)
    {
       for (int j = (6*i)+1; j <= (6*i)+4; j++)
       {
           int h=j-2*i-1;
           Ri_exp[j]=Ri[h];
       }
    }
    while (k<=42)
    {
        if((k==0)||(k==42)){
            if(k==0){Ri_exp[k]=Ri[31];
                     Ri_exp[k+5]=Ri[4*(k/6+1)];}
            else {Ri_exp[k]=Ri[4*(k/6)-1];
                  Ri_exp[k+5]=Ri[0];}
                  }
        else{ 
         Ri_exp[k]=Ri[4*(k/6)-1];
         Ri_exp[k+5]=Ri[4*(k/6+1)];}
        k=k+6;
    }
    return Ri_exp;
}
/***************hàm dịch******************/
string Left_shift_per(int k, string &key_c, string &key_d){
   if((k==1)||(k==2)||(k==9)||(k==16)){
       for(int i=0;i<=26;i++){
           key_c[i]=key_c[i+1];
           key_d[i]=key_d[i+1];
       }
       key_c=key_c.replace(27,1,"0");
       key_d=key_d.replace(27,1,"0");
   }
   else{
       for (int i = 0; i <= 25; i++)
       {
           key_c[i]=key_c[i+2];
           key_d[i]=key_d[i+2];
       }
       key_c.replace(26,2,"00");
       key_d.replace(26,2,"00");
   }
   string per_choice={key_c[13],key_c[16],key_c[10],key_c[23],key_c[0],key_c[4],key_c[2],key_c[27],
               key_c[14],key_c[5],key_c[20],key_c[9],key_c[22],key_c[18],key_c[11],key_c[3],
               key_c[25],key_c[7],key_c[15],key_c[6],key_c[26],key_c[19],key_c[12],key_c[1],
               key_d[40-28],key_d[51-28],key_d[30-28],key_d[36-28],key_d[46-28],key_d[54-28],key_d[29-28],key_d[39-28],
               key_d[50-28],key_d[44-28],key_d[32-28],key_d[47-28],key_d[43-28],key_d[48-28],key_d[38-28],key_d[55-28],
               key_d[33-28],key_d[52-28],key_d[45-28],key_d[41-28],key_d[49-28],key_d[35-28],key_d[28-28],key_d[31-28]};
    return per_choice;
}
/***************bỏ bit và hoán vị key********************************/
string Drop_per(string p){
    int k;
    string re=p.substr(0,56);
    for(int j=1;j<=8;j++){
        if(j<5){
        for(int i=8*j-8;i<=8*j-1;i++){
            if(i>27){break;}
            re[i]=p[(55+j)-8*(i%8)];}
            }
        else{
            k=0;
            for(int i=8*j-12;i<=8*j-5;i++){
            if(i>55){break;}
            if(i>51){
                re[i]=p[443-i*8];}
             else{re[i]=p[(67-j)-8*k];}
            k=k+1;}
        }
    }
    return re;
}
/**********dec2bin*************/
string dec2bin(int dec){
    string bin="0000";
     int a;
     string b;
     for (int i = 3; i >=0; i--)
     {
        a=dec%2;
        if(a==0){bin.replace(i,1,"0");}
        else{bin.replace(i,1,"1");}
         dec=dec/2;
     }
    return bin; 
}
/*************xor************/
string XOR(string p,string q){
    string r="";
    for (int i = 0; i < p.length(); i++)
    {
        string k=p.substr(i,1);
        string h=q.substr(i,1);
        if(k.compare(h)==0){
            r.append("0");
        }
        else{
            r.append("1");
        }
    }
    return r;
}
/**********************S-box****************************************/

string S_box(string &p){
       string c;
       string sub_p;
       int m=0,col,rol;
       int s1[4][16]={14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
                      0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
                      4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
                      15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13};
      int s2[4][16]={15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
                    3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
                    0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
                    13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9};
      int s3[4][16]={10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
                    13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
                    13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
                    1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12};
      int s4[4][16]={7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
                    13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
                    10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
                    3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14};
      int s5[4][16]={2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
                    14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
                    4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
                    11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3};
      int s6[4][16]={12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
                     10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
                     9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
                     4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13};
      int s7[4][16]={4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
                    13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
                    1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
                    6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12};
      int s8[4][16]={13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
                    1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
                    7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
                    2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11};
       while(m<=42)
       {
           sub_p=p.substr(m,6);
           col=0,rol=0;
           for (int i = 0; i <= 5; i++)
           {
               if(i!=0&&i!=5){
                   if (sub_p[i]=='1') {col+=pow(2,(4-i)); }  
                }
               else{
                   if(sub_p[i]=='1'){rol+=pow(2,(1-i/5));}
               }
           }
        switch(m/6+1){
          case 1: c=dec2bin(s1[rol][col]);break;
          case 2: c=dec2bin(s2[rol][col]);break;
          case 3: c=dec2bin(s3[rol][col]);break;
          case 4: c=dec2bin(s4[rol][col]);break;
          case 5: c=dec2bin(s5[rol][col]);break;
          case 6: c=dec2bin(s6[rol][col]);break;
          case 7: c=dec2bin(s7[rol][col]);break;
          case 8: c=dec2bin(s8[rol][col]);break;
        }
           p=p.replace((m*2/3),4,c);
           m+=6;
       }
       p=p.substr(0,32);
        return p;
    }
string DES(string plain_tex,string key){
   string left,right;
   string key_c,key_d;
   string cipher;
   initial_per(plain_tex);
   left=plain_tex.substr(0,32);
   right=plain_tex.substr(32,32);
   string p_key=Drop_per(key);
   key_c=p_key.substr(0,28);
   key_d=p_key.substr(28,28);
   for(int k=1;k<=16;k++){
    /***********hoán vị mở rộng E*********/
     string y=Expansion(right);
    /***********left shift******************/
     per_choice2 =Left_shift_per(k,key_c,key_d);
     /****xor****/
      string x=XOR(y,per_choice2);
      S_box(x);
    /***********straight_permuted************/
      string cpy_x=x.substr(0);
      x={cpy_x[15],cpy_x[6],cpy_x[19],cpy_x[20],cpy_x[28],cpy_x[11],cpy_x[27],cpy_x[16],
       cpy_x[0],cpy_x[14],cpy_x[22],cpy_x[25],cpy_x[4],cpy_x[17],cpy_x[30],cpy_x[9],
       cpy_x[1],cpy_x[7],cpy_x[23],cpy_x[13],cpy_x[31],cpy_x[26],cpy_x[2],cpy_x[8],
       cpy_x[18],cpy_x[12],cpy_x[29],cpy_x[5],cpy_x[21],cpy_x[10],cpy_x[3],cpy_x[24]};
    /*********xor_left********/
    string cpy_right=right.substr(0);
    string d=XOR(x,left); 
    right=d.substr(0);
    left=cpy_right.substr(0);
    /**************swap 32 bit*************/
    if(k==16){
        swap(right,left);
    }
    /**************final_per************/
    string comb=left+right;
     cipher = { comb[39],comb[7],comb[47],comb[15],comb[55],comb[23],comb[63],comb[31],
                comb[38],comb[6],comb[46],comb[14],comb[54],comb[22],comb[62],comb[30],
                comb[37],comb[5],comb[45],comb[13],comb[53],comb[21],comb[61],comb[29],
                comb[36],comb[4],comb[44],comb[12],comb[52],comb[20],comb[60],comb[28],
                comb[35],comb[3],comb[43],comb[11],comb[51],comb[19],comb[59],comb[27],
                comb[34],comb[2],comb[42],comb[10],comb[50],comb[18],comb[58],comb[26],
                comb[33],comb[1],comb[41],comb[9],comb[49],comb[17],comb[57],comb[25],
                comb[32],comb[0],comb[40],comb[8],comb[48],comb[16],comb[56],comb[24] };
    
}
return cipher;
}

int main(){
    /*************nhập plaintext và biến đổi nhị phân************************/
    string plain_text,p_key,iput_key;
    string bin_plain,bin_key,key;
    string left,right;
    string key_c,key_d;
    string x;
    cout<<"Enter the plaintext: ";
    cin>>plain_text;
    bin_plain=hex2bin(plain_text);
    /********************hàm hoán vị khởi tạo*********************/
    cout<<"sau khi hoan vi khoi tao: ";
    initial_per(bin_plain);
    cout<<bin2hex(bin_plain)<<endl;
    left=bin_plain.substr(0,32);
    right=bin_plain.substr(32,32);
    /*****************key**************************/
    cout<<"enter key: ";
    cin>>iput_key;
    bin_key=hex2bin(iput_key);
    p_key=Drop_per(bin_key);
    key_c=p_key.substr(0,28);
    key_d=p_key.substr(28,28);
    /*********************vào vòng lặp****************************/
    for(int k=1;k<=16;k++){
    cout<<"left  "<<k-1<<"   la:  "<<bin2hex(left )<<" ";
    cout<<"right "<<k-1<<"   la:  "<<bin2hex(right)<<endl;
    cout<<"key_c_d "<<key_c<<" "<<key_d<<endl;
     /***********hoán vị mở rộng E*********/
     string y=Expansion(right);//ok
     /***********left shift******************/
     Left_shift_per(k,key_c,key_d);
     /****xor****/
    x=XOR(y,per_choice2,48);//ok
    /****************S-box******************/
    S_box(x);//ok
    /***********straight_permuted************/
    string cpy_x=x.substr(0);
    x={cpy_x[15],cpy_x[6],cpy_x[19],cpy_x[20],cpy_x[28],cpy_x[11],cpy_x[27],cpy_x[16],
       cpy_x[0],cpy_x[14],cpy_x[22],cpy_x[25],cpy_x[4],cpy_x[17],cpy_x[30],cpy_x[9],
       cpy_x[1],cpy_x[7],cpy_x[23],cpy_x[13],cpy_x[31],cpy_x[26],cpy_x[2],cpy_x[8],
       cpy_x[18],cpy_x[12],cpy_x[29],cpy_x[5],cpy_x[21],cpy_x[10],cpy_x[3],cpy_x[24]};
    /*********xor_left********/
    string cpy_right=right.substr(0);
    string d=XOR(x,left,32); 
    right=d.substr(0);
    left=cpy_right.substr(0);
    }
    return 0;
}