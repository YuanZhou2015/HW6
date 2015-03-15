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
* Github https://github.com/YuanZhou2015/HW6
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

void print(ofstream &outputfile, ofstream &logfile,
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
        print(outputfile, logfile, slog.str(), sout, F);
        sout = inputfilename;
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        sout ="\n";
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(), sout, F);
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
        print(outputfile, logfile, slog.str(), sout, F);
        sout = outputfilename;
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        exit(0);
        return;
    }
}

enum Months{
    January = 1,
    February,
    March,
    April,
    May,
    June,
    July,
    Auguest,
    September,
    October,
    November,
    December
};

Months int_to_months(int m){
    if (m == 1) return January;
    if (m == 2) return February;
    if (m == 3) return March;
    if (m == 4) return April;
    if (m == 5) return May;
    if (m == 6) return June;
    if (m == 7) return July;
    if (m == 8) return Auguest;
    if (m == 9) return September;
    if (m == 10) return October;
    if (m == 11) return November;
    if (m == 12) return December;
    exit (EXIT_FAILURE);
}

string months_to_string(Months m){
    switch(m){
        case January: return "January";
        case February: return "February";
        case March: return "March";
        case April: return "April";
        case May: return "May";
        case June: return "June";
        case July: return "July";
        case Auguest: return "Auguest";
        case September: return "September";
        case October: return "October";
        case November: return "November";
        case December: return "December";
    }
    exit(EXIT_FAILURE);
}

struct Date_format{
    string date;
    string month;
    string year;
};

void set_date(string date, Date_format &Date, stringstream & slog){
    string sout;
    ofstream outputfile, logfile;
    if (date.size()!=10){
        sout ="Invalid date.(Hint: Size should be 10 as 'MM/DD/YYYY or MM-DD-YYYY')\n";
        slog << sout;
        int F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        exit (0);
    }
    if (!isdigit(date[0])||!isdigit(date[1])||!isdigit(date[3])||!isdigit(date[4])
        ||!isdigit(date[6])||!isdigit(date[7])||!isdigit(date[8])||!isdigit(date[9])){
        sout ="Invalid date. (Hint: The date should be numbers.)\n";
        slog << sout;
        int F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        exit(0);
    }   
    if((date[2] != '-' || date[5] != '-')&&(date[2] != '/' || date[5] != '/')){
        sout ="Invalid fomat of date.(Hint: MM/DD/YYYY or MM-DD-YYYY)\n";
        slog << sout;
        int F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        exit(0);
    }
    string d1,d2,d3,d4,d5,d6,d7,d8;
    d1 = date[0];
    d2 = date[1];
    d3 = date[3];
    d4 = date[4];
    d5 = date[6];
    d6 = date[7];
    d7 = date[8];
    d8 = date[9];
    string month = d1+d2, day = d3+d4, year = d5+d6+d7+d8;
    int m = atoi(month.c_str()), d = atoi(day.c_str()), y = atoi(year.c_str());
    // Check on correcness of the date.
    if (y<0){
        sout ="Invalid year.\n";
        slog << sout;
        int F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        exit(0);
    }
    if (m<1 || m>12){
        sout ="Invalid month.(Hint: Month should between 1 to 12.)\n";
        slog << sout;
        int F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        exit(0);
    }
    else{
        month = months_to_string(int_to_months(m)); 
    }
    if ((m == 1||m == 3||m == 5||m == 7||m == 8||m == 10||m == 12)&&(d>31 || d<0)){
        sout ="Invalid date of the month.\n";
        slog << sout;
        int F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        exit(0);    
    }
    if ((m == 4||m == 6||m == 9||m == 11)&&(d>30 || d<0)){
        sout ="Invalid date of the month.\n";
        slog << sout;
        int F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        exit(0);    
    }
    if (m == 2){
        if (((y%4) == 0 && (y%100))||(y%400 == 0)){
            if (d>29||d<0){
                sout ="Invalid date of the month.\n";
                slog << sout;
                int F=2;
                print(outputfile, logfile, slog.str(), sout, F);
                exit(0);
            }
        }
        else{
            if (d>28||d<0){
                sout ="Invalid date of the month.\n";
                slog << sout;
                int F=2;
                print(outputfile, logfile, slog.str(), sout, F);
                exit(0);
            }
        }
    }

    Date.date = day;
    Date.month = month;
    Date.year = year;
    return;
}

