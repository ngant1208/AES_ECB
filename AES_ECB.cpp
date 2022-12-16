#include<iostream>
#include<string>
#include<cmath>
using namespace std;
string hex2bin(string hexnum){
    int i=0;
    string binary;
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
            case 'A':
            case 'a':binary.append("1010");break;
            case 'b':
            case 'B':binary.append("1011");break;
            case 'c':
            case 'C':binary.append("1100");break;
            case 'd':
            case 'D':binary.append("1101");break;
            case 'e':
            case 'E':binary.append("1110");break;
            case 'f':
            case 'F':binary.append("1111");break;
        }
        i++;
    }
        return binary;
}
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
string XOR(string p,string q){
    string r="";
    for (int i = 0; i < q.length(); i++)
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
// addround key là xor plaintext với key
/*****S_bõ cho 8 bit************/
string S_box(string bin){
    string n_bin;
const char *s[16][16]={"63","7C","77","7B","F2","6B","6F","C5","30","01","67","2B","FE","D7","AB","76",
                    "CA","82","C9","7D","FA","59","47","F0","AD","D4","A2","AF","9C","A4","72","C0",
                    "B7","FD","93","26","36","3F","F7","CC","34","A5","E5","F1","71","D8","31","15",
                    "04","C7","23","C3","18","96","05","9A","07","12","80","E2","EB","27","B2","75",
                    "09","83","2C","1A","1B","6E","5A","A0","52","3B","D6","B3","29","E3","2F","84",
                    "53","D1","00","ED","20","FC","B1","5B","6A","CB","BE","39","4A","4C","58","CF",
                    "D0","EF","AA","FB","43","4D","33","85","45","F9","02","7F","50","3C","9F","A8",
                    "51","A3","40","8F","92","9D","38","F5","BC","B6","DA","21","10","FF","F3","D2",
                    "CD","0C","13","EC","5F","97","44","17","C4","A7","7E","3D","64","5D","19","73",
                    "60","81","4F","DC","22","2A","90","88","46","EE","B8","14","DE","5E","0B","DB",
                    "E0","32","3A","0A","49","06","24","5C","C2","D3","AC","62","91","95","E4","79",
                    "E7","C8","37","6D","8D","D5","4E","A9","6C","56","F4","EA","65","7A","AE","08",
                    "BA","78","25","2E","1C","A6","B4","C6","E8","DD","74","1F","4B","BD","8B","8A",
                    "70","3E","B5","66","48","03","F6","0E","61","35","57","B9","86","C1","1D","9E",
                    "E1","F8","98","11","69","D9","8E","94","9B","1E","87","E9","CE","55","28","DF",
                    "8C","A1","89","0D","BF","E6","42","68","41","99","2D","0F","B0","54","BB","16"};
    int rol=0,col=0;
    for (int i = 0; i < 4; i++)
    {
        if(bin[i]=='1'){rol+=pow(2,3-i);
        }
    }
    
    for (int i = 4; i < 8; i++)
    {
        if(bin[i]=='1'){col+=pow(2,7-i);
        }
    }
   n_bin=hex2bin(s[rol][col]);
   return n_bin;
}

string  G_function(string w,int k){
    string cp,sub_cp;
    cp=w.substr(8);
    cp.append(w.substr(0,8));
    for(int i=0;i<=24;i=i+8){
     sub_cp=S_box(cp.substr(i,8));
     w=w.replace(i,8,sub_cp);
    }
    // rc
    string c="00000000000000000000000000000000";
    const char *RC[10]={"01","02","04","08","10","20","40","80","1B","36"};
    c.replace(0,8,hex2bin(RC[k-1]));
    string kq=XOR(w,c);
    return kq;
}
string key_e;
void Key_Expansion(string key,int k){
    
    if(k==0){
     key_e=key.substr(0);
    }
    else{
    string w0_3=key_e.substr(96,32);
    string w0_3_g=G_function(w0_3,k);
    string temp,w1="";
    for(int i=0;i<=96;i=i+32){
      if(i==0){
          string w1_4=XOR(key_e.substr(0,32),w0_3_g);
          temp=w1_4.substr(0);}
      else{string w1_5=XOR(key_e.substr(i,32),temp);
           temp=w1_5;}
      w1.append(temp);
      }
      key_e=w1.substr(0);
    }
}
string Shift_row(string &m){
   string cp_m=m.substr(0);
   m.replace(32,24,cp_m.substr(40,24));
   m.replace(56,8,cp_m.substr(32,8));
   m.replace(64,16,cp_m.substr(80,16));
   m.replace(80,16,cp_m.substr(64,16));
   m.replace(96,8,cp_m.substr(120,8));
   m.replace(104,24,cp_m.substr(96,24));
   return m;
}
string multi(string p,int k){
    string p_new;
    switch (k)
    {
    case 1:p_new=p.substr(0);break;
    case 2:
    p.append("0");
    if(p[0]=='1'){
        p_new=XOR(p.substr(1),"00000010");
    }
    else{
       p_new=p.substr(1);
    }
    ;break;
    case 3:
    p_new= XOR(p,multi(p,2));break;
    }
    return p_new;
}
string Mix_column(string m){
           int s[4][4]={2,3,1,1,
                        1,2,3,1,
                        1,1,2,3,
                        3,1,1,2};
int k=0;
string kq_m="",c;
int j;
while (k<=96)
{
    
    c="00000000";
    for(int x=0;x<=3;x++){
        j=0;
    for (int i = k; i <= k+31; i=i+8)
    {
        if (j<=3)
        {
         string k=multi(m.substr(i,8),s[j][x]);
         c=XOR(c,k);
        }  
        j++;
    }
    kq_m.append(c);
    }
    k+=32;
}
  return kq_m;
}
string AES(string px,string k){
    string bin_px=hex2bin(px);
    Key_Expansion(hex2bin(k),0);
    string add_round=XOR(key_e,bin_px);
    string input_round=add_round.substr(0);
    for (int j = 1; j <= 10; j++)
    {
        /********substitute***************/
    string sub_add="";
    for (int i = 0; i <= 127; i=i+8) {
       string b=S_box(add_round.substr(i,8));
       sub_add.append(b);
     }
    Shift_row(add_round);
    string mix_add=Mix_column(add_round);
    Key_Expansion(k,j);
    string ed_round;
    if(j=!10){
    ed_round=XOR(key_e,mix_add);
    input_round=ed_round;}
    else{
     ed_round=XOR(add_round,key_e);
    }
    }
    return input_round;
}
int main(){
   string plaintex,key;
   cout<<"nhap plaintex: ";
   cin>>plaintex;
   cout<<"nhap key: ";
   cin>>key;
   string bin_plan=hex2bin(plaintex);
   string bin_key=hex2bin(key);
   string result_ecb="";
   for (int i = 0; i <= plaintex.length()/128; i++)
   {
       string sub_plain=plaintex.substr(i,128);
       result_ecb.append(AES(sub_plain,bin_key));
   }
   cout<<"ban ma hoa AES_ECB la:"<<bin2hex(result_ecb)<<endl;
    return 0;
}