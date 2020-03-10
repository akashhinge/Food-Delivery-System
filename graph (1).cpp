#include<fstream>
#include<iostream>
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include<math.h>
using namespace std;

ifstream fin("input.txt",ios::in);
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
		friend class graph;
};

class node
{
	string hot_name;
	int x,y;
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
		friend class graph;			
};

class graph
{
	int noofhotels;
	node** head;
	public:
		graph(int n):noofhotels(n)
		{
			head=new node*[noofhotels];
			for(int i=0;i<noofhotels;i++)
			{
				head[i]=NULL;
			}
		}
		void display();
		
		void all_hotels();
		void near_hotels();
		void createGraph();
		void updateRoute();
		void enterloc();
		void searchdish();
		void searchhotel();
		void add_hotels();
		void dijkstras(string,string);
		int getindex(string);	
		void hotel_info(node*,int);	
};

void graph::hotel_info(node* temp,int n)
{
	
	for(int i=0;i<n;i++)
	{
		cout<<"\n enter dish name ";
		fin>>temp->d[i].dishname;
		
		cout<<"\n enter dish cost ";
		fin>>temp->d[i].dishcost;
	}
}
void graph::add_hotels()
{
	int n;
	int x1,y1;
	string hotname;
		
	for(int i=0;i<noofhotels;i++)
	{
		cout<<"\n Enter the Hotel name : ";
		fin>>hotname;
		cout<<"\n enter the no. of dishes of hotel ";
		fin>>n;
		cout<<"\n enter x and y ";
		fin>>x1>>y1;
		node* temp;
		temp=new node(n);
		temp->x=x1;
		temp->y=y1;
		temp->hot_name=hotname;
		hotel_info(temp,n);
		head[i]=temp;
	}	
}

void graph::display()
{
	node* temp;
	cout<<"\n in display \n";
	for(int i=0;i<noofhotels;i++)
	{
		temp=head[i];
		while(temp!=NULL)
		{
			cout<<"\t"<<temp->hot_name<<"-->";
			temp=temp->next;
		}
		cout<<"\n";
	}
	

}
int graph::getindex(string sname)
{
	int i=0;

	while(i<noofhotels && sname!=head[i]->hot_name)
	{
		i++;
	}
	if(i>=noofhotels)
	{
		cout<<"\n enter valid hotel name ";
		return -1;
	}
	else
	{
		return i;
	}	

}
void graph::createGraph()
{
	char ch;
	do
	{
		display();
		cout<<"\n enter source hotel name ";
		string shotel;
		fin>>shotel;
		
		int sindex=getindex(shotel);
		string dhotel;
		int dindex;
		int d;
		if(sindex!=-1)
		{
			cout<<"\n enter destination hotel name ";
			fin>>dhotel;	
			dindex=getindex(dhotel);
		}
		
		if(sindex>=0 && dindex>=0)
		{
			cout<<"\n enter distance : ";
			fin>>d;
			//d=	sqrt(pow(((head[dindex]->x)-(head[sindex]->x)),2)+pow(((head[dindex]->y)-(head[sindex]->y)),2));
			node* curr1;
			curr1=new node(head[dindex]->dishes);
			curr1->distance=d;
			curr1->hot_name=head[dindex]->hot_name;
			for(int i=0;i<head[dindex]->dishes;i++)
			{
				curr1->d[i].dishname=head[dindex]->d[i].dishname;
				curr1->d[i].dishcost=head[dindex]->d[i].dishcost;
			}
			curr1->next=head[sindex]->next;
			head[sindex]->next=curr1;
			
			node* curr2;
			curr2=new node(head[sindex]->dishes);
			curr2->hot_name=head[sindex]->hot_name;
			curr1->distance=d;
			for(int i=0;i<head[sindex]->dishes;i++)
			{
				curr2->d[i].dishname=head[sindex]->d[i].dishname;
				curr2->d[i].dishcost=head[sindex]->d[i].dishcost;
			}
			curr2->next=head[dindex]->next;
			head[dindex]->next=curr2;
			cout<<"\n"<<head[sindex]->hot_name<<"-->"<<head[sindex]->next->hot_name;
			cout<<"\n"<<head[dindex]->hot_name<<"-->"<<head[dindex]->next->hot_name;
		}
		display();
		cout<<"\n Do you want to add more paths?(y/n) ";
		fin>>ch;
	}while(ch=='y' || ch=='Y');	
}

/*void graph::dijskstras(string shotel,string dhotel)
{
	
}*/
int main()
{

	cout<<"\n enter the no of hotels : ";
	int n;
	fin>>n;
	graph g1(n);
	g1.add_hotels();
	g1.createGraph();		
	return 0;
}
