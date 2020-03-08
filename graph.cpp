#include<iostream>
#include<string.h>
#include<stdio.h>
#include<ctype.h>
using namespace std;

class dish
{
	string dishname;
	float dishcost;
	
	public:
		dish()
		{
			dishname="";
			dishcost=0.0f;
		}
		
		friend class node;
};

class node
{
	string hot_name;
	float distance;
	dish *d;
	int dishes;
	node* next;
	
	public:
		node(int n):dishes(n)
		{
			hot_name="";
			distance=0.0f;
			d=new dish[n];
			next=NULL;
		}
		
		void update_info(string);
		void add_info();	
		void menucard();
		friend class graph;			
};

void node::add_info(string name)
{
	for(int i=0;i<n;i++)
	{
		cout<<"\n enter dish name";
		cin>>d[i].dishname;
		
		cout<<"\n enter dish cost";
		cin>>d[i].dishcost;
	}
}

class graph
{
	int noofhotels;
	node* head[noofhotels];
	public:
		graph(int n):noofhotels(n){}
		void all_hotels();
		void near_hotels();
		void createGraph();
		void updateRoute();
		void enterloc();
		void searchdish();
		void searchhotel();
		void add_hotels();
		void dijkstras();
		int getindex(string);				
};

void graph::add_hotels()
{
	for(int i=0;i<noofhotels;i++)
	{
		int n;
		string hotname;
		
		cout<<"\n Enter the Hotel name :";
		cin>>hotname;
		cout<<"\n enter the no. of dishes of hotel ";
		cin>>n;
		node* temp;
		temp=new node(n);
		temp->add_info(hotname);
		head[i]=temp;
	}	
}

int getindex(string sname)
{
	int i=0;
	while(sname!=head[i].hot_name)
	{
		i++;
	}
	if(i>=noofhotels)
	{
		cout<<"\n enter valid hotel name ";
		return -1;
	}
	else
		return i;	
}
void graph::create_graph()
{
	do
	{
		cout<<"\n enter source hotel name";
		string shotel;
		cin>>shotel;
		int sindex=getindex(shotel);
		string dhotel;
		cout<<"\n enter destination hotel name";
		cin>>dhotel;
		int dindex=getindex(dhotel);
		if(sindex>=0 && dindex>=0)
		{
			node* curr;
			curr=new node(head[dindex].dishes);
			for(int i=0;i<head[dindex].dishes;i++)
			{
				curr.d[i].dishname=head[dindex].d[i].dishname;
				curr.d[i].dishcost=head[dindex].d[i].dishcost;
			}
			curr->next=head[sindex]->next;
			head[sindex]->next=curr;
		}
		cout<<"\n Do you want to add more paths?(y/n)";
	}while(ch=='y' || ch='Y');	
}

int main()
{

	return 0;
}