void set_time(string time, stringstream & slog){
    string sout;
    ofstream outputfile, logfile;
    if (time.size()!=12){
        sout = "Invalid format of time.(Hint: Size should be 12 as 'hh:mm:ss.fff')\n";
        slog << sout;
        int F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        exit (0);
    }
    if (!isdigit(time[0])||!isdigit(time[1])
        ||!isdigit(time[3])||!isdigit(time[4])
        ||!isdigit(time[6])||!isdigit(time[7])
        ||!isdigit(time[9])||!isdigit(time[10])||!isdigit(time[11])){
        sout = "Invalid time. (Hint: The time should be numbers.)\n";
        slog << sout;
        int F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        exit(0);
    }   
    if(time[2] != ':' || time[5] != ':'||time[8] != '.' ){
        sout = "Invalid fomat of time.(Hint: hh:mm:ss.fff)\n";
        slog << sout;
        int F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        exit(0);
    }
    // Check the corrctness of time.
    string t1,t2,t3,t4,t5,t6,t7,t8,t9;
    t1 = time[0];
    t2 = time[1];
    t3 = time[3];
    t4 = time[4];
    t5 = time[6];
    t6 = time[7];
    t7 = time[9];
    t8 = time[10];
    t9 = time[11];
    string hour = t1+t2, minute = t3+t4, second = t5+t6, ms = t7+t8+t9;
    int h = atoi(hour.c_str()), m = atoi(minute.c_str());
    int s = atoi(second.c_str()), f = atoi(ms.c_str());
    if(h<0||h>23){
        sout ="Invalid hour.\n";
        slog << sout;
        int F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        exit(0);      
    }
    if(m<0||m>59){
        sout ="Invalid minute.\n";
        slog << sout;
        int F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        exit(0);      
    }
    if(s<0||s>59){
        sout ="Invalid second.\n";
        slog << sout;
        int F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        exit(0);      
    }
    if(f<0||f>999){
        sout ="Invalid millisecond.\n";
        slog << sout;
        int F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        exit(0);      
    }    return;
}

void set_timezone(string timezone, stringstream &slog){
    string sout;
    ofstream outputfile, logfile;
    if (timezone.size()!=3){
        sout = "Invalid format of timezone.(Hint: Size should be 3.)\n";
        slog << sout;
        int F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        exit (0);
    }
    if (!isalpha(timezone[0])||!isalpha(timezone[1])||!isalpha(timezone[2])){
        sout = "Invalid format of timezone. (Hint: The timezone should be 3 chars)\n";
        slog << sout;
        int F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        exit(0);
    }
    return;
}

