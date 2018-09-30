/*Erick Enriquez 9/29/18
 */

#include<cstring>
#include <string>
#include <iostream>
#include "defns.h"

using namespace std;


// helper functions

bool compare(mlb_stats,mlb_stats,string);//will compare 2 teams  year
bool checkEquality(mlb_stats,mlb_stats,string);
bool compareName(mlb_stats,mlb_stats);// the function checks team name
int findYearIndex(annual_stats*,int,int);// the function looks for a given year in an annual_stats array
float getFloData(mlb_stats,string);//can return any of the float data within the struct
int getIntData(mlb_stats,string);//can return any of the integer fields
string getString(mlb_stats,string);//returns a string
void printField(annual_stats*,int,int,string);//outputs the data of a given year and a given stat
void printField(annual_stats*,mlb_stats*,int,int,string);
int getTeamYear(annual_stats*,mlb_stats,int);//this function will give you the year of a team given an array of teams and a team that you want to look for
void copyTeams(annual_stats*,mlb_stats*,int,int);//this function will copy all of the annual stats data into a team array to use for range
//we will need more functions to do insertion sort, merge sort, ifind, and mfind

//isort function
void iSort(annual_stats*,int,int, string,string);//sorts the field given and order given
void iSort(mlb_stats*,int,string,string);//for sorting and array of mlb_stats

void ifind(annual_stats*,int,int,string,string);
void mfind(annual_stats*,int,int,int,int,string,string);

/*mSort functions for a single year*/
void mSort(annual_stats* ,int left ,int right ,int year,int numberofYears ,string field ,string order );
void merge(annual_stats* ,int left ,int mid ,int right,int year ,int numberOfYears ,string field ,string order );

/*mSort of a range of years*/
void mSort(mlb_stats*,int,int,string,string);
void merge(mlb_stats*,int,int,int,string,string);





