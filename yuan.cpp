/*Homework 6
*Redoing homework 5 with some minor changes.
*
*The task in this assignment is to read information about station instruments in 
*seismic networks that recorded an earthquake, checking for and reporting errors 
*as you read the input file, and write out a list with validsignals available for
*the given earthquake.
*
*If the header read correctly, the maximum number of valid signals should be 300.
*
* Github 
* by Yuan Zhou
* March 12 2015
*/
#include <stdio.h>
#include <iostream>
#include <string>
#include <ctype.h>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

void print_output(ofstream &outputfile, ofstream &logfile,
                  string str,string termina, int &F){    
    if (F==1){
        outputfile.open("yuan.out");
        outputfile << str;
        outputfile.close();
    }
    if (F==2){
        logfile.open("yuan.log");
        cout << termina;
        logfile << str;
        logfile.close();
    }        
}

void open_log( string logfilename, ofstream &logfile){
    //stringstream ss;
    string information;
    ofstream outputfile;
    logfile.open(logfilename.c_str());
    if (!logfile.is_open() ){
        cout<< "Cannot open log file: "
            << logfilename
            << endl;
        return;
    }
}

void open_input(string inputfilename,ifstream &inputfile,stringstream &slog, int &flag){

    ofstream outputfile, logfile;
    string  sout;

    inputfile.open(inputfilename.c_str());
    if (!inputfile.is_open()){
        sout ="\nCannot open input file: ";
        slog << sout;
        int F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        sout = inputfilename;
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        sout ="\n";
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        flag = 1;
        exit(0);
    } 

    return;
}

void open_output( string outputfilename, ofstream &outputfile, stringstream &slog){
    ofstream logfile;
    string sout;

    outputfile.open(outputfilename.c_str());
    logfile.open("yuan.log");
    if (!outputfile.is_open() ){
        sout ="\nCannot open output file: ";
        slog << sout;
        int F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        sout = outputfilename;
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        exit(0);
        return;
    }
}


void date_check(string date, stringstream & slog){
    string sout;
    ofstream outputfile, logfile;
    if (date.size()!=10){
        sout ="Invalid date.(Hint: Size should be 10 as 'MM/DD/YYYY or MM-DD-YYYY')\n";
        slog << sout;
        int F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        exit (0);
    }
    if (!isdigit(date[0])||!isdigit(date[1])||!isdigit(date[3])||!isdigit(date[4])
        ||!isdigit(date[6])||!isdigit(date[7])||!isdigit(date[8])||!isdigit(date[9])){
        sout ="Invalid date. (Hint: The date should be numbers.)\n";
        slog << sout;
        int F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        exit(0);
    }   
    if((date[2] != '-' || date[5] != '-')&&(date[2] != '/' || date[5] != '/')){
        sout ="Invalid fomat of date.(Hint: MM/DD/YYYY or MM-DD-YYYY)\n";
        slog << sout;
        int F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        exit(0);
    }

    return;
}

string print_out_month(string date){
    if ((date[0]==48) && (date[1]==49))
        return "January ";
    if ((date[0]==48) && (date[1]==50))
        return "February ";
    if ((date[0]==48) && (date[1]==51))
        return "March ";
    if ((date[0]==48) && (date[1]==52))
        return "April ";
    if ((date[0]==48) && (date[1]==53))
        return "May ";
    if ((date[0]==48) && (date[1]==54))
        return "June ";
    if ((date[0]==48) && (date[1]==55))
        return "July ";
    if ((date[0]==48) && (date[1]==56))
        return "August ";
    if ((date[0]==48) && (date[1]==57))
        return "September ";
    if ((date[0]==49) && (date[1]==48))
        return "Ocotobor ";
    if ((date[0]==49) && (date[1]==49))
        return "November ";
    if ((date[0]==49) && (date[1]==50))
        return "December ";
}

void time_check(string time, stringstream & slog){
    string sout;
    ofstream outputfile, logfile;
    if (time.size()!=12){
        sout = "Invalid format of time.(Hint: Size should be 12 as 'hh:mm:ss.fff')\n";
        slog << sout;
        int F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        exit (0);
    }
    if (!isdigit(time[0])||!isdigit(time[1])
        ||!isdigit(time[3])||!isdigit(time[4])
        ||!isdigit(time[6])||!isdigit(time[7])
        ||!isdigit(time[9])||!isdigit(time[10])||!isdigit(time[11])){
        sout = "Invalid time. (Hint: The time should be numbers.)\n";
        slog << sout;
        int F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        exit(0);
    }   
    if(time[2] != ':' || time[5] != ':'||time[8] != '.' ){
        sout = "Invalid fomat of time.(Hint: hh:mm:ss.fff)\n";
        slog << sout;
        int F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        exit(0);
    }

    return;
}

