#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include "setEnvironment.h"
#include "globals.h"
using namespace std;

string SetEnvironment::fileRead(const char* filename){
	 string line ;
	 ifstream myfile (filename);

	 while (!myfile.eof()){
		 string buffer;
		 getline(myfile,buffer);
		 if ((!myfile.eof())&&(buffer.length()==0)){
			 getline(myfile,buffer);
		 }
		line = line + buffer+"!";
	 }
	 if (myfile.eof()){
		 line=line+"!!!!!!!!!!";
	 }
	 return line;
}

University SetEnvironment::makeUniversity(string s){
	University U;
	int i = 10,j,L=s.length();
	while(s[i] == ' ')
		i++;
	j=i;
	while(s[j] != '!')
		j++;
	U.university_name = s.substr(i,j-i);
	i=j+1;
	Department D;
	int dep_no=0;
	Interest I;
	Course C;
	while(i<L){
		if((i+10<L)&&(s.substr(i,10).compare("DEPARTMENT") == 0)){
			i = i+10;
			while(s[i] == ' ')
				i++;
			j=i;
			while(s[j] != ' ')
				j++;
			D.dept_name = s.substr(i,j-i);
			i=j+1;
			while(s[i] == ' ')
				i++;
			j=i;
			while(s[j] != ' ')
				j++;
			D.num_faculty = atoi(s.substr(i,j-i).c_str());
			i=j+1;
			while(s[i] == ' ')
				i++;
			j=i;
			while(s[j] != ' ')
				j++;
			D.num_students_per_year = atoi(s.substr(i,j-i).c_str());
			i=j+1;
			while(s[i] == ' ')
				i++;
			j=i;
			while(s[j] != ' ')
				j++;
			D.semester_dept_courses = atof(s.substr(i,j-i).c_str());
			i=j+1;
			while(s[i] == ' ')
				i++;
			j=i;
			while(s[j] != '!')
				j++;
			D.semester_nondept_courses = atof(s.substr(i,j-i).c_str());
			i=j;
			D.dep_univ =  &U;
			U.department_array.push_back(D);
		}
		else if ((i+8<L)&&(s.substr(i,8).compare("INTEREST") == 0)){
			i = i+8;
			while(s[i]==' ')
				i++;
			j=i;
			while(s[j]!=' ')
				j++;
			I.interest_name = s.substr(i,j-i);
			i=j+1;
			while(s[i] == ' ')
					i++;
			j=i;
			while(s[j] != '!')
				j++;
			I.popularity = atof(s.substr(i,j-i).c_str());
			U.interest_array.push_back(I);
			i=j;
		}
		else if ((i+6<L)&&(s.substr(i,6).compare("COURSE") == 0)){
			i=i+6;
			while(s[i] == ' ')
				i++;
			j=i;
			while(s[j] != ' ')
				j++;
			C.course_name = s.substr(i,j-i);
			i=j+1;
			while(s[i] == ' ')
				i++;
			j=i;
			while(s[j] != ' ')
				j++;
			C.dept_that_offers = s.substr(i,j-i);
			dep_no = 0;
			while(dep_no < U.department_array.size()){
				if((U.department_array[dep_no].dept_name).compare(C.dept_that_offers)==0){
					U.department_array[dep_no].course_array.push_back(C);
					break;
				}
				dep_no++; 
			}
			i=j+1;
			while(s[i] == ' ')
					i++;
			j=i;
			while(s[j] != '!')
				j++;
			C.frequency_per_year = atof(s.substr(i,j-i).c_str());
			i=j;
		}
		else if ((i+6<L)&&(s.substr(i,6).compare("HOSTEL") == 0)){
			i=i+6;
			while(s[i]==' ')
				i++;
			j=i;
			while(s[j] != '!')
				j++;
			U.hostel_name.push_back(s.substr(i,j-i));
			i=j;
		}
		else if ((i+13<L)&&(s.substr(i,13).compare("HOUSELOCALITY") == 0)){
			i=i+13;
			while(s[i]==' ')
				i++;
			j=i;
			while(s[j]!='!')
				j++;
			U.locality_name.push_back(s.substr(i,j-i));
			i=j;
		}
		else if ((i+14<L)&&(s.substr(i,14).compare("FRIENDSHIPRATE") == 0)){
			i=i+14;
			while(s[i]==' ')
				i++;
			j=i;
			while(s[j]!='!')
				j++;
			U.friendship_rate = atof(s.substr(i,j-i).c_str());
			i=j;
		}
		else if ((i+12<L)&&(s.substr(i,12).compare("FRIENDLINESS") == 0)){
			i=i+12;
			while(s[i]==' ')
				i++;
			j=i;
			while(s[j]!='!')
				j++;
			U.friendliness = atof(s.substr(i,j-i).c_str());
			i = j;
		}
		else if ((i+8<L)&&(s.substr(i,8).compare("OPENNESS") == 0)){
			i=i+8;
			while(s[i]==' ')
				i++;
			j=i;
			while(s[j]!='!')
				j++;
			U.openness = atof(s.substr(i,j-i).c_str());
			i = j;
		}
		i++;
	}
	return U;
}

