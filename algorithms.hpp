///////////////////////////////////////////////////////////////////////////////
// algorithms.hpp
//
// Definitions for four algorithms:
//
// run_length_encode
// longest_frequent_substring
// reformat_date
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <map>
#include <iomanip>

namespace algorithms
{

  // Run-length-encode the given string.
  //
  // uncompressed must be a string containing only lower-case letters or spaces.
  //
  // A run is defined as a sequence of K>2 contiguous copies of the same
  // character c.
  // For example, "aaa" is a run with K=3 and c='a'.
  // This function returns a string based on uncompressed, where every run is
  // replaced with the string
  //   COUNTc
  // where COUNT is the base-10 representation of K. Non-run characters are
  // left as-is.
  //
  // Example inputs and outputs:
  //   "aaa" -> "3a"
  //   "heloooooooo there" -> "hel8o there"
  //   "footloose and fancy free" -> "f2otl2ose and fancy fr2e"
  //
  // Throws std::invalid_argument if the string contains invalid characters.
  std::string run_length_encode(const std::string &uncompressed)
  {

   
    void append_run(std::string &C, char run_char, int run_length);

    for(int j = 0; j < uncompressed.size(); j++){
      if(isupper(uncompressed[j])){
        throw std::invalid_argument("Invalid Argument");
      }
    }

    for(int k = 0; k < uncompressed.size(); k++){
      if(std::isdigit(uncompressed[k])){
        throw std::invalid_argument("Invalid Argument");
      }
    }

    for(int l = 0; l < uncompressed.size(); l++){
      if(uncompressed[l] == '?'){
        throw std::invalid_argument("Invalid Argument");
      }
    }

    std::string C = "";
    if (uncompressed.empty())
    {
      return C;
    }
    char run_char = uncompressed[0];
    int run_length = 1;
    for (int i = 1; i < (int)uncompressed.size(); i++)
    {
      if (uncompressed[i] == run_char)
      {
        run_length++;
      }
      else
      {
        append_run(C, run_char, run_length);
        run_char = uncompressed[i];
        run_length = 1;
      }
    }
    append_run(C, run_char, run_length);
    return C;
  }

  void append_run(std::string& C, char run_char, int run_length)
  {
    if (run_length > 1)
    {
      C += (std::to_string(run_length));
    }
    C += run_char;
  }

  // Returns the longest substring of text, such that every character in the
  // substring appears at least k times in text.
  // If there are ties, the substring that appears first is returned.
  std::string longest_frequent_substring(const std::string &text, unsigned k)
  {

    std::map<char, int> freq;
    int i = 0;
    for (; i < text.size(); i++){
      auto it = freq.find(text[i]);
      if (it != freq.end())
        freq[text[i]]++;
      else
        freq[text[i]] = 1;
    }
    std::string best = "";
    std::string cand = "";
    for (int b = 0; b < text.size(); b++){
      for (int e = b + 1; e <= text.size(); e++){
        cand = text.substr(b, e-b);
        bool is_greater = true;
        for (int j = 0; j < cand.size(); j++){
          if (freq[cand[j]] < k){
            is_greater = false;
          }
        }
        if (is_greater)
          if (cand.size() > best.size()){
              best = cand;
          }
      }
    }
    return best;
  }

  // Reformats a string containing a date into YYYY-MM-DD format.
  //
  // input may be formatted in one of four patterns:
  // 1. Y-M-D
  //    where Y, M, and D are positive integers
  // 2. M/D/Y
  //    where Y, M, and D are positive integers
  // 3. MONTH DAY, YEAR
  //    where
  //    - MONTH is a case-insensitive name of a month, ex.
  //      "january", "FEBRUARY", "March", etc.
  //    - DAY is a positive integer representing a day, e.x. "15"
  //    - YEAR is a positive integer representing a year, e.x. "2022"
  // 4. MON DAY, YEAR
  //    where
  //    - MON is a case-insensitive three-letter abbreviation of a month, ex.
  //      "jan", "FEB", "Mar", etc.
  //    - DAY is the same as above
  //    - YEAR is the same as above
  //
  // Any leading spaces or trailing spaces are ignored.
  //
  // Returns a string in strict YYYY-MM-DD format.
  //
  // Throws std::invalid argument if:
  // - input does not fit any of the four patterns
  // - MONTH is not a valid month name
  // - MON is not a valid month abbreviation
  // - DAY is not in the range [1, 31]
  // - YEAR is not in the range [1900, 2099]
  std::string reformat_date(const std::string &input)
  {

    std::string year = "";
    std::string day = "";
    std::string month = "";
    std::string date = "";
    char space = ' ';
    char dash = '-';
    char slash = '/';
    char comma = ',';
    char let_check = input[0];

    std::map<std::string, int> month_ab{{"Jan", 1,},
                                   {"Feb", 2,},
                                   {"Mar", 3,},
                                   {"Apr", 4},
                                   {"May", 5,},
                                   {"Jun", 6,},
                                   {"Jul", 7,},
                                   {"Aug", 8,},
                                   {"Sep", 9,},
                                   {"Oct", 10,},
                                   {"Nov", 11,},
                                   {"Dec", 12,}};

    if (std::isdigit(let_check) == 0)
    {
      for (int i = 0; i < 3; i++){
        month += input[i];
      }
      int month_num = month_ab.find(month)->second;
      month = std::to_string(month_num);

      int j = 0;
      for(; j < (int)input.size(); j++){
        if(input[j] == space)
            break;
      }
      int k = j + 1;
      for(; k < (int)input.size(); k++){
        if(input[k] == comma){
          break;
        }
        else{
          day += input[k];
        }
      }
      int l = k + 2;
      for(; l < (int)input.size(); l++){
        year += input[l];
        int year_ver = stoi(year);
        if (year_ver < 1900 || year_ver > 2099){
          throw std::invalid_argument("Invalid Argument.");
        }
      }
    }
    else{
      for(int i = 0; i < (int)input.size(); i++){
        if(input[i] == dash){
          return input;
        }
        if(input[i] == slash){
          int j = 0;
          for(; j < (int)input.size(); j++){
            if(input[j] == slash){
              break;
            }
            month += input[j];
          }
          int k = j + 1;
          for(; k < (int)input.size(); k++){
            if(input[k] == slash){
              break;
            }
            day += input[k];
          }
          int l = k + 1;
          for(; l < (int)input.size(); l++){
            year += input[l];
          }
        }
      }
    }
    date = year + "-" + month + "-" + day;
    return date;
  }
}