void timezone_check(string timezone, stringstream &slog){
    string sout;
    ofstream outputfile, logfile;
    if (timezone.size()!=3){
        sout = "Invalid format of timezone.(Hint: Size should be 3.)\n";
        slog << sout;
        int F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        exit (0);
    }
    if (!isalpha(timezone[0])||!isalpha(timezone[1])||!isalpha(timezone[2])){
        sout = "Invalid format of timezone. (Hint: The timezone should be 3 chars)\n";
        slog << sout;
        int F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        exit(0);
    }
    return;
}

enum magnitude{ 
    Ml, 
    Ms, 
    Mb, 
    Mw 
};
// useful function to convert a string to uppercase 
string uppercase (string &s){
    string result = s;
    for (int i=0; i<(int)result.size(); i++)
        result[i] = toupper(result[i]);
    return result;
}

bool is_valid_magnitude (string s) {
    string ss = uppercase(s);
    return((ss=="ML")||(ss=="MS")||(ss=="MB")||(ss=="MW"));
}

void magnitude_check(string magnitude, stringstream &slog){
    string sout;
    ofstream outputfile, logfile;
    if(!is_valid_magnitude (magnitude)){
        sout = "Invalid magnitude.\n";
        slog << sout;
        int F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        exit (0);
    }
}

string itos(int i) {
    stringstream s;
    s << i;
    return s.str();
}

void networkcode_check(string networkcode, stringstream &slog, 
                       stringstream &ss, int &i, int &flag){
    string sout;
    ofstream outputfile, logfile;
    int F;
    flag = 0;
    if (networkcode.size()!=2){
        sout = "Entry # ";
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        sout = itos(i);
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        sout = " ignored. Invalid network. \n";
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        flag=1;
    }

    if (networkcode!= "CE" && networkcode!= "CI" && networkcode!="FA" 
        && networkcode!="NP" && networkcode!="WR"){
        sout = "Entry # ";
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        sout =itos (i);
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        sout = " ignored. Invalid network. \n";
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        flag=1;
    }
    return;
}

void stationcode_check(string stationcode,stringstream &slog,
                       stringstream &ss, int &i, int &flag){
    string sout;
    ofstream outputfile, logfile;
    int F;
    flag=0;
    if (stationcode.size()!=3 && stationcode.size()!=5){
        sout = "Entry # ";
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        sout = itos(i);
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        sout = " ignored. Invalid station code. \n";
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        flag=1;
    }

    if (stationcode.size()==3){
        if (!isupper(stationcode[0])||!isupper(stationcode[1])||!isupper(stationcode[2])){
            sout = "Entry # ";
            slog << sout;
            F=2;
            print_output(outputfile, logfile, slog.str(), sout, F);
            sout =itos (i);
            slog << sout;
            F=2;
            print_output(outputfile, logfile, slog.str(), sout, F);
            sout = " ignored. Invalid station code. \n";
            slog << sout;
            F=2;
            print_output(outputfile, logfile, slog.str(), sout, F);
            flag=1;
        }
    }

    if (stationcode.size()==5){
        if (!isdigit(stationcode[0])||!isdigit(stationcode[1])||!isdigit(stationcode[2])
            ||!isdigit(stationcode[3])||!isdigit(stationcode[4])){
            sout = "Entry # ";
            slog << sout;
            F=2;
            print_output(outputfile, logfile, slog.str(), sout, F);
            sout =itos (i);
            slog << sout;
            F=2;
            print_output(outputfile, logfile, slog.str(), sout, F);
            sout = " ignored. Invalid network. \n";
            slog << sout;
            F=2;
            print_output(outputfile, logfile, slog.str(), sout, F);
            flag=1;
        }
    }
    return;
}

bool is_valid_typeofband (string s) {
    string ss = uppercase(s);
    return((ss=="LONG-PERIOD")||(ss=="SHORT-PERIOD")||(ss=="BROADBAND"));
}
void typeofband_check(string &typeofband,stringstream &slog,
                      stringstream &ss, int &i, int flag){
    string sout;
    ofstream outputfile, logfile;
    int F;
    flag=0;
    if (!is_valid_typeofband(typeofband)){
        sout = "Entry # ";
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        sout =itos (i);
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        sout = " ignored. Invalid band type. \n";
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        flag=1;    
    }
    if (flag==0){
        if (uppercase(typeofband)=="LONG-PERIOD"){
            typeofband = "L";
        }
        if (uppercase(typeofband)=="SHORT-PERIOD"){
            typeofband = "B";
        }
        if (uppercase(typeofband)=="BROADBAND"){
            typeofband = "H";
        }
    }

}

