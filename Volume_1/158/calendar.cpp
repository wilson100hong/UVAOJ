#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
/*
 * Hint: 
 * 1. Wrap: Consider 1/1 event and current day is 12/31.
 *    The 1/1 event is actually just one day after
 *    12/31. You need to "wrap" the dates.
 *
 * 2. Format: All date (month, date) are in width 3.
 *
 * 3. Ordering: The order is by date, then by priority 
 *    displayed, then by input order. 
 *    Notice if two events on the same day have different 
 *    priority, when asked for that day, these events should 
 *    be ordered by their input order, since the priority 
 *    displayed are both *TODAY*
 *
 */ 
using namespace std;

struct Time{
   int month;
   int date;
};

struct Appointment{
   int offset;
   int priority;
   int index;
   Time time;
};

int CompApt(const Appointment& a1, const Appointment& a2) {
   if (a1.offset == a2.offset) {
      if (a1.priority == a2.priority) {
         return a1.index < a2.index;
      }
      return a1.priority > a2.priority; 
   }
   return a1.offset < a2.offset;
}


int MONTHS[] = {
31, 28, 31, 30, 31, 30,
31, 31, 30, 31, 30, 31};

int MONTHS_LEAP[] = {
31, 29, 31, 30, 31, 30,
31, 31, 30, 31, 30, 31};

int GetOffset(int year, int month, int date) {
   int* months = MONTHS;
   if (year % 4 == 0) 
      months = MONTHS_LEAP;
   int offset = 0;
   
   for (int i = 1; i < month; ++i) 
      offset += months[i - 1];
   offset += date;
   return offset;
}

#define MAX_PRI 100
void PrintStar(int priority) {
   cout << " ";
   if (priority == MAX_PRI)
      cout << "*TODAY*";
   else {
      for (int i = 1; i <= priority; ++i)
         cout << "*";
      for (int i = priority + 1; i <= 7; ++i)
         cout << " ";
   }
   cout << " ";
}

void Remind(const vector<Appointment>& apts, const vector<string>& texts, 
  int year, int month, int date) {
   int offset = GetOffset(year, month, date);
   // 1. Binary search
   int l = 0, h = apts.size() - 1;
   while (l < h) {
      int m = l + (h - l) / 2;
      int pivot = apts[m].offset;
      if (pivot == offset) {
         h = m;
      } else if (pivot < offset) {
         l = m + 1;
      } else {
         h = m - 1;
      }
   }

   cout << "Today is:";
   cout.width(3);
   cout << date;
   cout.width(3);
   cout << month << endl;
   // at this point, l == h
   // 2. Dump until apt.day > day
   for (int i = l; i < apts.size() && apts[i].offset == offset; ++i) {
      cout.width(3);
      cout << apts[i].time.date;
      cout.width(3);
      cout << apts[i].time.month;
      PrintStar(apts[i].priority); 
      cout << texts[apts[i].index] << endl;
   }
}

string trim_leading_ws(string& s) {
   int i = 0;
   int len = s.length();
   while (i < len && s[i] == ' ')
      i++;
   return s.substr(i, len - i);
}

int main() {
   vector<Appointment> apts;
   vector<Time> times;
   vector<string> texts;

   int year, month, date;
   string line;
   cin >> year;
   getline(cin, line);
   while (getline(cin, line) && line != "#") {
      stringstream ss(line);
      char type;
      ss >> type >> date >> month;
      Time time = {month, date};
      int offset = GetOffset(year, month, date);
      
      if (type == 'A') {
         int priority;
         ss >> priority;
         string rest;
         getline(ss, rest);
         string text = trim_leading_ws(rest);
         texts.push_back(text);
 
         Appointment apt;
         apt.offset = offset;
         apt.time = time;
         apt.index = texts.size() - 1;
         apt.priority = MAX_PRI;  
         apts.push_back(apt);
         
         apt.priority = priority;
         do {
            apt.offset--; 
            if (apt.offset == 0) {
               apt.offset = (year % 4 == 0 ? 366: 365);
            }
            apts.push_back(apt);
            apt.priority--;
         } while (apt.priority > 0);

      } else if (type == 'D') {
         times.push_back(time);
      }
   }

   sort(apts.begin(), apts.end(), CompApt);

   for (int i = 0; i < times.size(); ++i)  {
      if (i != 0)
         cout << endl;
      Remind(apts, texts, year, times[i].month, times[i].date);
   }
}
