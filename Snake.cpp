#include<iostream> // for cin/cout
#include<conio.h> // for getch and key-selection
#include<windows.h> // for delay/sleep
#include<stdlib.h> // for clear 
#include<cstdlib>// for color
using namespace std;

const int width=60; // map width
const int height=23; // map height
int x,y,fruitx,fruity,score; // head,fruit,score
int tailx[100],taily[100],ntail;
enum direction {STOP=0,PAUSE=0,LEFT,RIGHT,UP,DOWN}; // direction
direction dir,temp;
char *name;
int flag,choice,first=0;

void help()
{
	system("cls");
	cout<<"\nFeature Yet Not Available\n";
	cout<<"Updating Soon...\n";
	cout<<"Press any key to return.";
	getch();
	return;
}

void setup() // main interface
{
	system("color 9f");
	system("cls");
	if(first!=1)
	{
		cout<<"\t\t\t\tSnake\n";
		cout<<"\t\t\t\t-----\n";
		cout<<"Please Enter Player Name:";
		name=new char;
		cin>>name;
		first=1;
	}
	system("cls");
	x=width/2;
	y=height/2;
	fruitx=rand()% width;
	fruity=rand()% height;
	score=0;
	ntail=0;
	cout<<"\t\t\t\tSnake\n";
	cout<<"\t\t\t\t-----\n";
	cout<<"Welcome "<<name<<"...\n\n";
	cout<<"--Choose Map/Option--\n";
	cout<<"1. Box\n";
	cout<<"2. Free Way\n";
	cout<<"3. Help\n";
	cout<<"4. Exit\n";
	abc :
	cout<<"Enter Your Choice:";
	cin>>choice;
		switch(choice)
		{
			case 1:
				flag=1;
				break;
			case 2:
				flag=2;
				break;
			case 3:
				help();
				setup();
				break;
			case 4:
				delete name;
				exit(0);
				break;
			default:
				cout<<"Invalid Choice\n";
				goto abc;
				break;
		}
}

void draw() // draw map
{
	system("cls");
	if(flag==1)
	{
		cout<<"\t\t\t\tBox\n";
		cout<<"\t\t\t\t---\n";
	}
	if(flag==2)
	{
		cout<<"\t\t\t\tFree Way\n";
		cout<<"\t\t\t\t--------\n";
	}
	cout<<"Press 's' To Pause And 'n' To Exit The Game.\n";
	int i,j;
	for(i=0;i<width+2;i++)
	{
		cout<<"#";
	}
	cout<<endl;
	for(i=0;i<height;i++)
	{
		bool print=false;
		for(j=0;j<width+2;j++)
		{
			if(j==0)
			{
				cout<<"#";
			}
			if(i==y&&j==x)
			{
				cout<<"0";
			}
			else if(i==fruity&&j==fruitx)
			{
				cout<<"X";
			}
			else
			{
				bool print=false;
				for(int k=0;k<ntail;k++)
				{
					if(tailx[k]==j && taily[k]==i)
					{
						cout<<"o";
						print=true;
					}
				}
				if(!print)
				{
					cout<<" ";
				}
			}
			if(j==width-1)
			{
				cout<<"#";
			}
		}
		cout<<endl;
	}
	for(i=0;i<width+2;i++)
	{
		cout<<"#";
	}
	cout<<endl;
	cout<<"Score:"<<score;
	
}

void pause()
{
	char c;
	temp=dir;
	dir=PAUSE;
	cout<<"\nGame Paused... Press 's' To Resume";
	xyz:
	if(((c=_getch())=='s') || (c=='S'))
	{
		dir=temp;
		return;
	}
	else if((c=='n') || (c=='N'))
	{
		setup();
		return;
	}
	else 
	{
		goto xyz;
	}	
}

void input() // input key
{
	if(_kbhit())
	{
		switch(_getch())
		{
			case 72:
				if(dir!=DOWN)
				{
				dir=UP;
				}
				break;
			case 80:
				if(dir!=UP)
				{
				dir=DOWN;
				}
				break;
			case 75:
				if(dir!=RIGHT)
				{
				dir=LEFT;
				}
				break;
			case 77:
				if(dir!=LEFT)
				{
				dir=RIGHT;
				}
				break;
			case 'n':
				dir=STOP;
				setup();
				break;
			case 'N':
				dir=STOP;
				setup();
				break;
			case 's':
				pause();
				break;
			case 'S':
				pause();
				break;
		}
	}
}

void logic() // games logic
{
	char temp;
	if(dir!=PAUSE)
	{
		int prex=tailx[0];
		int prey=taily[0];
		int pre2x;
		int pre2y;
		tailx[0]=x;
		taily[0]=y;
		for (int i=1;i<ntail;i++)
		{
			pre2x=tailx[i];
			pre2y=taily[i];
			tailx[i]=prex;
			taily[i]=prey;
			prex=pre2x;
			prey=pre2y;
			
		}
	}
	switch(dir)
	{
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		case RIGHT:
			x++;
			break;
		case LEFT:
			x--;
			break;
	}
	if(x==fruitx && y==fruity)
	{
		score++;
		fruitx=rand() % width;
		fruity=rand() % height;
		ntail++;
	}
	if(flag==1)
	{
		if(x>width-1 || x<0 || y>=height || y<0)
		{
			dir=STOP;
			cout<<"\nGame Over!!!";
			cout<<" Press Any Key To Return...";
				getch();
				setup();
		}
		for(int i=0;i<ntail;i++)
		{
			if(tailx[i]==x && taily[i]==y)
			{
				draw();
				dir=STOP;
				cout<<"\nGame Over!!!";			
				cout<<" Press Any Key To Return...";
				getch();
				setup();
			}
		}
	}
	else if(flag==2)
	{
		if(x>width-1) x=0;  else if(x<0) x=width-1;
		if(y>=height) y=0;  else if(y<0) y=height;
		for(int i=0;i<ntail;i++)
		{
			if(tailx[i]==x && taily[i]==y)
			{
				draw();
				dir=STOP;
				cout<<"\nGame Over!!!";
				cout<<" Press Any Key To Return...";
				getch();
				setup();
			}
		}
	}
}

int main()
{
	setup();
	while(1)
	{
		draw();
		input();
		logic();
	}
	return 0;
}