bool is_valid_typeofinstru (string s) {
    string ss = uppercase(s);
    return((ss=="HIGH-GAIN")||(ss=="LOW-GAIN")||(ss=="ACCELEROMETER"));
}
void typeofinstru_check(string &typeofinstru,stringstream &slog, 
                        stringstream &ss, int&i, int &flag){
    string sout;
    ofstream outputfile, logfile;
    int F;
    flag=0;
    if (!is_valid_typeofinstru(typeofinstru)){
        sout = "Entry # ";
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        sout =itos (i);
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        sout = " ignored. Invalid type of instrument. \n";
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        flag=1;    
    }
    if (flag==0){
        if (uppercase(typeofinstru)=="HIGH-GAIN"){
            typeofinstru = "H";
        }
        if (uppercase(typeofinstru)=="LOW-GAIN"){
            typeofinstru = "L";
        }
        if (uppercase(typeofinstru)=="ACCELEROMETER"){
            typeofinstru = "N";
        }
    }
}

void orientation_check(string orientation,stringstream &slog,
                       stringstream &ss, int &i, int &flag){
    string sout;
    ofstream outputfile, logfile;
    int F,n,j;
    flag=0;
    if (orientation.size()>3||orientation.size()<1){
        sout = "Entry # ";
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        sout = itos(i);
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        sout = " ignored. Invalid orientation. \n";
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(), sout, F);
        flag=1;
    }
    else{
        j=0;
        n=orientation.size();
        orientation = uppercase (orientation);
        while(j<n){
            if(isdigit(orientation[j]))
                j++;
            else{
                j=0;
                while(j<n){
                    if(isalpha(orientation[j]))
                        j++;
                    else{
                        sout = "Entry # ";
                        slog << sout;
                        F=2;
                        print_output(outputfile, logfile, slog.str(), sout, F);
                        sout = itos(i);
                        slog << sout;
                        F=2;
                        print_output(outputfile, logfile, slog.str(), sout, F);
                        sout = " ignored. Invalid orientation. \n";
                        slog << sout;
                        F=2;
                        print_output(outputfile, logfile, slog.str(), sout, F);
                        flag=1;
                        j++;
                    }
                }
                if(flag==1) break;
            }
        }
        j=0;
        while(j<n){
            if ((orientation[j]!= '1' && orientation[j]!='2' && orientation[j]!= '3')
                &&(orientation[j]!='N' && orientation[j]!='E' && orientation[j]!= 'Z')){
                 sout = "Entry # ";
                        slog << sout;
                        F=2;
                        print_output(outputfile, logfile, slog.str(), sout, F);
                        sout = itos(i);
                        slog << sout;
                        F=2;
                        print_output(outputfile, logfile, slog.str(), sout, F);
                        sout = " ignored. Invalid orientation. \n";
                        slog << sout;
                        F=2;
                        print_output(outputfile, logfile, slog.str(), sout, F);
                        flag=1;
                        j++;
            }
            else
                j++;
            if (flag==1)break;
        }
    }
}

struct Signal {
    string NT;
    string STN;
    string B;
    string I;
    string O;
};

