#include<bits/stdc++.h>

using namespace std;

struct Bucket{
    int ld=0;
	vector<int>a;
};

map<int,Bucket*> dir;
int gd, bsize;

int Hash(int n){
    int h = n & ((1<<gd) - 1);
    return h;
} 

void create_dir(int gd){
    for (int i = 0;i < pow(2,gd);i++){
        Bucket* newb = new Bucket;
        newb->ld=gd;
        dir.insert(pair<int,Bucket*>(i,newb));
    }
}

void split(int h){
    Bucket* newb = new Bucket;
    vector<int> temp(dir[h]->a.begin(),dir[h]->a.end());
    dir[h]->a.clear();
    for (int i = 0;i < dir.size();i++){
        dir.insert(pair<int,Bucket*>(i ^ (1<<gd),dir[i]));
    }
    if(dir[h]->ld == gd){
        dir[h ^ (1<<gd)] = newb;
        gd++;
        newb->ld = ++ dir[h]->ld;

        for(int i = 0;i < temp.size();i++){
        dir[Hash(temp[i])]->a.push_back(temp[i]);
        }
    }
    else{
        dir[h ^ (1<<dir[h]->ld)] = newb;
        newb->ld = ++ dir[h]->ld;
        for(int i = 0;i < temp.size();i++){
        dir[Hash(temp[i])]->a.push_back(temp[i]);
        }
    }
}

void insert(int n){
    int h = Hash(n);
    if(dir[h]->a.size() < bsize)
		dir[h]->a.push_back(n);
	else
	{
		split(h);
		insert(n);
	}
}

int search(int n)
{
	return count(dir[Hash(n)]->a.begin(),dir[Hash(n)]->a.end(),n);
}

void merge(){
    for(int i = 0; i<(1<<(gd-1));i++)
	{
        if(dir[i] != dir[i ^ (1<<(dir[i]->ld-1))])
		{
            if(dir[i]->a.size() == 0 | dir[i ^ (1<<(dir[i]->ld-1))]->a.size() == 0){
                dir[i]->a.insert(dir[i]->a.end(),dir[i ^ (1<<(dir[i]->ld-1))]->a.begin(),dir[i ^ (1<<(dir[i]->ld-1))]->a.end());
                dir[i ^ (1<<(dir[i]->ld-1))]->a.clear();
                dir[i ^ (1<<(dir[i]->ld-1))] = dir[i];
                dir[i]->ld--;
            }
        }
    }
}

void shrink(void){
    int check = 0;
    for(int i = 0; i<(1<<(gd-1));i++)
	{
        if(dir[i ^ (1<<(dir[i]->ld-1))]->ld == gd){
            check = 1;
            break;
        }    
    }
    if (check == 0){
        gd--;
    }
}

void del(int n)
{
	if(search(n))
	{
		for(auto i : dir)
		{
			auto it = find(i.second->a.begin(),i.second->a.end(),n);
			if(it!=i.second->a.end())
			{
				i.second->a.erase(it);
				break;
			}
		}
		merge();
		shrink();
	}
}

void display(void){
    
    set<Bucket*> cnt;
    for(int i = 0;i < dir.size();i++){
        cnt.insert(dir[i]);
    }
    cout<<gd<<endl<<cnt.size()<<" "<<dir.size()<<endl;
    vector<Bucket*> cnt1 (cnt.begin(),cnt.end());
    for(int i = 0; i < cnt1.size();i++){
        cout<<cnt1[i]->a.size()<<" "<<cnt1[i]->ld<<endl;
    }
}




int main(){
    cin>>gd>>bsize;
    create_dir(gd);
    int choice;
	int n;
	while(1)
	{
		cin>>choice;
		switch(choice)
		{
			case 2:
				cin>>n;
				insert(n);
				break;
			case 3:
				cin>>n;
				if(search(n))
					cout<<"2\n";
				else
					cout<<"3\n";
				break;
            case 4:
				cin>>n;
				del(n);
				break;
			case 5:
				display();
				break;
			case 6:
				exit(0);
			default:
				cout<<"Invalid Input"<<endl;
		}
	}
}
