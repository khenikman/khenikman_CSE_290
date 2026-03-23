#ifndef COURSEGRADEBOOK_H
#define COURSEGRADEBOOK_H

#include <algorithm>
#include "Gradebook.h"
#include <unordered_map>
#include <vector>
#include <algorithm> // Required for std::sort()

class CourseGradebook : public Gradebook {
protected:
   // TODO: Type your code here
    // double score;
     //std::string assignment;
    // int id;
    //std::unordered_map<std::string, double> AssignmentScores;
    //std::vector<std::string> UnsortedAssignmentNames;
    //std::vector<int> SortedStudentIDs;
    std::unordered_map<std::string, std::unordered_map<int, double>> scores;

public:
   virtual ~CourseGradebook() {
      // TODO: Type your destructor code here, if needed
   }

   std::unordered_map<int, double> GetAssignmentScores(
      std::string assignmentName) override {

      return scores[assignmentName];
      // TODO: Type your code here (remove placeholder line below)
      //return std::unordered_map<int, double>();
   }

   double GetScore(std::string assignmentName, int studentID) override {
      // TODO: Type your code here (remove placeholder line below)
    //   if (id == studentID && AssignmentScores.find(assignmentName) != AssignmentScores.end()) {
    //     return AssignmentScores.at(assignmentName);
    //   }
    //   return NAN;
    if (scores.count(assignmentName) != 0 && scores.at(assignmentName).count(studentID) != 0) {
        return scores[assignmentName][studentID];
    }
    return NAN;
   }
   
   std::vector<std::string> GetSortedAssignmentNames() override {
      // TODO: Type your code here (remove placeholder line below)
      //std::vector<std::string> assignmentNames = UnsortedAssignmentNames;
      std::vector<std::string> assignmentNames = {};
      for (auto i = scores.begin(); i != scores.end(); i++) {
        const auto& pair = *i; 
        assignmentNames.push_back(pair.first);


      }
      sort(assignmentNames.begin(),assignmentNames.end());

      return assignmentNames;
      //return std::vector<std::string>();
   }
   
   // GetSortedStudentIDs() returns a vector with all distinct student IDs,
   // sorted in ascending order.
   std::vector<int> GetSortedStudentIDs() override {
      // TODO: Type your code here (remove placeholder line below)

      std::vector<int> studentIDs = {};

      for (auto j = scores.begin(); j != scores.end(); j++) {

      const auto& initialMap = *j; 
      const auto& innerMap = initialMap.second; 
      
      for (auto i = innerMap.begin(); i != innerMap.end(); i++) {
        const auto& pair = *i; 
        if (std::find(studentIDs.begin(),studentIDs.end(), pair.first) == studentIDs.end()) {

        studentIDs.push_back(pair.first);

        }

      }
      }
      sort(studentIDs.begin(),studentIDs.end());

      return studentIDs;
      //return std::vector<std::string>();
      //return std::vector<int>();
   }
   
   // GetStudentScores() gets all scores that exist in the gradebook for the
   // student whose ID equals the studentID parameter. Scores are returned as
   // an unordered_map that maps an assignment name to the student's
   // corresponding score for that assignment.
   std::unordered_map<std::string, double> GetStudentScores(
      int studentID) override {
      // TODO: Type your code here (remove placeholder line below)

    std::unordered_map<std::string, double> studentScores;

      for (auto j = scores.begin(); j != scores.end(); j++) { //iterates through the {string, map{int , double}} map

      const auto& initialMap = *j; //map reference iterator
      const auto& innerMap = initialMap.second; //reference to second map of {int, double}
      
      for (auto i = innerMap.begin(); i != innerMap.end(); i++) { //iterates through second map of {int, double}

        const auto& pair = *i; //map reference iterator

        //if (innerMap.find(studentID) != innerMap.end()) { //does this student ID match anything in the map (WRONG LINE WE JUST NEED TO CHECK EACH ELEMENT IN THE MAP ONE AT A TIME NOT CHECKING IF THE MAP CONTAINS THE ID THEN ADD THE FIRST THING IN THE MAP)
        if (pair.first == studentID) { //checks if the element we are iterating over exists in the map reference we are on

      
        //std::cout << initialMap.first << " : " << pair.second << '\n'; Helpful code debugger

        studentScores.insert({initialMap.first, pair.second}); //if so insert assignment string & score double into map

        }

    }

      }
      
      //sort(studentIDs.begin(),studentIDs.end());


      return studentScores;
   }

   void SetScore(std::string assignmentName, int studentID, double score) override {
      // TODO: Type your code here
       scores[assignmentName][studentID] = score;
       //UnsortedAssignmentNames.push_back(assignmentName);
   }
};

#endif