int main(){
    ifstream inputfile;
    ofstream logfile, outputfile;
    string inputfilename, logfilename, outputfilename;
    string sout, EventID, date, time, timezone,information;
    stringstream slog;
  
    int flag=0,F;

    open_log("yuan.log",logfile);
    logfile.close();
    sout = "> Enter input file name: ";
    F=2;
    print_output(outputfile, logfile,slog.str(), sout, F);
    cin >> inputfilename;
    if (flag ==1)
    return 0;
    sout = "Opening file: ";
    slog << sout;
    F=2;
    print_output(outputfile, logfile, slog.str(), sout, F);
    sout =inputfilename;
    slog << sout;
    F=2;
    print_output(outputfile, logfile, slog.str(),sout, F);
    open_input(inputfilename,inputfile, slog, flag);
    sout = "\nProcessing input...\n";
    slog << sout;
    F=2;
    print_output(outputfile, logfile, slog.str(),sout, F);
    logfile.close();
    if (flag ==1)
    return 0;
    inputfile >> EventID;
    inputfile >> date;
    date_check(date,slog);  
    inputfile >> time;
    time_check(time,slog);
    inputfile >> timezone;
    timezone_check(timezone,slog);
    string name;
    getline(inputfile,name);
    getline(inputfile,name);
    double longitude, latitude,depth;
    inputfile >> longitude >> latitude >> depth;
    string magnitude;
    inputfile >> magnitude;
    magnitude_check(magnitude, slog);
    float magnitudevalue;
    inputfile >> magnitudevalue;
    if (magnitudevalue<0){
        sout =  "invalid magnitude value.\n";
        slog << sout;
        F=2;
        print_output(outputfile, logfile, slog.str(),sout,F);
        flag = 1;
        return 0;
    }

    // If the header read successfully, then open the output file.
    // Print the header information into output file.

    if (flag == 0)
        open_output("yuan.out",outputfile,slog);
    outputfile.close();
    sout = "Header read correctly!\n";
    slog << sout;
    F=2;
    print_output(outputfile, logfile, slog.str(),sout, F);
    stringstream ss;
    ss << "# " << date[3] << date[4]<<' ';
    ss << print_out_month(date);
    ss << date[6] << date[7] << date[8] << date[9] <<' ';
    ss << time << ' ' << timezone << ' ';
    ss << magnitude << ' ' << magnitudevalue << ' ';
    ss << name << "\n";
    ss << "[" << EventID <<"] ";
    ss << "(" << longitude << ", " << latitude << ", " << depth << ")\n";
    F=1;
    print_output(outputfile, logfile,ss.str(),sout, F);

    // Reading the table of earthquake information. 
    // The number of valid information will not more than 300.

    const int MAXSIZE = 300;
    Signal Signaldata[MAXSIZE];
    int size = 0, i=1,m=0, flag1=0,flag2=0,flag3=0,flag4=0,flag5=0;
    string networkcode, stationcode, typeofband, typeofinstru, orientation;
    while (inputfile != NULL && size < MAXSIZE ){              
        inputfile >> networkcode;
        networkcode_check(networkcode,slog,ss,i,flag1);
        inputfile >> stationcode;
        stationcode_check(stationcode,slog,ss,i,flag2);
        inputfile >> typeofband;
        typeofband_check(typeofband,slog,ss,i,flag3);
        inputfile >> typeofinstru;
        typeofinstru_check(typeofinstru,slog,ss,i,flag4);
        inputfile >> orientation;
        int n = orientation.size(), j=0;
        orientation_check(orientation,slog,ss,i,flag5);

        if(flag1==0 && flag2==0 && flag3==0 && flag4==0 && flag5==0){
            while (j<n){
                Signaldata[size].NT = networkcode;
                Signaldata[size].STN = stationcode;
                Signaldata[size].B = typeofband;
                Signaldata[size].I = typeofinstru;
                Signaldata[size].O = orientation[j];
                size++;
                j++;
                if (size == 300)
                    break;
            }
        }
        if(flag1!=0 || flag2!=0 || flag3!=0 || flag4!=0 || flag5!=0)
            m++;    
        i++;
    }
    int k=i;
    
    // Generat the report for total information read.

    F=2;
    sout ="\nTotal invalid entries igored: ";
    slog << sout;
    print_output(outputfile, logfile,slog.str(),sout,F); 
    sout =itos(m);
    slog << sout; 
    print_output(outputfile, logfile,slog.str(),sout,F); 
    sout ="\nTotal valid entries read: ";
    slog << sout;
    print_output(outputfile, logfile,slog.str(),sout,F);
    sout =itos(k-m-1);
    slog << sout; 
    print_output(outputfile, logfile,slog.str(),sout,F);
    sout ="\nSignal names produced: ";
    slog << sout;
    print_output(outputfile, logfile,slog.str(),sout,F);
    sout = itos(size);
    slog << sout <<"\n";
    print_output(outputfile, logfile,slog.str(),sout,F);
    F=1;
    sout = '\0';
    ss << itos(size) <<"\n";
    print_output(outputfile, logfile,ss.str(),sout,F);     
    for (int j=0; j< size; j++){
        ss << Signaldata[j].NT << "." << Signaldata[j].STN << "." 
           << Signaldata[j].B << Signaldata[j].I << Signaldata[j].O <<"\n"; 
    }
    F=1;
    print_output(outputfile, logfile,ss.str(),sout,F); 
    F=2;
    sout = "\nFinished!\n";
    slog << sout;
    print_output(outputfile, logfile,slog.str(),sout,F);

    return 0;
}