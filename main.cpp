#include <bits/stdc++.h>
using namespace std;

map<int,vector<int>> master; //key - "new" course id; value - vector of profs

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

    map<int,double> prof_potential; // max courses can be taken by prof, first element prof id second potential
    map<int,string> prof_id; //this stores id of prof as key and stored prof name as value
    map<string,int> rev_prof_id; // this is used when i want to find id of a prof
    map<int,string> course_id; //init after the master input for loop 
    map<string,int> rev_course_id; // used when i want id of a course 
    set<string> courses; //to find unique total courses offered 

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

    map<int, int> new_cid; // key is old course id and value is revised course id, order of new cid -> fdcdc,hdcdc,fdelec,hdelec
    map<int,int > rev_new_cid; //key is revised course id and value is old course id,
    int newid_allocator =  1; //value of current new id to be alloted 
    int column_num = 0;//column currently in use of (say fdcdc map)
    int count = 0;//allows to traverse map and breaks once all elements are traveresed(all vectors and all elements in them)
    while(count < prof_fd_cdc.size())
    {
        count = 0;
        for(auto it = prof_fd_cdc.begin() ; it != prof_fd_cdc.end(); it++ )
        {
            if( (*it).second.size() <= column_num) count++; //count increments seeing a vector size less than column num which ensures complete traversal of that vector 
            else
            {
                if(new_cid[(*it).second[column_num]] == 0) //checks if id has been alloted previously
                {
                    new_cid[(*it).second[column_num]] = newid_allocator; //makes newid
                    rev_new_cid[newid_allocator] = (*it).second[column_num];
                    newid_allocator++;
                }
            }
        }
        column_num++;
    }
    //same as above for rest
    column_num = 0;
    count = 0;
    while(count < prof_hd_cdc.size())
    {
        count = 0;
        for(auto it = prof_hd_cdc.begin() ; it != prof_hd_cdc.end(); it++ )
        {
            if( (*it).second.size() <= column_num) count++;
            else
            {
                if(new_cid[(*it).second[column_num]] == 0)
                {
                    new_cid[(*it).second[column_num]] = newid_allocator;
                    rev_new_cid[newid_allocator] = (*it).second[column_num];
                    newid_allocator++;
                }
            }
        }
        column_num++;
    }
    column_num = 0;
    count = 0;
    while(count < prof_fd_elec.size())
    {
        count = 0;
        for(auto it = prof_fd_elec.begin() ; it != prof_fd_elec.end(); it++ )
        {
            if( (*it).second.size() <= column_num) count++;
            else
            {
                if(new_cid[(*it).second[column_num]] == 0)
                {
                    new_cid[(*it).second[column_num]] = newid_allocator;
                    rev_new_cid[newid_allocator] = (*it).second[column_num];
                    newid_allocator++;
                }
            }
        }
        column_num++;
    }
    column_num = 0;
    count = 0;
    while(count < prof_hd_elec.size())
    {
        count = 0;
        for(auto it = prof_hd_elec.begin() ; it != prof_hd_elec.end(); it++ )
        {
            if( (*it).second.size() <= column_num) count++;
            else
            {
                if(new_cid[(*it).second[column_num]] == 0)
                {
                    new_cid[(*it).second[column_num]] = newid_allocator;
                    rev_new_cid[newid_allocator] = (*it).second[column_num];
                    newid_allocator++;
                }
            }
        }
        column_num++;
    }

    
    // PART - 2 : THE MAN ALGORITHM BEGINS 

    // init master map
    //using above traversal route but updating master at end
    column_num = 0;
    count = 0;
    while(count < prof_fd_cdc.size())
    {
        count = 0;
        for(auto it = prof_fd_cdc.begin() ; it != prof_fd_cdc.end(); it++ )
        {
            if( (*it).second.size() <= column_num) count++;
            else
            {//master updated here to have key as new course id and value as a vector of profs who can take that course
                //also priority order of the profs are maintained due to new course id
                master[new_cid[(*it).second[column_num]]].push_back((*it).first); 
            }
        }
        column_num++;
    }
    column_num = 0;
    count = 0;
    while(count < prof_hd_cdc.size())
    {
        count = 0;
        for(auto it = prof_hd_cdc.begin() ; it != prof_hd_cdc.end(); it++ )
        {
            if( (*it).second.size() <= column_num) count++;
            else
            {
                master[new_cid[(*it).second[column_num]]].push_back((*it).first); 
            }
        }
        column_num++;
    }
    column_num = 0;
    count = 0;
    while(count < prof_fd_elec.size())
    {
        count = 0;
        for(auto it = prof_fd_elec.begin() ; it != prof_fd_elec.end(); it++ )
        {
            if( (*it).second.size() <= column_num) count++;
            else
            {
                master[new_cid[(*it).second[column_num]]].push_back((*it).first); 
            }
        }
        column_num++;
    }
    column_num = 0;
    count = 0;
    while(count < prof_hd_elec.size())
    {
        count = 0;
        for(auto it = prof_hd_elec.begin() ; it != prof_hd_elec.end(); it++ )
        {
            if( (*it).second.size() <= column_num) count++;
            else
            {
                master[new_cid[(*it).second[column_num]]].push_back((*it).first); 
            }
        }
        column_num++;
    }




    


}