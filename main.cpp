#include <bits/stdc++.h>
using namespace std;

int main()
{
    // PART 1 : THE STORING OF INPUT FILES INTO MANY SMALL USEFUL PIECES

     // input from txt
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    // Redirect cin to read from the file
    std::streambuf *orig_cin = std::cin.rdbuf(inputFile.rdbuf());
    int num_of_profs;
    cin>> num_of_profs;
    cin >> ws; //skips first input line

    map<int,double> prof_potential; // max courses taken by prof first element prof id second potential
    map<int,string> prof_id; //this stores id of prof as key and stored prof name as value
    map<string,int> rev_prof_id; // this is used when i want to find id of a prof
    map<int,string> course_id; //init after the master input for loop 
    map<string,int> rev_course_id; // used when i want id of a course 
    set<string> courses; //to find unique courses

    map<int,vector<int>> prof_courses;// key of map is prof id, value is all the courses(id) prof take
    map<int,vector<int>> prof_fd_cdc; // key of map is prof id , vector<int> is vector of course id offered by prof
    map<int,vector<int>> prof_hd_cdc; // same as above
    map<int,vector<int>> prof_fd_elec; // same as above
    map<int,vector<int>> prof_hd_elec; // same as above


    vector<vector<string> > input ; 
    for (int  i = 0; i < num_of_profs ; i++)
    {
        string prof_name;
        double category;
        int fd_cdc,hd_cdc,fd_elec,hd_elec;
        //// 
        string inputLine;
        getline(cin, inputLine);
        vector<string> prof_deets;//this string contain all the inputs as declared in input.txt
        istringstream tokenStream(inputLine);
        string token;
        while (getline(tokenStream, token, ',')) { prof_deets.push_back(token); }
        ////

        input.push_back(prof_deets);

        prof_id[i+1]=prof_deets[0];
        rev_prof_id[prof_deets[0]] = i+1;

        prof_potential[i+1] = stod(prof_deets[1]);

        for (int  i = 2; i < prof_deets.size(); i++)
        {
            int num_of_given_type_course = stoi(prof_deets[i]);
            while(num_of_given_type_course--)
            {
                i++;
                courses.insert(prof_deets[i]);// inserting all the courses in courses set to help make id for courses
            }
        }            
    }

    
    //course_id map init
    int c_id=1;
    for(string s: courses)
    {
        course_id[c_id]=s;
        rev_course_id[s] = c_id;
        c_id++;
    }
    
    //master vector to individual map data copy
    int flag=0; // this is used to distinguish between maps of types of courses
    for (int  i = 0; i < input.size() ; i++)
    {
        flag=0;
        for (int  j = 2; j < input[i].size(); j++)
        {
            flag++;
            int num_of_given_type_course = stoi(input[i][j]);
            while(num_of_given_type_course--)
            {
                j++;
                prof_courses[rev_prof_id[input[i][0]]].push_back(rev_course_id[input[i][j]]);
                if(flag==1)
                {//this just stores course ids of fd cdc of a particular prof(id)
                    prof_fd_cdc[rev_prof_id[input[i][0]]].push_back(rev_course_id[input[i][j]]);
                }
                else if(flag==2)
                {
                    //same as above
                    prof_hd_cdc[rev_prof_id[input[i][0]]].push_back(rev_course_id[input[i][j]]);
                }
                else if(flag==3)
                {//same as above
                    prof_fd_elec[rev_prof_id[input[i][0]]].push_back(rev_course_id[input[i][j]]);
                }
                else if(flag==4)
                {//same as above
                    prof_hd_elec[rev_prof_id[input[i][0]]].push_back(rev_course_id[input[i][j]]);
                }
            }
        }
        
    }

     for(auto pr : prof_courses)
    {
        cout<<pr.first<<endl;
        for (int  i = 0; i < pr.second.size() ; i++)
        {
            cout<<pr.second[i]<<" ";
        }cout<<endl;        
    }cout<<endl;
    // PART - 2 : THE MAN ALGORITHM BEGINS 



    


}