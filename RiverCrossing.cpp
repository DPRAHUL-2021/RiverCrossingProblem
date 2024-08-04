#include<bits/stdc++.h>
using namespace std;

typedef tuple<char,char,char,char> State;

State initial_state = make_tuple('L','L','L','L');
State goal_state = make_tuple('R','R','R','R');


bool is_valid(State state)
{
    char M,T,G,C;
    tie(M,T,G,C) = state;
    if((T == G && T != M) && (G == C && G != M))
    {
        return false;
    }
    return true;
}

vector<State> get_next_states(State state)
{
    char M,T,G,C;
    tie(M,T,G,C) = state;
    vector<State> next_states;

    // If Man goes alone
    if(M == 'L')
    {
        next_states.push_back(make_tuple('R',T,G,C));
    }
    else
    {
        next_states.push_back(make_tuple('L',T,G,C));
    }

    // If Man takes the Tiger with him
    if(M == T)
    {
        if(M == 'L')
        {
            next_states.push_back(make_tuple('R','R',G,C));
        }
        else
        {
            next_states.push_back(make_tuple('L','L',G,C));
        }
    }

    // If Man takes the Goat with him
    if(M == G)
    {
        if(M == 'L')
        {
            next_states.push_back(make_tuple('R',T,'R',C));
        }
        else
        {
            next_states.push_back(make_tuple('L',T,'L',C));
        }
    }

    // If Man takes the Cabbage with him
    if(M == C)
    {
        if(M == 'L')
        {
            next_states.push_back(make_tuple('R',T,G,'R'));
        }
        else
        {
            next_states.push_back(make_tuple('L',T,G,'L'));
        }
    }

    vector<State> valid_states;
    for(State next_state : next_states)
    {
        if(is_valid(next_state))
        {
            valid_states.push_back(next_state);
        }
    }

    return valid_states;
}

vector<State> solve_puzzle()
{
    queue<pair<State,vector<State>>> q;
    set<State> visited;
    q.push(make_pair(initial_state,vector<State>()));

    while(!q.empty())
    {
        State current_state;
        vector<State> path;
        tie(current_state,path) = q.front();
        q.pop();

        if(visited.find(current_state) != visited.end())
        {
            continue;
        }

        visited.insert(current_state);
        path.push_back(current_state);

        if(current_state == goal_state)
        {
            return path;
        }

        vector<State> next_states = get_next_states(current_state);
        for(State next_state : next_states)
        {
            if(visited.find(next_state) == visited.end())
            {
                q.push(make_pair(next_state,path));
            }
        }
    }
    return vector<State>();
}


int main()
{
    vector<State> solution = solve_puzzle();
    int count = 0;
    if(!solution.empty())
    {
        cout<<"Solution Found : "<<endl;
        for(State step : solution)
        {
            char M,T,G,C;
            tie(M,T,G,C) = step;
            cout<<"("<<M<<", "<<T<<", "<<G<<", "<<C<<")"<<endl;
            count++;
        }
        cout<<"The Number Of Steps Taken To Reach The Goal Are : "<<count<<endl;
    }
    else
    {
        cout<<"No Solution Found"<<endl;
    }
    return 0;
}