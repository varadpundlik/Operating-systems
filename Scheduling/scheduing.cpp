#include <bits/stdc++.h>
using namespace std;

class Job
{
    int id;
    string name;
    int at;
    int wt;
    int bt;
    int b1;
    int tat;
    int ct;
    int priority;

public:
    Job()
    {
        cout << "Enter Job id :" << endl;
        cin >> id;
        cout << "Enter Job name :" << endl;
        cin >> name;
        cin.ignore();
        cout << "Enter Job Arrival Time : " << endl;
        cin >> at;
        cout << "Enter Job Burst Time :" << endl;
        cin >> bt;
        b1 = bt;
        wt = 0;
        tat = 0;
        ct = 0;
        priority = 0;
    }
    void printJob()
    {
        cout << name << endl;
        cout << "id : " << id << endl;
        cout << "waiting time : " << wt << endl;
        cout << "burst time : " << bt << endl;
        cout << "turn around time : " << tat << endl;
        cout << "completion time : " << ct << endl;
    }
    friend class Scheduler;
};

class Scheduler
{
    int num;
    vector<Job> taskList;
    int avgWT;
    int avgTAT;

public:
    Scheduler()
    {
        cout << "Enter no. of tasks : ";
        cin >> num;
        for (int i = 0; i < num; i++)
        {
            Job j;
            taskList.push_back(j);
        }

        avgTAT = 0;
        avgWT = 0;
    }

    void fcfs()
    {
        int totalWT = 0;
        int totalTAT = 0;
        int wait = 0;

        sort(taskList.begin(), taskList.end(), [](const Job &jl, const Job &jr)
             { return jl.at < jr.at; });

        taskList[0].ct = taskList[0].bt + taskList[0].at;
        taskList[0].tat = taskList[0].ct - taskList[0].at;
        totalTAT += taskList[0].tat;
        wait += taskList[0].ct;

        for (int i = 1; i < num; i++)
        {
            taskList[i].wt = max(taskList[i - 1].ct - taskList[i].at, 0);
            taskList[i].ct = taskList[i].bt + max(taskList[i - 1].ct, taskList[i].at);
            taskList[i].tat = taskList[i].ct - taskList[i].at;
            totalWT += taskList[i].wt;
            totalTAT += taskList[i].tat;
        }

        cout << "Avg. Waiting time : " << (double)totalWT / (double)num << endl;
        cout << "Avg. Turn Around Time : " << (double)totalTAT / (double)num << endl;
        display();
    }

    void sjfPreemptive()
    {
        int totalTAT = 0;
        int totalWT = 0;
        int currentTime = 0;
        int tm = 2;
        int remainingTasks = num;

        int rt[num];
        for (int i = 0; i < num; i++)
        {
            rt[i] = taskList[i].bt;
        }
        int complete = 0, t = 0, minm = INT_MAX;
        int shortest = 0, finish_time;
        bool check = false;

        while (complete != num)
        {
            for (int j = 0; j < num; j++)
            {
                if ((taskList[j].at <= t) &&
                    (rt[j] < minm) && rt[j] > 0)
                {
                    minm = rt[j];
                    shortest = j;
                    check = true;
                }
            }
            if (check == false)
            {
                t++;
                continue;
            }

            // Reduce remaining time by one
            rt[shortest]--;

            // Update minimum
            minm = rt[shortest];
            if (minm == 0)
                minm = INT_MAX;

            // If a process gets completely
            // executed
            if (rt[shortest] == 0)
            {

                // Increment complete
                complete++;
                check = false;

                // Find finish time of current
                // process
                finish_time = t + 1;

                // Calculate waiting time
                taskList[shortest].wt = finish_time -
                               taskList[shortest].bt -
                               taskList[shortest].at;

                if (taskList[shortest].wt < 0)
                    taskList[shortest].wt = 0;
            }
            // Increment time
            t++;
        }

        for (int i = 0; i < num; i++) 
        taskList[i].tat = taskList[i].bt + taskList[i].wt; 

        for(int i = 0; i < num; i++)
        {
            totalTAT += taskList[i].tat;
            totalWT += taskList[i].wt;
        }

        cout << "Avg. Waiting time : " << (double)totalWT / (double)num << endl;
        cout << "Avg. Turn Around Time : " << (double)totalTAT / (double)num << endl;
        display();
    }

