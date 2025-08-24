#include<bits/stdc++.h>
using namespace std;

struct job{
    string id;
    int deadline;
    int profit;
};

bool cmp(job a,job b)
{
    return a.profit>b.profit;
}

pair<vector<string>,int> jobScheduling(vector<job> &jobs)
{
    int i;
    sort(jobs.begin(),jobs.end(),cmp);
    int maxDeadline = 0;
    for(i=0;i<jobs.size();i++)
        maxDeadline = max(maxDeadline,jobs[i].deadline);
    vector<string> slots(maxDeadline+1,"");
    int totalProfit = 0;
    vector<string> scheduledJobs;
    for(i=0;i<jobs.size();i++)
    {
        for(int j=jobs[i].deadline;j>0;j--)
        {
            if(slots[j] == "")
            {
                slots[j] = jobs[i].id;
                scheduledJobs.push_back(jobs[i].id);
                totalProfit+= jobs[i].profit;break;
            }
        }
    }
    return {scheduledJobs,totalProfit};
}

int main()
{
    vector<job> jobs = {
    {"j1",2,100},{"j2",1,19},{"j3",2,27},
    {"j4",1,25},{"j5",3,15},{"j6",5,99}
    };
    pair<vector<string>,int> result = jobScheduling(jobs);
    cout<<"Scheduled jobs: ";
    vector<string> resJobId;
    resJobId = result.first;
    for(int i=0;i<resJobId.size();i++)
    {
        cout<<resJobId[i]<<" ";
    }
    cout<<"\nTotal Profit: "<<result.second<<endl;
}
