#include <iostream>
#include <sstream>
using namespace std;

struct Date{
   int day;   // 1 ~
   int month; // 1 ~ 
   int year;  // 1 ~
};

string WEEK[] = {
   "Sunday", "Monday", "Tuesday", 
   "Wednesday", "Thursday", "Friday", "Saturday"
};

int str2Week(string s) {
   for (int i = 0; i < 7; ++i)
      if (WEEK[i] == s)
         return i;
   return -1;
}
int MONTH_LEN[] = {
   31, 28, 31, 30, 31, 30,
   31, 31, 30, 31, 30, 31
};

int LEAP_MONTH_LEN[] = {
   31, 29, 31, 30, 31, 30,
   31, 31, 30, 31, 30, 31
};

string MONTH[] =  {
   "January", "February", "March", "April",
   "May", "June", "July", "August",
   "September", "October", "November", "December"
}; 

int str2Month(string s) {
   for (int i = 0; i < 12; ++i)
      if (MONTH[i] == s)
         return i + 1;
   return -1;
}

void DumpDate(const Date& date, bool old) {
   cout << date.day;
   if (old)
      cout << "*";
   cout << " " << MONTH[date.month - 1] << " " << date.year << endl;
}

int OldWeek(int diff) {
   // 0001/01/01* is Saturday
   return (6 + diff) % 7;
}

int NewWeek(int diff) {
   // 0001/01/01 is Monday
   return (1 + diff) % 7;
}

int OldDiff(const Date& date) {
   int y = date.year;
   int diff = (y - 1) * 365 + (y - 1) / 4;
   for (int i = 0; i < date.month - 1; ++i)
      diff += MONTH_LEN[i];
   diff += date.day;
   diff--;
   // Is this year has 2/29 and it passed? 
   if (y % 4 == 0 && date.month > 2 )
      diff++;
   return diff;
}

int NewDiff(const Date& date) {
   int y = date.year;
   int diff = (y - 1) * 365 + (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400;
   for (int i = 0; i < date.month - 1; ++i)
      diff += MONTH_LEN[i];
   diff += date.day;
   diff--;
   // Is this year has 2/29 and it passed? 
   bool leap = (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0 );
   if ( leap && date.month > 2 )
      diff++;
   return diff;
}

Date OldDate(int diff) {
   Date date;
   date.day = 1; date.month = 1; date.year = 1;
   // Binary search for year
   // which OldDiff(year) <= diff && OldDiff(year + 1) > dif
   int l = 1, h = 2300;
   bool success = false;
   while (l <= h) {
      int mid = (l + h) / 2;
      date.year = mid;
      Date next_year_date = date;
      next_year_date.year++;
      int tmp_diff = OldDiff(date);
      if (tmp_diff == diff || 
         (tmp_diff < diff && diff < OldDiff(next_year_date))) {
         diff -= tmp_diff;
         success = true;
         break;
      } else if (tmp_diff > diff) {
         h = mid - 1;
      } else { // OldDiff(year) < diff && OldDiff(year + 1) <= diff
         l = mid + 1;  
      }
   }
   if (!success) {
      cout << "BS FAILED!" << endl;
      return date;
   }

   int* month_len = (date.year % 4 == 0 ? LEAP_MONTH_LEN : MONTH_LEN);
   int month = 1;
   while (diff - month_len[month - 1] >= 0) {
      diff -= month_len[month - 1];
      month++;
   }
   date.month = month;
   date.day = diff + 1;
   return date;
}

Date NewDate(int diff) {
   Date date;
   date.day = 1; date.month = 1; date.year = 1;
   // Binary search for year
   // which NewDiff(year) <= diff && NewDiff(year + 1) > dif
   int l = 1, h = 2300;
   bool success = false;
   while (l <= h) {
      int mid = (l + h) / 2;
      date.year = mid;
      Date next_year_date = date;
      next_year_date.year++;
      int tmp_diff = NewDiff(date);
      if (tmp_diff == diff || 
         (tmp_diff < diff && diff < NewDiff(next_year_date))) {
         diff -= tmp_diff;
         success = true;
         break;
      } else if (tmp_diff > diff) {
         h = mid - 1;
      } else { // NewDiff(year) < diff && NewDiff(year + 1) <= diff
         l = mid + 1;  
      }
   }
   if (!success) {
      cout << "BS FAILED!" << endl;
      return date;
   }
   int y = date.year;
   bool leap = (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0 );
   int* month_len = (leap ? LEAP_MONTH_LEN : MONTH_LEN);
   int month = 1;
   while (diff - month_len[month - 1] >= 0) {
      diff -= month_len[month - 1];
      month++;
   }
   date.month = month;
   date.day = diff + 1;
   return date;
}

int main() {
   string line, tmp;
   Date date;
   while (getline(cin, line) && line != "#") {
      stringstream ss(line);
      ss >> tmp;
      cout << tmp << " ";

      int week = str2Week(tmp);
      ss >> date.day;
      ss >> tmp;

      date.month = str2Month(tmp);
      ss >> date.year;
      int old_diff = OldDiff(date);
      int old_week = OldWeek(old_diff);
      int new_diff = NewDiff(date);
      int new_week = NewWeek(new_diff);
      
      /*
      for (int i = old_diff; i <= old_diff + 365 * 600; ++i) {
         cout << WEEK[OldWeek(i)] << " ";
         DumpDate(OldDate(i), true);
      }
      
       for (int i = new_diff; i <= new_diff + 365 * 600; ++i) {
         cout << WEEK[NewWeek(i)] << " ";
         DumpDate(NewDate(i), true);
      }
      */

      if (old_week == week) {
         // re-calculate new date
         new_diff = old_diff - 2;
         date = NewDate(new_diff);
         DumpDate(date, false);
      } else if (new_week == week) {
         // re-calculate old date
         old_diff = new_diff + 2;
         date = OldDate(old_diff);
         DumpDate(date, true);
      }
   }
}