    void roundRobin()
    {
        int totalTAT = 0;
        int totalWT = 0;

        queue<int> ready;

        sort(taskList.begin(), taskList.end(), [](const Job &jl, const Job &jr)
             { return jl.at < jr.at; });

        int tm;
        int temp = 0;
        cout << "Enter optimal time : ";
        cin >> tm;

        int t = 0;
        ready.push(0);
        while (!ready.empty())
        {
            int j = ready.front();
            ready.pop();
            temp = t;
            if (taskList[j].b1 < tm)
                t += taskList[j].b1;
            else
                t += tm;
            taskList[j].b1 = max(taskList[j].b1 - tm, 0);

            for (int i = 0; i < num; i++)
            {
                if (taskList[i].at <= t && taskList[i].at > temp && taskList[i].b1 > 0)
                {
                    ready.push(i);
                }
            }

            if (taskList[j].b1 > 0)
            {
                ready.push(j);
            }
            else
            {
                taskList[j].wt = temp;
                taskList[j].ct = t;
                taskList[j].tat = taskList[j].ct - taskList[j].at;
                totalWT += taskList[j].wt;
                totalTAT += taskList[j].tat;
            }
        }
        cout << "Avg. Waiting time : " << (double)totalWT / (double)num << endl;
        cout << "Avg. Turn Around Time : " << (double)totalTAT / (double)num << endl;
    }

    void priorityScheduling()
    {
        acceptPriority();

        int totalTAT = 0;
        int totalWT = 0;
        int currentTime = 0;

        sort(taskList.begin(), taskList.end(), [](const Job &jl, const Job &jr)
             { return jl.at < jr.at; });

        for (int i = 0; i < num; i++)
        {
            if (taskList[i].at > currentTime)
            {
                currentTime = taskList[i].at;
            }

            int shortestPriorityJob = i;
            for (int j = i + 1; j < num; j++)
            {
                if (taskList[j].at <= currentTime && taskList[j].priority < taskList[shortestPriorityJob].priority)
                {
                    shortestPriorityJob = j;
                }
            }

            swap(taskList[i], taskList[shortestPriorityJob]);

            currentTime += taskList[i].bt;
            taskList[i].ct = currentTime;
            taskList[i].tat = taskList[i].ct - taskList[i].at;
            taskList[i].wt = taskList[i].tat - taskList[i].b1;

            totalTAT += taskList[i].tat;
            totalWT += taskList[i].wt;
        }

        cout << "Avg. Waiting time : " << (double)totalWT / (double)num << endl;
        cout << "Avg. Turn Around Time : " << (double)totalTAT / (double)num << endl;
        display();
    }

    void acceptPriority()
    {
        for (auto &i : taskList)
        {
            int pr;
            cout << "Enter priority of " << i.name << " : ";
            cin >> pr;
            i.priority = pr;
        }
    }

    void display()
    {
        cout << "id\tname\tat\tbt\tct\twt\ttat\tpriority" << endl;
        for (auto i : taskList)
        {
            cout << i.id << "\t" << i.name << "\t" << i.at << "\t" << i.bt << "\t" << i.ct << "\t" << i.wt << "\t" << i.tat << "\t" << i.priority << endl;
        }
    }
};

int main()
{
    Scheduler s;

    cout << "By FCFS policy : \n\n";
    s.fcfs();
    cout << "\n\n";

    cout << "\n\nBy SJF policy : \n\n";
    s.sjfPreemptive();
    cout << "\n\n";

    cout << "\n\nBy Priority based scheduling policy : \n\n";
    s.priorityScheduling();
    cout << "\n\n";

    cout << "\n\nBy round robin based scheduling policy : \n\n";
    s.roundRobin();
    cout << "\n\n";
    s.display();

    return 0;
}
