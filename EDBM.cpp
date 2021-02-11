/*Author: Md. Anuvob Pradan
Date: 15-09-2019
*/
#include<iostream>
#include<string.h>
#include <cstdlib>
#include <ctime>
#include<math.h>
#include<windows.h>
using namespace std;
char correctCW[20];
char s_error[20];
char d_error[20];
int r;//Number of Parity
class sender
{
public:
    int n;//Cordword Size
    int m;//Number of actual data

public:
    int get_codeword_size(char data_c[30])
    {
        r=0;

        m=strlen(data_c);
        //Number of Parity Calculation
        while(1)
        {
            if(pow(2,r)>=(m+r+1))
                break;

            r++;
        }
        n=m+r;
        return n;
    }

    void set_parity_position(char data_c[20])
    {
        int j=0,k,i;
        k=m-1;

        for(i=1; i<=n; i++)
        {
            int p=pow(2,j);
            if(i%p==0)
            {
                correctCW[i]='0';
                j++;
            }
            else
            {
                correctCW[i]=data_c[k];
                k--;

            }
        }
    }

    void generate_codeword(int p_t_c)
    {
        int i,k,j,count,p;
        for(i=0; i<=r-1; i++)
        {
            count=0;
            p=pow(2,i);
            k=0;
            for(j=0; j<=n; j++)
            {

                if(k==1)
                {
                    if(correctCW[j]=='1')
                        count++;

                    if((j+1)%p==0)
                        k=0;
                }
                else if(k==0)
                {
                    if((j+1)%p==0)
                        k=1;
                }

            }

            if(p_t_c==0 && count%2!=0)
            {
                correctCW[p]='1';

            }

            else if(p_t_c==1 && count%2==0)
            {
                correctCW[p]='1';
            }
        }
        cout<<"\n\t\t\t\tGenerated codeword    : ";
        for(i=n; i>=1; i--)
        {
            cout<<correctCW[i];
        }

    }


};

class receiver
{
public:
    int pos[10];
    int error_index;

public:
    void receive(char data_c[20],int n,int parity)
    {
        int i,k,j,count,p,index=0;
        for(i=0; i<=r-1; i++)
        {
            count=0;
            p=pow(2,i);
            k=0;
            for(j=0; j<=n; j++)
            {

                if(k==1)
                {
                    if(data_c[j]=='1')
                        count++;

                    if((j+1)%p==0)
                        k=0;
                }
                else if(k==0)
                {
                    if((j+1)%p==0)
                        k=1;
                }




            }


            if(parity==0)
            {
                if(count%2!=0)
                {

                    pos[index]=1;
                    index++;

                }
                else
                {
                    pos[index]=0;
                    index++;
                }
            }

            if(parity==1)
            {
                if(count%2==0)
                {
                    pos[index]=1;
                    index++;

                }

                else
                {
                    pos[index]=0;
                    index++;
                }
            }


        }//end of loop

        for(i=0; i<r; i++)
        {
            error_index=error_index+(pos[i]*pow(2,i));

        }

        if(error_index==0)
        {
            cout<<"\nThere is no error detected in codeword!";
        }

        else
        {
            cout<<"\nThere is error detected in codeword on "<<error_index<<"th index!";
        }
    }

};

void single_error(int n)
{
    int i,random_index;
    for(i=1; i<=n; i++)
    {
        s_error[i]=correctCW[i];
    }
    srand((unsigned)time(0));

    random_index = (rand()%n)+1;

    if(s_error[random_index]=='0')
    {
        s_error[random_index]='1';

    }
    else
    {
        s_error[random_index]='0';
    }

    cout<<"\n\t\t\t\tOne Bit error codeword: ";
    for(i=n; i>=1; i--)
    {
        cout<<s_error[i];
    }


}


void double_error(int n)
{
    int i,random_index,random_index2;
    for(i=1; i<=n; i++)
    {
        d_error[i]=correctCW[i];
    }
    srand((unsigned)time(0));

    random_index = (rand()%n)+1;

    if(d_error[random_index]=='0')
    {
        d_error[random_index]='1';

    }

    else
    {
        d_error[random_index]='0';
    }

    while(1)
    {
        random_index2 = (rand()%n)+1;
        if(random_index2!=random_index)
        {
            if(d_error[random_index2]=='0')
            {
                d_error[random_index2]='1';

            }

            else
            {
                d_error[random_index2]='0';
            }

            break;
        }

    }

    cout<<"\n\t\t\t\tTwo Bit error codeword: ";
    for(i=n; i>=1; i--)
    {
        cout<<d_error[i];
    }


}


int main()
{
    char data[30];
    int word_size;
    int p_t;
    cout<<"\n\t\t\t\t\tWelcome to my project code!";
    cout<<"\n\nEnter Data in binary:";
    cin>>data;
    cout<<"\nEnter Parity type(0 for even and 1 for odd):";
    cin>>p_t;
    sender s;
    receiver r;
    word_size=s.get_codeword_size(data);
    s.set_parity_position(data);
    s.generate_codeword(p_t);
    single_error(word_size);
    double_error(word_size);
    cout<<"\nReceiving.";
    Sleep(0700);
    cout<<".";
    Sleep(0700);
    cout<<".";
    Sleep(0700);
    cout<<".";
    Sleep(0700);
    cout<<".";
    cout<<"\n\nAfter sending correct codeword at receiver:";
    r.receive(correctCW,word_size,p_t);
    cout<<"\n\nAfter sending one bit error codeword at receiver:";
    r.receive(s_error,word_size,p_t);
    cout<<"\n\nAfter sending two bit codeword at receiver:";
    r.receive(d_error,word_size,p_t);
    cout<<endl;

    return 0;
}
