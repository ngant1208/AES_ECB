#include<iostream>
#include<string>
using namespace std;
/************hàm dịch trái**********/
string key="01001011011001010000101110101000011010110101010001101010";
string key_c;
string key_d;
string left_shift(int k, string &key_c, string &key_d){
    static string permuted;
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
   cout<<"sau dich:"<<endl;
   cout<<key_c<<endl;
   cout<<key_d<<endl;
   permuted={key_c[13],key_c[16],key_c[10],key_c[23],key_c[0],key_c[4],key_c[2],key_c[27],
             key_c[14],key_c[5],key_c[20],key_c[9],key_c[22],key_c[18],key_c[11],key_c[3],
             key_c[25],key_c[7],key_c[15],key_c[6],key_c[26],key_c[19],key_c[12],key_c[1],
             key_d[12],key_d[23],key_d[2],key_d[8],key_d[18],key_d[26],key_d[1],key_d[11],
             key_d[22],key_d[16],key_d[4],key_d[19],key_d[15],key_d[20],key_d[10],key_d[27],
             key_d[5],key_d[24],key_d[17],key_d[13],key_d[21],key_d[7],key_d[0],key_d[3]};
    return permuted;
}

int main(){
    string per;
    key_c=key.substr(0,28);
    key_d=key.substr(28,28);
    cout<<"truoc dich: "<<endl;
    cout<<key_c<<endl;
    cout<<key_d<<endl;
    per=left_shift(3,key_c,key_d);
    cout<<"permuted:"<<per<<endl;
    cout<<per.length()<<endl;
    
    /****string Ri="00001110101001101101011010110101";
    string Ri_exp="000000000000000000000000000000000000000000000000";
     int k=0;
    for (int i = 0; i < 8; i++)
    {
       for (int j = (6*i)+1; j <= (6*i)+4; j++)
       {
           int h=j-2*i-1;
           Ri_exp[j]=Ri[h];
           cout<<Ri_exp[j]<<" ";
       }
       cout<<endl;
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
    for (int i = 0; i < 8; i++)
    {
        for (int j = 6*i; j <= 6*i+5; j++)
        {
            cout<<Ri_exp[j]<<" ";

        }
        cout<<endl;
    }****/
    return 0;
}

    std::cout << key << std::endl;