int main(){
	//variables
	int y, c ,startYear,endYear,startIndex,endIndex; //will be number of years and number of commands endYear, startYEar, and start and endindex
	string s1,s2,s3,s4,s5,s6; // 5 string variables that we will use to find out what command we want
    mlb_stats* teamArr ; //temp arry we will use to sort a range of years;

	cin>> y ; // read in the number of years that will be read
	int i  = 1;

	annual_stats* tStats = new annual_stats[y];//allocate an array to store the total number of years that we will be using
	//the array will start indexing at 1 to n
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while(i<=y)//while there are still years to read in
	{
		cin>> tStats[i].year>>tStats[i].no_teams;//read in the year we will be testing and the total number of teams

		tStats[i].stats = new mlb_stats[tStats[i].no_teams+1]; //allocate an array to store the number of teams in a given year 1 based

		int j  = 1;
			do{

				cin.getline(tStats[i].stats[j].Team,TEAM_NAME_LEN,'\t');//read in the name of the team until you reach a tab

				//read in all of the info of team j for year i
				cin>>tStats[i].stats[j].League
				>>tStats[i].stats[j].G
				>>tStats[i].stats[j].AB
				>>tStats[i].stats[j].R
				>>tStats[i].stats[j].H
				>>tStats[i].stats[j].B2
				>>tStats[i].stats[j].B3
				>>tStats[i].stats[j].HR
				>>tStats[i].stats[j].RBI
				>>tStats[i].stats[j].BB
				>>tStats[i].stats[j].SO
				>>tStats[i].stats[j].SB
				>>tStats[i].stats[j].CS
				>>tStats[i].stats[j].AVG
				>>tStats[i].stats[j].OBP
				>>tStats[i].stats[j].SLG
				>>tStats[i].stats[j].OPS;

				j++; // increment the count of the inner loop by 1

			}while(j <= tStats[i].no_teams );// loop through and read all of the teams while there are still teams for that year

		i++;// increment the count by 1 for the outer loop
	}//end outer loop

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


cin>>c;//read in the total number of commands we will need
while(c>0){//while there are more commands to do


cin>>s1>>s2;//read in the first 2 lines to see what kind of command we will do
	if(s1 == "isort" && s2 == "range"){//if we are going to do an insertion sort on a range of years
		cin>>s3>>s4>>s5>>s6;//read in start year, end year, field,and order respectively

		 startYear = stoi(s3);//get the start year
		 endYear = stoi(s4);//get the end year
		  int startIndex = findYearIndex(tStats,startYear,y);
		  int endIndex = findYearIndex(tStats,endYear,y);
		  int count = startIndex;
		  int numOfTeams = 0;
		  if(startIndex > endIndex){//if the stats were input in desending years
			  while(count>= endIndex){
				  numOfTeams = numOfTeams + tStats[count].no_teams;
				  count--;
			  }
		  }
		  else if(startIndex < endIndex){
			  while(count <= endIndex){//loop through and add up all of the teams
			  			  numOfTeams = numOfTeams + tStats[count].no_teams;
			  			  count++;
			  	  	  }
		  }
		  teamArr = new mlb_stats[numOfTeams];//allocate a pointer of size numOfTeams
		  copyTeams(tStats,teamArr,startIndex,endIndex);//copy the 2 dimensional data into a 1d array of mlb_stats
		  iSort(teamArr,numOfTeams-1,s5,s6);//sort the range
		  printField(tStats,teamArr,numOfTeams,y,s5);//output the sorted Array of mlb_stats
		  delete[] teamArr;//free the memory allocated for the array
		  teamArr = NULL;//set the pointer to null

	}
	else if(s1 == "isort" && s2 != "range" ){
		cin>>s3>>s4;//read in  field, and order
		int year = stoi(s2);
		iSort(tStats,y,year,s3,s4);//call the isort function
		printField(tStats,year,y,s3);
	}
	else if(s1== "msort" && s2 == "range"){//doing msort on a range of years
		cin>>s3>>s4>>s5>>s6;//read in start year, end year, field, and order
		 startYear = stoi(s3);//get the start year
		 endYear = stoi(s4);//get the end year
		startIndex = findYearIndex(tStats,startYear,y);
	    endIndex = findYearIndex(tStats,endYear,y);
		 int count = startIndex;
		 int numOfTeams = 0;
		 if(startIndex > endIndex){//if the stats were input in desending years
		     while(count>= endIndex){
		         numOfTeams = numOfTeams + tStats[count].no_teams;
		         count--;
		     }
		 }
		 else if(startIndex<endIndex){
		 while(count <= endIndex){//loop through and add up all of the teams
				 numOfTeams = numOfTeams + tStats[count].no_teams;
				count++;
			}
		 }
		teamArr = new mlb_stats[numOfTeams];//allocate a pointer of size numOfTeams
		copyTeams(tStats,teamArr,startIndex,endIndex);//copy the 2 dimensional data into a 1d array of mlb_stats
		mSort(teamArr,0,numOfTeams-1,s5,s6);
		printField(tStats,teamArr,numOfTeams,y,s5);
		delete[] teamArr;//delete the memory allocated for the array
		teamArr = NULL;//set the pointer to null
	}
	else if(s1 == "msort" && s2 != "range"){
		cin>>s3>>s4;//read in field, and order
		int year = stoi(s2);//get the year we will be working on
		int yIndex = findYearIndex(tStats,year,y);//get the index of the year we are working on
		mSort(tStats,1,tStats[yIndex].no_teams,year,y,s3,s4);
		printField(tStats,year,y,s3);
	}
	else if(s1 =="mfind"){//
		cin>>s3>>s4;//read in field and select
		int year = stoi(s2);
		int yIndex = findYearIndex(tStats,year,y);;
		mfind(tStats,1,tStats[yIndex].no_teams,year,y,s3,s4);
	}
	else if(s1 == "ifind"){
		cin>>s3>>s4;//read in field and select;
		int year = stoi(s2);
	ifind(tStats,y,year,s3,s4);
	}

	c--;
}

	return 0;
}//end main


/** the function takes in 3 parameters an array of annual_stats, number of years, and a year,
 *  and checks if the year is in the array and returns its position returns 0 if element isn't in array*/
int findYearIndex(annual_stats* arr,int year,int numOfYears){
	for(int i  = 1;i<=numOfYears;i++){
		if(arr[i].year == year)//if we find a matching year in the array return its index
			return i;
	}
		return 0;// returns 0 if it loops through and can't find it
}

/**this function takes in 2 teams and a field, if t1 is larger than t2 return true
 * else return false, if 2 teams have the same stat then we will check the teamname
 */