enum magnitude_type{ 
    ML, 
    MS, 
    MB, 
    MW 
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

void set_magnitude(string magnitude, stringstream &slog){
    string sout;
    ofstream outputfile, logfile;
    if(!is_valid_magnitude (magnitude)){
        sout = "Invalid magnitude.\n";
        slog << sout;
        int F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        exit (0);
    }
}

magnitude_type string_to_magnitude_type (string s){
    string ss = uppercase (s);
    if (ss == "ML") return ML;
    if (ss == "MS") return MS;
    if (ss == "MB") return MB;
    if (ss == "MW") return MW;
    exit (EXIT_FAILURE);
}

string itos(int i) {
    stringstream s;
    s << i;
    return s.str();
}

enum Network_code{
    CE,
    CI,
    FA,
    NP,
    WR
};

bool is_valid_network_code(string s){
    return ((s=="CE")||(s=="CI")||(s=="FA")||(s=="NP")||(s=="WR"));
}

void set_networkcode(string networkcode, stringstream &slog, 
                       stringstream &ss, int &i, int &flag){
    string sout;
    ofstream outputfile, logfile;
    int F;
    flag = 0;
    if (networkcode.size()!=2){
        sout = "Entry # ";
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        sout = itos(i);
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        sout = " ignored. Invalid network. \n";
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        flag=1;
    }

    if (!is_valid_network_code(networkcode)){
        sout = "Entry # ";
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        sout =itos (i);
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        sout = " ignored. Invalid network. \n";
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        flag=1;
    }
    return;
}

void set_stationcode(string stationcode,stringstream &slog,
                       stringstream &ss, int &i, int &flag){
    string sout;
    ofstream outputfile, logfile;
    int F;
    flag=0;
    if (stationcode.size()!=3 && stationcode.size()!=5){
        sout = "Entry # ";
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        sout = itos(i);
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        sout = " ignored. Invalid station code. \n";
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        flag=1;
    }

    if (stationcode.size()==3){
        if (!isupper(stationcode[0])||!isupper(stationcode[1])||!isupper(stationcode[2])){
            sout = "Entry # ";
            slog << sout;
            F=2;
            print(outputfile, logfile, slog.str(), sout, F);
            sout =itos (i);
            slog << sout;
            F=2;
            print(outputfile, logfile, slog.str(), sout, F);
            sout = " ignored. Invalid station code. \n";
            slog << sout;
            F=2;
            print(outputfile, logfile, slog.str(), sout, F);
            flag=1;
        }
    }

    if (stationcode.size()==5){
        if (!isdigit(stationcode[0])||!isdigit(stationcode[1])||!isdigit(stationcode[2])
            ||!isdigit(stationcode[3])||!isdigit(stationcode[4])){
            sout = "Entry # ";
            slog << sout;
            F=2;
            print(outputfile, logfile, slog.str(), sout, F);
            sout =itos (i);
            slog << sout;
            F=2;
            print(outputfile, logfile, slog.str(), sout, F);
            sout = " ignored. Invalid station code. \n";
            slog << sout;
            F=2;
            print(outputfile, logfile, slog.str(), sout, F);
            flag=1;
        }
    }
    return;
}

enum Band_type{
    LONGPERIOD,
    SHORTPERIOD,
    BROADBAND
};
bool is_valid_typeofband (string s){
    string ss = uppercase(s);
    return((ss=="LONG-PERIOD")||(ss=="SHORT-PERIOD")||(ss=="BROADBAND"));
}
Band_type string_to_bandtype (string s){
    string ss = uppercase(s);
    if (ss == "LONG-PERIOD") return LONGPERIOD;
    if (ss == "SHORT-PERIOD") return SHORTPERIOD;
    if (ss == "BROADBAND") return BROADBAND;
    exit(EXIT_FAILURE);
}   
string bandtype_to_string (Band_type b){
    switch(b){
        case LONGPERIOD: return "L";
        case SHORTPERIOD: return "B";
        case BROADBAND: return "H";
    }
    exit(EXIT_FAILURE);
}
void set_typeofband(string &typeofband,stringstream &slog,
                      stringstream &ss, int &i, int flag){
    string sout;
    ofstream outputfile, logfile;
    int F;
    flag=0;
    if (!is_valid_typeofband(typeofband)){
        sout = "Entry # ";
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        sout =itos (i);
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        sout = " ignored. Invalid band type. \n";
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        flag=1;    
    }
    if (flag==0){
        typeofband = bandtype_to_string(string_to_bandtype(typeofband));
    }
}

enum Instrument_type{
    HIGHGAIN,
    LOWGAIN,
    ACCELEROMETER
};
bool is_valid_typeofinstru (string s) {
    string ss = uppercase(s);
    return((ss=="HIGH-GAIN")||(ss=="LOW-GAIN")||(ss=="ACCELEROMETER"));
}
Instrument_type string_to_instrutype (string s){
    string ss = uppercase(s);
    if (ss == "HIGH-GAIN") return HIGHGAIN;
    if (ss == "LOW-GAIN") return LOWGAIN;
    if (ss == "ACCELEROMETER") return ACCELEROMETER;
    exit(EXIT_FAILURE);
}   
string instrutype_to_string (Instrument_type instr){
    switch(instr){
        case HIGHGAIN: return "H";
        case LOWGAIN: return "L";
        case ACCELEROMETER: return "N";
    }
    exit(EXIT_FAILURE);
}
void set_typeofinstru(string &typeofinstru,stringstream &slog, 
                        stringstream &ss, int&i, int &flag){
    string sout;
    ofstream outputfile, logfile;
    int F;
    flag=0;
    if (!is_valid_typeofinstru(typeofinstru)){
        sout = "Entry # ";
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        sout =itos (i);
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        sout = " ignored. Invalid type of instrument. \n";
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        flag=1;    
    }
    if (flag==0){
        typeofinstru = instrutype_to_string(string_to_instrutype(typeofinstru));
    }
}

void set_orientation(string orientation,stringstream &slog,
                       stringstream &ss, int &i, int &flag){
    string sout;
    ofstream outputfile, logfile;
    int F,n,j;
    flag=0;
    if (orientation.size()>3||orientation.size()<1){
        sout = "Entry # ";
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        sout = itos(i);
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(), sout, F);
        sout = " ignored. Invalid orientation. \n";
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(), sout, F);
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
                        print(outputfile, logfile, slog.str(), sout, F);
                        sout = itos(i);
                        slog << sout;
                        F=2;
                        print(outputfile, logfile, slog.str(), sout, F);
                        sout = " ignored. Invalid orientation. \n";
                        slog << sout;
                        F=2;
                        print(outputfile, logfile, slog.str(), sout, F);
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
                        print(outputfile, logfile, slog.str(), sout, F);
                        sout = itos(i);
                        slog << sout;
                        F=2;
                        print(outputfile, logfile, slog.str(), sout, F);
                        sout = " ignored. Invalid orientation. \n";
                        slog << sout;
                        F=2;
                        print(outputfile, logfile, slog.str(), sout, F);
                        flag=1;
                        j++;
            }
            else
                j++;
            if (flag==1)break;
        }
    }
}