UniversityRandomseedTuple SetEnvironment::separteUniversities(string s){
	unsigned int i=0;
	UniversityRandomseedTuple output;
	vector<University> university_array;
	Randomseed Rand;
	while (i<s.length()){
		if ((i<s.length())&&(s[i]!='U')&&(s[i]!='R')){
			while ((i+10<s.length())&&(s.substr(i,10).compare("UNIVERSITY"))&&(s.substr(i,10).compare("RANDOMSEED"))){
			i++;
			}
		}
		unsigned int j=i+1;
		if ((j<s.length())&&(s[j]!='U')&&(s[j]!='R')){
			while ((j+10<s.length())&&(s.substr(j,10).compare("UNIVERSITY"))&&(s.substr(j,10).compare("RANDOMSEED"))){
			j++;
			}
		}
		string line = s.substr(i,j-i);
		if(line[0] == 'U'){
			university_array.push_back(makeUniversity(line));
		}
		else if(line[0] == 'R')	{
			int k=0,l;
			if(line.substr(0,10).compare("RANDOMSEED")==0){
				k=k+11;
				l=k;
				while(line[l] != ' ')
					l++;
				Rand.faculty_random = atoi(line.substr(k,l-k).c_str());
				k=l+1;
				while(line[k] == ' ')
					k++;
				l=k;
				while(line[l] != ' ')
					l++;
				Rand.student_random = atoi(line.substr(k,l-k).c_str());
				k=l+1;
				while(line[k] == ' ')
					k++;
				l=k;
				while(line[l] != ' ')
					l++;
				Rand.course_random = atoi(line.substr(k,l-k).c_str());
				k=l+1;
				while(line[k] == ' ')
					k++;
				l=k;
				while(line[l] != '!')
					l++;
				Rand.friend_random = atoi(line.substr(k,l-k).c_str());
			}
		}
		i=j;
	}
	output.university_array =university_array ;
	output.randomseed = Rand;
	return output;

}

UniversityRandomseedTuple SetEnvironment::setEnvironment(const char* filename){
	UniversityRandomseedTuple ans = separteUniversities(fileRead(filename));
	return ans;
}

void SetEnvironment::print(UniversityRandomseedTuple w){
	vector<University> a = w.university_array;
	int c=0,q=0,r=0;
	while (c!=a.size()){
		cout<<a[c].university_name<<" "<< a[c].friendliness<<" "<< a[c].friendship_rate<<" "<< a[c].openness<<endl;
		q=0;
		while (q!=a[c].department_array.size()){
			cout<<a[c].department_array[q].dept_name<<" "<<a[c].department_array[q].num_faculty<<" "<<a[c].department_array[q].num_students_per_year<<" "<<a[c].department_array[q].semester_dept_courses<<" "<<a[c].department_array[q].semester_nondept_courses<<endl;
			r=0;
			while(r!=a[c].department_array[q].course_array.size())
			{
				cout<<a[c].department_array[q].course_array[r].course_name<<" ";
				r++;
			}
			cout<<endl;
			q++;
		}
		cout<<endl;
		q=0;
		while (q!=a[c].interest_array.size()){
				cout<<a[c].interest_array[q].interest_name<<" "<<a[c].interest_array[q].popularity<<endl;
				q++;
		}
		cout<<endl;
		q=0;
		cout<<endl;
		q=0;
		while(q!=a[c].hostel_name.size()){
			cout<<a[c].hostel_name[q]<<" ";
			q++;
		}
		cout<<endl<<endl;
		q=0;
		while(q!=a[c].locality_name.size()){
			cout<<a[c].locality_name[q]<<" ";
			q++;
		}
		cout<<endl<<endl;
		c++;
	}
	cout<<w.randomseed.course_random<<" "<<w.randomseed.faculty_random<<" "<<w.randomseed.friend_random<<" "<<w.randomseed.student_random<<endl;
}