bool compare(mlb_stats t1,mlb_stats t2, string field){
//////////////////////////////////////////////////////////////////////////
if(field  == "Team"){
	return(compareName(t1,t2));//calls compare name function and returns result
}
else if(field == "League"){
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
///////////////////////////////////////////////////////////////////////////
else if (field == "G"){
	if(t1.G == t2.G)
	return compareName(t1,t2);
	if(t1.G >t2.G)
		return true;
	else
		return false;
}
else if (field =="AB"){
	if(t1.AB == t2.AB)
	return compareName(t1,t2);
	if(t1.AB > t2.AB)
		return true;
	else
		return false;
}
else if(field == "R"){
	if(t1.R == t2.R)
		return compareName(t1,t2);
	if(t1.R >t2.R)
		return true;
	else
		return false;
}
else if(field == "H"){
	if(t1.H == t2.H)
		return compareName(t1,t2);
	if(t1.H >t2.H)
		return true;
	else
		return false;
}
else if(field == "B2"){
	if(t1.B2 == t2.B2)
		return compareName(t1,t2);
	if(t1.B2 >t2.B2)
		return true;
	else
		return false;
}
else if(field == "B3"){
	if(t1.B3 == t2.B3)
		return compareName(t1,t2);
	if(t1.B3 >t2.B3)
		return true;
	else
		return false;
}
else if(field == "HR"){
	if(t1.HR == t2.HR)
		return compareName(t1,t2);
	if(t1.HR >t2.HR)
		return true;
	else
		return false;
}
else if(field == "RBI"){
	if(t1.RBI == t2.RBI)
		compareName(t1,t2);
	if(t1.RBI >t2.RBI)
		return true;
	else
		return false;
}
else if(field == "BB"){
	if(t1.BB == t2.BB)
		return compareName(t1,t2);
	if(t1.BB >t2.BB)
		return true;
	else
		return false;
}
else if(field == "SO"){
	if(t1.SO == t2.SO)
		return compareName(t1,t2);
	if(t1.SO >t2.SO)
		return true;
	else
		return false;
}
else if(field == "SB"){
	if(t1.SB == t2.SB)
		return compareName(t1,t2);
	if(t1.SB >t2.SB)
		return true;
	else
		return false;
}
else if(field == "CS"){
	if(t1.CS == t2.CS)
		return compareName(t1,t2);
	if(t1.CS >t2.CS)
		return true;
	else
		return false;
}
/////////////////////////////////////////////////////////
else if(field == "AVG"){
	if(t1.AVG == t2.AVG)
		return compareName(t1,t2);
	else if(t1.AVG>t2.AVG)
		return true;
	else
		return false;
}
else if(field == "OBP"){
	if(t1.OBP == t2.OBP)
			return compareName(t1,t2);
		else if(t1.OBP>t2.OBP)
			return true;
		else
			return false;

}
else if(field == "SLG"){
	if(t1.SLG == t2.SLG)
		return compareName(t1,t2);
	else if(t1.SLG>t2.SLG)
		return true;
	else
		return false;

}
else if(field =="OPS"){
	if(t1.OPS == t2.OPS)
		return compareName(t1,t2);
	else if(t1.OPS>t2.OPS)
		return true;
	else
		return false;
}
/////////////////////////////////////////////////////////
return false;//if the field isn't one of the ones
}
/** The function takes in 2 team structs and checks their order alphabetically . returns false if t1 comes before t2 or true if otherwise */
bool compareName(mlb_stats t1,mlb_stats t2){
	if(strncmp(t1.Team,t2.Team,TEAM_NAME_LEN) == -1)
		return false;
	else
		return true;
}

/*this function checks if 2 teams are equal in a given field stat, */
bool checkEquality(mlb_stats t1,mlb_stats t2,string field){
	//////////////////////////////////////////////////////////////////////////
	if(field  == "Team"){
		if(strncmp(t1.Team,t2.Team,TEAM_NAME_LEN) == 0)
			return true;
		else
			return false;
	}
	else if(field == "League"){
	if(strncmp(t1.League,t2.League, LEAGUE_NAME ) == 0)
		return true;
	else
		return false;
	}
	///////////////////////////////////////////////////////////////////////////
	else if (field == "G"){
		if(t1.G == t2.G)
		return true;
		else
			return false;
	}
	else if (field =="AB"){
		if(t1.AB == t2.AB)
		return true;
		else
			return false;
	}
	else if(field == "R"){
		if(t1.R == t2.R)
			return true;
		else
			return false;
	}
	else if(field == "H"){
		if(t1.H == t2.H)
			return true;
		else
			return false;
	}
	else if(field == "B2"){
		if(t1.B2 == t2.B2)
			return true;
		else
			return false;
	}
	else if(field == "B3"){
		if(t1.B3 == t2.B3)
			return true;
		else
			return false;
	}
	else if(field == "HR"){
		if(t1.HR == t2.HR)
			return true;
		else
			return false;
	}
	else if(field == "RBI"){
		if(t1.RBI == t2.RBI)
			return true;
		else
			return false;
	}
	else if(field == "BB"){
		if(t1.BB == t2.BB)
			return true;
		else
			return false;
	}
	else if(field == "SO"){
		if(t1.SO == t2.SO)
			return true;
		else
			return false;
	}
	else if(field == "SB"){
		if(t1.SB == t2.SB)
			return true;
		else
			return false;
	}
	else if(field == "CS"){
		if(t1.CS == t2.CS)
			return true;
		else
			return false;
	}
	/////////////////////////////////////////////////////////
	else if(field == "AVG"){
		if(t1.AVG == t2.AVG)
			return true;
		else
			return false;
	}
	else if(field == "OBP"){
		if(t1.OBP == t2.OBP)
				return true;
			else
				return false;

	}
	else if(field == "SLG"){
		if(t1.SLG == t2.SLG)
			return true;
		else
			return false;

	}
	else if(field =="OPS"){
		if(t1.OPS == t2.OPS)
			return true;
		else
			return false;
	}
		return false;
}

/*this function sorts an year of stats given year, number of years, the field, and the order requested*/
void iSort(annual_stats* arr,int numbOfYears,int year, string field,string order){
	int i ,j;
		mlb_stats key;
		int index = findYearIndex(arr,year,numbOfYears);//find the index of the year in question

		//if the sort is going to be in decreasing order use this implementation
		if(order == "incr"){
			for( i = 2;i<=arr[index].no_teams;i++){
				key = arr[index].stats[i];
				j=i-1;
				while(j>=1 && compare(arr[index].stats[j],key,field)== true){
					arr[index].stats[j+1] = arr[index].stats[j];
					j=j-1;
				}
				arr[index].stats[j+1]=key;
			}

		}
		//if the sort is going to be in increasing order use this implementation
		else{
			if(order == "decr"){
				for( i = 2;i<=arr[index].no_teams;i++){
					key = arr[index].stats[i];
					j=i-1;
					while(j>=1 && compare(arr[index].stats[j],key,field)== false){
						arr[index].stats[j+1] = arr[index].stats[j];
						j=j-1;
					}
					arr[index].stats[j+1]=key;
				}

			}

		}

}

/*this function works on a range of teams and will sort them in order given with respect to field given */
void iSort(mlb_stats* arr,int numOfTeams,string field,string order){
	int i = 0;
	mlb_stats key;
	if(order == "incr"){
		for(int j  = 1 ; j <= numOfTeams;j++){
			key = arr[j];
			i=j-1;
			while(i>=0 && compare(arr[i],key,field)==true){
				arr[i+1] = arr[i];
				i=i-1;
			}
			arr[i+1] = key;
		}

	}
	else if (order == "decr"){
		for(int j  = 1 ; j <= numOfTeams;j++){
					key = arr[j];
					i=j-1;
					while(i>=0 && compare(key,arr[i],field)==true){
						arr[i+1] = arr[i];
						i=i-1;
					}
					arr[i+1] = key;
				}
	}
}

/*this function will sort the array in increasing order then it will give you back the print the select given*/
void ifind(annual_stats* arr,int numOfYears,int year,string field,string select){
	int index = findYearIndex(arr,year,numOfYears);
	int i = arr[index].no_teams;
	int count  = i-1;
	cout<<"\n\n\n";
	iSort(arr,numOfYears,year,field,"incr");//call the iSort function and sort the array
	if(select=="max"){//if the function wants the max go through and check what field they want
		if(field=="Team" || field == "League"){//if the field is one of the strings

						cout<<select<<"\t"<<field<<"\n"<<arr[index].stats[i].Team<<" "<<getString(arr[index].stats[i],field)<<"\n";
						while(count >= 1){
							if(checkEquality(arr[index].stats[i],arr[index].stats[count],field)== true){//if the last team shares the same stats are team[count] print it out
								cout<<arr[index].stats[count].Team<<"\t"<<getString(arr[index].stats[count],field)<<"\n";//print the team and the value of matching stats for a field
							}
							count--;//decrement the count by 1
						}
		}
		//if the field is a float
		else if(field =="AVG" ||field =="OBP" || field =="SLG" || field =="OPS"){
						cout<<select<<"\t"<<field<<"\n"<<arr[index].stats[i].Team<<"\t"<<getFloData(arr[index].stats[i],field)<<"\n";
						while(count >= 1){
							if(checkEquality(arr[index].stats[i],arr[index].stats[count],field)== true){//if the last team shares the same stats are team[count] print it out
								cout<<arr[index].stats[count].Team<<"\t"<<getFloData(arr[index].stats[count],field)<<"\n";//print the team and the value of matching stats for a field
							}
							count--;//decrement the count by 1
						}
		}//if the field is an inr
		else{
			cout<<select<<"\t"<<field<<"\n"<<arr[index].stats[i].Team<<"\t"<<getIntData(arr[index].stats[i],field)<<"\n";
			while(count >= 1){
				if(checkEquality(arr[index].stats[i],arr[index].stats[count],field)== true){//if the last team shares the same stats are team[count] print it out
					cout<<arr[index].stats[count].Team<<"\t"<<getIntData(arr[index].stats[count],field)<<"\n";//print the team and the value of matching stats for a field
				}
				count--;//decrement the count by 1
			}
		}
	}


	else if(select == "min"){
		count = 2;
		if(field=="Team" || field == "League"){
			cout<<select<<"\t"<<field<<"\n"<<arr[index].stats[1].Team<<"\t"<<getString(arr[index].stats[1],field)<<"\n";
					while(count<=i){
							if(checkEquality(arr[index].stats[1],arr[index].stats[count],field)== true){//if the last team shares the same stats are team[count] print it out
								cout<<arr[index].stats[count].Team<<"\t"<<getString(arr[index].stats[count],field)<<"\n";//print the team and the value of matching stats for a field
							}
									count++;//increment the count by 1
				}
		}
		else if(field =="AVG" ||field =="OBP" || field =="SLG" || field =="OPS"){
			cout<<select<<"\t"<<field<<"\n"<<arr[index].stats[1].Team<<"\t"<<getFloData(arr[index].stats[1],field)<<"\n";
											while(count<=i){
												if(checkEquality(arr[index].stats[1],arr[index].stats[count],field)== true){//if the last team shares the same stats are team[count] print it out
													cout<<arr[index].stats[count].Team<<"\t"<<getFloData(arr[index].stats[count],field)<<"\n";//print the team and the value of matching stats for a field
												}
												count++;//increment the count by 1
											}
		}
		else{
			cout<<select<<"\t"<<field<<"\n"<<arr[index].stats[1].Team<<"\t"<<getIntData(arr[index].stats[1],field)<<"\n";
								while(count<=i){
										if(checkEquality(arr[index].stats[1],arr[index].stats[count],field)== true){//if the last team shares the same stats are team[count] print it out
											cout<<arr[index].stats[count].Team<<"\t"<<getIntData(arr[index].stats[count],field)<<"\n";//print the team and the value of matching stats for a field
										}
												count++;//increment the count by 1
							}

		}
	}
	else if(select == "average"){
		if(field =="AVG" ||field =="OBP" || field =="SLG" || field =="OPS"){
			float average = 0.0;
			for(int i = 1;i<=arr[index].no_teams;i++ ){
				average = average + getFloData(arr[index].stats[i],field);
			}
			average = average/arr[index].no_teams;
			cout<<"\n\n\n\n\n" <<arr[index].year << " Average "<< field <<"\n"<< average<<"\n\n\n\n\n\n" ;
		}
		else{
			int average = 0;
					for(int i = 1;i<=arr[index].no_teams;i++ ){
						average = average + getIntData(arr[index].stats[i],field);
					}
					average = average/arr[index].no_teams;
					cout<<"\n\n\n\n\n" <<arr[index].year << " Average "<< field <<"\n"<< average<<"\n\n\n\n\n\n" ;		}
	}
	else{//select is median
		cout<<"median\n";
		if(field=="Team" || field =="League"){
			cout<<getString(arr[index].stats[i/2],field);
		}
		else if(field =="AVG" ||field =="OBP" || field =="SLG" || field =="OPS"){
			cout<<getFloData(arr[index].stats[i/2],field);
		}
		else{
			cout<<getIntData(arr[index].stats[i/2],field);
		}
	}
}

void mfind(annual_stats* arr, int left, int right, int year, int num, string field, string select){
	mSort(arr,left,right,year,num,field,"incr");// sort the array with mergesort
	int index = findYearIndex(arr,year,num);
	int i = arr[index].no_teams;
	int count  = i-1;
	cout<<"\n\n\n";
	if(select=="max"){//if the function wants the max go through and check what field they want
		if(field=="Team" || field == "League"){//if the field is one of the strings

						cout<<select<<"\t"<<field<<"\n"<<arr[index].stats[i].Team<<" "<<getString(arr[index].stats[i],field)<<"\n";
						while(count >= 1){
							if(checkEquality(arr[index].stats[i],arr[index].stats[count],field)== true){//if the last team shares the same stats are team[count] print it out
								cout<<arr[index].stats[count].Team<<"\t"<<getString(arr[index].stats[count],field)<<"\n";//print the team and the value of matching stats for a field
							}
							count--;//decrement the count by 1
						}
		}
		//if the field is a float
		else if(field =="AVG" ||field =="OBP" || field =="SLG" || field =="OPS"){
						cout<<select<<"\t"<<field<<"\n"<<arr[index].stats[i].Team<<"\t"<<getFloData(arr[index].stats[i],field)<<"\n";
						while(count >= 1){
							if(checkEquality(arr[index].stats[i],arr[index].stats[count],field)== true){//if the last team shares the same stats are team[count] print it out
								cout<<arr[index].stats[count].Team<<"\t"<<getFloData(arr[index].stats[count],field)<<"\n";//print the team and the value of matching stats for a field
							}
							count--;//decrement the count by 1
						}
		}//if the field is an inr
		else{
			cout<<select<<"\t"<<field<<"\n"<<arr[index].stats[i].Team<<"\t"<<getIntData(arr[index].stats[i],field)<<"\n";
			while(count >= 1){
				if(checkEquality(arr[index].stats[i],arr[index].stats[count],field)== true){//if the last team shares the same stats are team[count] print it out
					cout<<arr[index].stats[count].Team<<"\t"<<getIntData(arr[index].stats[count],field)<<"\n";//print the team and the value of matching stats for a field
				}
				count--;//decrement the count by 1
			}
		}
	}


	else if(select == "min"){
		count = 2;
		if(field=="Team" || field == "League"){
			cout<<select<<"\t"<<field<<"\n"<<arr[index].stats[1].Team<<"\t"<<getString(arr[index].stats[1],field)<<"\n";
					while(count<=i){
							if(checkEquality(arr[index].stats[1],arr[index].stats[count],field)== true){//if the last team shares the same stats are team[count] print it out
								cout<<arr[index].stats[count].Team<<"\t"<<getString(arr[index].stats[count],field)<<"\n";//print the team and the value of matching stats for a field
							}
									count++;//increment the count by 1
				}
		}
		else if(field =="AVG" ||field =="OBP" || field =="SLG" || field =="OPS"){
			cout<<select<<"\t"<<field<<"\n"<<arr[index].stats[1].Team<<"\t"<<getFloData(arr[index].stats[1],field)<<"\n";
											while(count<=i){
												if(checkEquality(arr[index].stats[1],arr[index].stats[count],field)== true){//if the last team shares the same stats are team[count] print it out
													cout<<arr[index].stats[count].Team<<"\t"<<getFloData(arr[index].stats[count],field)<<"\n";//print the team and the value of matching stats for a field
												}
												count++;//increment the count by 1
											}
		}
		else{
			cout<<select<<"\t"<<field<<"\n"<<arr[index].stats[1].Team<<"\t"<<getIntData(arr[index].stats[1],field)<<"\n";
								while(count<=i){
										if(checkEquality(arr[index].stats[1],arr[index].stats[count],field)== true){//if the last team shares the same stats are team[count] print it out
											cout<<arr[index].stats[count].Team<<"\t"<<getIntData(arr[index].stats[count],field)<<"\n";//print the team and the value of matching stats for a field
										}
												count++;//increment the count by 1
							}

		}
	}
	else if(select == "average"){
		if(field =="AVG" ||field =="OBP" || field =="SLG" || field =="OPS"){
			float average = 0.0;
			for(int i = 1;i<=arr[index].no_teams;i++ ){
				average = average + getFloData(arr[index].stats[i],field);
			}
			average = average/arr[index].no_teams;
			cout<<"\n\n\n\n\n" <<arr[index].year << " Average "<< field <<"\n"<< average<<"\n\n\n\n\n\n" ;
		}
		else{
			int average = 0;
					for(int i = 1;i<=arr[index].no_teams;i++ ){
						average = average + getIntData(arr[index].stats[i],field);
					}
					average = average/arr[index].no_teams;
					cout<<"\n\n\n\n\n" <<arr[index].year << " Average "<< field <<"\n"<< average<<"\n\n\n\n\n\n" ;		}
	}
	else{//select is median
		cout<<"median\n";
		if(field=="Team" || field =="League"){
			cout<<getString(arr[index].stats[i/2],field);
		}
		else if(field =="AVG" ||field =="OBP" || field =="SLG" || field =="OPS"){
			cout<<getFloData(arr[index].stats[i/2],field);
		}
		else{
			cout<<getIntData(arr[index].stats[i/2],field);
		}
	}

}

/*mergeSort function.divides the problem and then will call merge function in order to sort it back*/
void mSort(annual_stats* arr,int left,int right,int year,int numbOfYears,string field,string order){
	int index = findYearIndex(arr,year,numbOfYears);//get the year that we want to sort.
	if(index == 0){//if the index we get it 0 then the return from the function because the year doesn't exist
		cout<<"year not found";
		return;
	}
	if(left<right){
		int mid = (left+right)/2;
		mSort(arr,left,mid,year,numbOfYears,field,order);
		mSort(arr,mid+1,right,year,numbOfYears,field,order);
		merge(arr,left,mid,right,year,numbOfYears,field,order);
	}
}

/*merges the array back in sorted order */
void merge(annual_stats* arr ,int left ,int mid ,int right,int year,int numbOfYears,string field ,string order ){
	int i , j , k ;
	int n1 = mid-left+1 ;
	int n2 = right-mid;
	int index = findYearIndex(arr,year,numbOfYears);
	/*create temp arrays*/
	mlb_stats* L = new mlb_stats[n1];
	mlb_stats* R = new mlb_stats[n2];
	/*copy data to temp arrays L and R*/
	for(i=0;i<n1;i++){
		L[i] = arr[index].stats[left+i];
	}
	for(j=0;j<n2;j++){
		R[j] =arr[index].stats[mid+1+j];
	}
	i=0;
	j=0;
	k=left;
	if(order == "decr"){
	 while(i<n1 && j<n2){
	        if(compare(L[i],R[j],field)==true){//if the right value is less than the left value
	            arr[index].stats[k] = L[i];
	            i++;
	        }
	        else{
	            arr[index].stats[k] = R[j];
	            j++;
	        }
	      k++;
	    }
	    /*copy remaining elements of L[] if they remain*/
	    while(i<n1){
	        arr[index].stats[k] = L[i];
	        i++;
	        k++;
	    }
	    /*copy remaining elements of R[] if they remain*/
	    while(j<n2){
	        arr[index].stats[k] = R[j];
	        j++;
	        k++;
	    }
	}
	else{
		 while(i<n1 && j<n2){
			        if(compare(R[j],L[i],field)==true){//if the right value is less than the right
			            arr[index].stats[k] = L[i];
			            i++;
			        }
			        else{
			            arr[index].stats[k] = R[j];
			            j++;
			        }
			      k++;
			    }
			    /*copy remaining elements of L[] if they remain*/
			    while(i<n1){
			        arr[index].stats[k] = L[i];
			        i++;
			        k++;
			    }
			    /*copy remaining elements of R[] if they remain*/
			    while(j<n2){
			        arr[index].stats[k] = R[j];
			        j++;
			        k++;
			    }
	}
}

/*overloaded mSort function to be used on a range of years*/
void mSort(mlb_stats* arr,int left,int right, string field, string order){
	if(left<right){
	int mid  = (right+left)/2;
	mSort(arr,left,mid,field,order);
	mSort(arr,mid+1,right,field,order);
	merge(arr,left,mid,right,field,order);
	}
}
/*overloaded merge function that sort the 1d array of teams in a range*/
void merge(mlb_stats* arr,int left,int mid, int right,string field,string order){
	int i,j,k;
	int n1 = mid-left+1;
	int n2 = right-mid;
	/*create temp arrays*/
	mlb_stats* L = new mlb_stats[n1];
	mlb_stats* R = new mlb_stats[n2];

	/*copy data to temp arrays L[] and R[]*/
	for(i=0;i<n1;i++){
	    L[i] = arr[left+i];
	}
    for(j = 0;j<n2;j++){
        R[j] = arr[mid+1+j];
    }
    /*merge the temp arrays back into arr[left...right]*/
    i=0;
    j=0;
    k=left;
    if(order == "decr"){
    while(i<n1 && j<n2){
        if(compare(L[i],R[j],field)==true){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
      k++;
    }
    /*copy remaining elements of L[] if they remain*/
    while(i<n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    /*copy remaining elements of R[] if they remain*/
    while(j<n2){
        arr[k] = R[j];
        j++;
        k++;
    }
    }
    else{
         while(i<n1 && j<n2){
        if(compare(R[j],L[i],field)==true){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
      k++;
    }
    /*copy remaining elements of L[] if they remain*/
    while(i<n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    /*copy remaining elements of R[] if they remain*/
    while(j<n2){
        arr[k] = R[j];
        j++;
        k++;
    }
    }
}

/*the function returns the int values of the struct */
int getIntData(mlb_stats t1, string s1){
	if(s1=="G")
		return t1.G;
	else if(s1=="AB")
			return t1.AB;
	else if(s1 == "R")
		return t1.R;
	else if(s1 == "H")
			return t1.H;
	else if(s1 == "B2")
			return t1.B2;
	else if(s1 == "B3")
			return t1.B3;
	else if(s1 =="HR")
			return t1.HR;
	else if (s1 =="RBI")
			return t1.RBI;
	else if(s1 == "BB")
			return t1.BB;
	else if(s1 == "SO")
			return t1.SO;
	else if(s1 == "SB")
			return t1.SB;
	else if(s1 == "CS")
			return t1.CS;
	else
		return -1;
}
/* the function will give you the float values of the struct*/
float getFloData(mlb_stats t1,string s1){
	if(s1=="AVG")
		return t1.AVG;
	else if(s1=="OBP")
		return t1.OBP;
	else if(s1== "SLG")
		return t1.SLG;
	else if(s1=="OPS")
		return t1.OPS;
	else
		return -1.0;
}
/*the function will give you back the char[] fields as strings*/
string getString(mlb_stats t1, string s1){
	if(s1 == "Team")
		return t1.Team;
	else if(s1 == "League")
		return t1.League;
	return NULL;
}

/*this function will print out the team name and field given */
void printField(annual_stats* temp,int year, int num,string s1){
	int i  = findYearIndex(temp,year,num);//get the index of the starting year

	int x = 1;

cout<<"\n\nTeam\t"<< year<<"\t"<<s1<<"\n";


		if(s1 == "Team" || s1 == "League"){//if the field is a String
			while(x<=temp[i].no_teams){
						cout<<temp[i].stats[x].Team<<"\t"<<getString(temp[i].stats[x],s1)<<"\n";
						x++;
						}
		}
		else if(s1 == "AVG" || s1 == "OBP" || s1 == "SLG"|| s1 == "OPS"){//if the field is one of the floats
			while(x<=temp[i].no_teams){
				cout<<temp[i].stats[x].Team<<"\t\t"<<getFloData(temp[i].stats[x],s1)<<"\n";
				x++;
			}
		}
		else{
			while(x <= temp[i].no_teams){
			cout<<temp[i].stats[x].Team<<"\t\t"<<getIntData(temp[i].stats[x],s1)<<"\n";
			x++;
			}
		}
	}

/*this function prints out all of the teams in a given range overloaded for range of years*/
void printField(annual_stats* ptr,mlb_stats* arr,int size,int years,string field){
	int i = 0;
	cout<<"\n\nYear\tTeam\t"<<field<<"\n";
	while(i<size){
		if(field=="Team" || field =="League"){
			cout<<getTeamYear(ptr,arr[i],years)<<" "<<arr[i].Team<<" "<<getString(arr[i],field)<<"\n";
		}
		else if(field == "AVG" || field =="OBP" || field == "SLG" || field == "SLG"){
			cout<<getTeamYear(ptr,arr[i],years)<<" "<<arr[i].Team<<" "<<getFloData(arr[i],field)<<"\n";
		}
		else{
			cout<<getTeamYear(ptr,arr[i],years)<<" "<<arr[i].Team<<" "<<getIntData(arr[i],field)<<"\n";
		}
		i++;
	}
}


/*this function checks an arry of annual stats and compares the team passed in with all of the teams in the annual stats and returns the year in which the team belongs*/
 int getTeamYear(annual_stats* arr,mlb_stats t1,int years){
	int i =1;//starting index of years stored
	int year = 0;
		while(i<=years){
			int j = 1;
			do{
			if(	  strncmp(t1.Team,arr[i].stats[j].Team,TEAM_NAME_LEN) == 0
				&& strncmp(t1.League,arr[i].stats[j].League,LEAGUE_NAME) == 0
				&& t1.G == arr[i].stats[j].G
				&& t1.AB == arr[i].stats[j].AB
				&& t1.R == arr[i].stats[j].R
				&& t1.H == arr[i].stats[j].H
				&& t1.B2 == arr[i].stats[j].B2
				&& t1.B3 == arr[i].stats[j].B3
				&& t1.HR == arr[i].stats[j].HR
				&& t1.RBI == arr[i].stats[j].RBI
				&& t1.BB == arr[i].stats[j].BB
				&& t1.SO == arr[i].stats[j].SO
				&& t1.SB == arr[i].stats[j].SB
				&& t1.CS == arr[i].stats[j].CS
				&& t1.AVG == arr[i].stats[j].AVG
				&& t1.OBP == arr[i].stats[j].OBP
				&& t1.SLG == arr[i].stats[j].SLG
				&& t1.OPS == arr[i].stats[j].OPS
				){
				return arr[i].year;//if the team struct has all of the same members then we can get its year from the annual_stats struct
			}
			else
				j++;

			}while(j<=arr[i].no_teams);
			i++;
}
		return year;
}

/*will copy the data from an array of type annual stats  into an array of mlb_stats*/
void copyTeams(annual_stats* arr,mlb_stats* teams,int startIndex,int endIndex){
	int i  = 0;//starting index for team array
	int k;
	if(startIndex < endIndex){//if the input was put in ascending years
		while(startIndex <= endIndex){
			k=1;
			while(k <=arr[startIndex].no_teams){
				teams[i]= arr[startIndex].stats[k];
				i++;
				k++;
			}
			startIndex++;
	}
	}
	else{
	    while(endIndex <= startIndex){//if the input was put in descending years
	        k=1;
	        while(k <= arr[endIndex].no_teams){
	            teams[i] = arr[endIndex].stats[k];
	            i++;
	            k++;
	        }
	        endIndex++;
	    }
	}

}