struct Earthquake{
    string ID;
    Date_format date;
    string time;
    string timezone;
    string earthquake_name;
    string epicenter;
    magnitude_type magnitudetype;
    float magnitude;    
};

struct Station {
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
    string sout, date, information;
    stringstream slog;

    int flag=0,F;
    open_log("yuan.log",logfile);
    logfile.close();
    sout = "> Enter input file name: ";
    F=2;
    print(outputfile, logfile,slog.str(), sout, F);
    cin >> inputfilename;
    if (flag ==1)
    return 0;
    sout = "Opening file: ";
    slog << sout;
    F=2;
    print(outputfile, logfile, slog.str(), sout, F);
    sout =inputfilename;
    slog << sout;
    F=2;
    print(outputfile, logfile, slog.str(),sout, F);
    open_input(inputfilename,inputfile, slog, flag);
    sout = "\nProcessing input...\n";
    slog << sout;
    F=2;
    print(outputfile, logfile, slog.str(),sout, F);
    logfile.close();
    if (flag ==1)
    return 0;
   
    //Reading the header
    Earthquake eqinfor;
    inputfile >> eqinfor.ID;
    inputfile >> date;
    Date_format Date;
    set_date(date,Date,slog);
    inputfile >> eqinfor.time;
    set_time(eqinfor.time,slog);
    inputfile >> eqinfor.timezone;
    set_timezone(eqinfor.timezone,slog);
    //string name;
    getline(inputfile,eqinfor.earthquake_name);
    getline(inputfile,eqinfor.earthquake_name);
    double longitude, latitude,depth;
    inputfile >> longitude >> latitude >> depth;
    stringstream epicenter;
    epicenter << "(" << longitude << ", " << latitude << ", " << depth << ")\n";
    string magnitude;
    inputfile >> magnitude;
    set_magnitude(magnitude, slog);
    eqinfor.magnitudetype = string_to_magnitude_type(magnitude);
    //float magnitudevalue;
    inputfile >> eqinfor.magnitude;
    if (eqinfor.magnitude<0){
        sout =  "invalid magnitude value.\n";
        slog << sout;
        F=2;
        print(outputfile, logfile, slog.str(),sout,F);
        flag = 1;
        return 0;
    }
    eqinfor.epicenter = epicenter.str();

