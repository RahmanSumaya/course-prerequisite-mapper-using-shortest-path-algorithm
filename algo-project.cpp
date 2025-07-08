#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main()
{
    cout<<"Enter the Your Course plan:"<<endl;
    cout<<"Enter the number of course: "<<endl;
    int n,k,cash,month;
    cin>>n;
    string s1,s2;
    unordered_map<string,vector<pair<pair<int,int>,string>>>mp;
    unordered_map<string,bool>visited;
    unordered_set<string> courses;
    for(int i=0; i<n; i++)
    {
        cout<<"Enter the name of Course "<<i+1<<": ";
        cin>>s1;
        cout<<"Enter the number of Courses its followed by: ";
        cin>>k;
        cout<<"Enter the details of those Courses: ";
        courses.insert(s1);
        for(int j=0; j<k; j++)
        {
            cout<<"Enter the name of Course "<<j+1<<": ";
            cin>>s2;
            courses.insert(s2);
            cout<<"Enter the number of months the Course will take to complete: ";
            cin>>month;
            cout<<"Enter the fee the Course: ";
            cin>>cash;
            mp[s1].push_back({{month,cash},s2});
            visited[s1]=false;
        }
    }

    int l,o,p;
    string h;

    unordered_map<string,bool>visited_cp=visited;
    cout<<"How many courses have you completed?"<<endl;
    cin>>o;
    vector<string>completed(o);
here:
    if(o>0)
    {
        cout<<"Enter the names of the courses: "<<endl;
        for(int i=0; i<o; i++)
        {
            cin>>completed[i];
            visited_cp[completed[i]]=true;
        }
    }
there:
    cout<<"Enter the options: \n 1. See Next available courses. \n 2.Have a Fixed Course. \n 3. EXIT"<<endl;
    cin>>l;
    if(l==1)
    {
        cout<<"Next courses available for you: ";
        unordered_map<string,bool>bruh=visited_cp;

        for(auto&u:mp)
        {
            if(visited_cp[u.first]){
            for(auto&[m,v]:u.second)
            {
                if(!bruh[v])
                {
                    cout<<v<<"..... Duration: "<<m.first<<"    Fee: "<<m.second<<endl;
                    bruh[v]=true;
                }
            }}
        }
        cout<<endl;
    }
    else if(l==2)
    {
        unordered_map<string, unordered_map<string, string>> next_course_mon;
        unordered_map<string, unordered_map<string, string>> next_course_taka;
        unordered_map<string,unordered_map<string,int>>fr_mon,fr_taka;
        for(auto &u:courses)
        {
            for(auto &v:courses)
            {
                if(u==v)
                {
                    fr_mon[u][v]=0;
                    fr_taka[u][v]=0;
                }
                else
                {
                    fr_mon[u][v]=INF;
                    fr_taka[u][v]=INF;
                }
            }
        }

        for(auto&u:mp)
        {
            for(auto&[m,v]:u.second)
            {
                fr_mon[u.first][v]=m.first;
                fr_taka[u.first][v]=m.second;
            }
        }
        for(auto& u:courses)
        {
            for(auto& v:courses)
            {
                if (u==v)
                {
                    next_course_mon[u][v]=u;
                    next_course_taka[u][v]=u;
                }
                else if (fr_mon[u][v]<INF)
                {
                    next_course_mon[u][v]=v;
                    next_course_taka[u][v]=v;
                }
                else
                {
                    next_course_mon[u][v]="";
                    next_course_taka[u][v]="";
                }
            }
        }
        for(auto &k:courses)
        {
            for (auto &i:courses)
            {
                for (auto &j:courses)
                {
                    if (fr_mon[i][j]>fr_mon[i][k]+fr_mon[k][j])
                    {
                        fr_mon[i][j]=fr_mon[i][k]+fr_mon[k][j];
                        next_course_mon[i][j]=next_course_mon[i][k];
                    }
                }
            }
        }
        for(auto &k:courses)
        {
            for (auto &i:courses)
            {
                for (auto &j:courses)
                {
                    if (fr_taka[i][j]>fr_taka[i][k]+fr_taka[k][j])
                    {
                        fr_taka[i][j]=fr_taka[i][k]+fr_taka[k][j];
                        next_course_taka[i][j]=next_course_taka[i][k];
                    }
                }
            }
        }
        while(1)
        {
            cout<<"Have a fixed course goal? Choose an option:"<<endl;
            int y;
            cout<<" 1. Least months to complete.\n 2. Least Reg fee to pay.\n";
            cin>>y;
            cout<<"Which Course you wanna do next?"<<endl;
            cin>>h;
            if(visited_cp[h])cout<<"The course is completed"<<endl;
            else
            {
                if(y==2)
                {
                    int m=INF;
                    string start;
                    for(int i=0; i<o; i++)
                    {
                        if(fr_mon[completed[i]][h]<m)
                        {
                            m=fr_mon[completed[i]][h];
                            start=completed[i];
                        }
                    }
                    if(m==INF)cout<<"You can directly start the course."<<endl;
                    else
                    {
                        cout<<m<<" Months to Complete. Following the path: "<<endl;
                        string u=start;
                        cout<<u;
                        while (u != h)
                        {
                            u = next_course_mon[u][h];
                            cout<<"->"<<u;
                        }
                        cout<<endl;
                    }
                }
                else if(y==1)
                {

                    int m=INF;
                    string start;
                    for(int i=0; i<o; i++)
                    {
                        if(fr_taka[completed[i]][h]<m)
                        {
                            m=fr_taka[completed[i]][h];
                            start=completed[i];
                        }
                    }
                    if(m==INF)cout<<"You the course is free."<<endl;
                    else
                    {
                        cout<<m<<"tk Fee to Complete. Following the path: "<<endl;
                        string u=start;
                        cout<<u;
                        while (u != h)
                        {
                            u = next_course_taka[u][h];
                            cout<<"->"<<u;
                        }
                        cout<<endl;
                    }
                }
                else cout<<"INVALID OPTION."<<endl;
            }
            cout<<"Do you want to continue? (y/n): ";
            char c;
            cin>>c;
            if(c=='n')break;
        }
    }
    int hi;
    cout<<"Enter an option: 1. Again\n 2. New Student \n 3. EXIT";
    cin>>hi;
    if(hi==1)goto there;
    else if(hi==2)goto here;
    cout<<"THANK YOU!!!";
    return 0;
}