    // If the header read successfully, then open the output file.
    // Print the header information into output file.

    if (flag == 0)
        open_output("yuan.out",outputfile,slog);
    outputfile.close();
    sout = "Header read correctly!\n";
    slog << sout;
    F=2;
    print(outputfile, logfile, slog.str(),sout, F);
    stringstream ss;
    ss << "# " << Date.date <<' '<<  Date.month << ' ' << Date.year <<' ';
    ss << eqinfor.time << ' ' << eqinfor.timezone << ' ';
    ss << eqinfor.magnitudetype << ' ' << eqinfor.magnitude << ' ';
    ss << eqinfor.earthquake_name << "\n";
    ss << "[" << eqinfor.ID <<"] ";
    ss << eqinfor.epicenter;
    F=1;
    print(outputfile, logfile,ss.str(),sout, F);

    // Reading the table of earthquake information. 
    // The number of valid information will not more than 300.

    const int MAXSIZE = 300;
    Station Signaldata[MAXSIZE];
    int size = 0, i, a = 0, flag1 = 0,flag2 = 0,flag3 = 0,flag4 = 0,flag5 = 0;
    string networkcode, stationcode, typeofband, typeofinstru, orientation;
    for(i = 1;inputfile != NULL && size < MAXSIZE; i++){        
        inputfile >> networkcode;
        if(inputfile == NULL)
            break;
        set_networkcode(networkcode,slog,ss,i,flag1);
        inputfile >> stationcode;
        set_stationcode(stationcode,slog,ss,i,flag2);
        inputfile >> typeofband;
        set_typeofband(typeofband,slog,ss,i,flag3);
        inputfile >> typeofinstru;
        set_typeofinstru(typeofinstru,slog,ss,i,flag4);
        inputfile >> orientation;
        int n = orientation.size(), j=0;
        set_orientation(orientation,slog,ss,i,flag5);
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
            a++;    
    }

    // Generat the report for total information read.

    F=2;
    sout ="\nTotal invalid entries igored: ";
    slog << sout;
    print(outputfile, logfile,slog.str(),sout,F); 
    sout =itos(a);
    slog << sout; 
    print(outputfile, logfile,slog.str(),sout,F); 
    sout ="\nTotal valid entries read: ";
    slog << sout;
    print(outputfile, logfile,slog.str(),sout,F);
    sout =itos(i-a-1);
    slog << sout; 
    print(outputfile, logfile,slog.str(),sout,F);
    sout ="\nSignal names produced: ";
    slog << sout;
    print(outputfile, logfile,slog.str(),sout,F);
    sout = itos(size);
    slog << sout <<"\n";
    print(outputfile, logfile,slog.str(),sout,F);
    F=1;
    sout = '\0';
    ss << itos(size) <<"\n";
    print(outputfile, logfile,ss.str(),sout,F);     
    for (int j=0; j< size; j++){
        ss << eqinfor.ID << "." << Signaldata[j].NT << "." << Signaldata[j].STN << "." 
           << Signaldata[j].B << Signaldata[j].I << Signaldata[j].O <<"\n"; 
    }
    F=1;
    print(outputfile, logfile,ss.str(),sout,F); 
    F=2;
    sout = "\nFinished!\n";
    slog << sout;
    print(outputfile, logfile,slog.str(),sout,F);

    return 0;
}