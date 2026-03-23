#ifndef NATURALMERGESORTER_H
#define NATURALMERGESORTER_H

class NaturalMergeSorter {
public:
   virtual int GetSortedRunLength(int* array, int arrayLength, int startIndex) {
      // TODO: Type your code here
      int runLength = 0;
    
      if (startIndex < arrayLength) {
        runLength = 1;
      }
      else {runLength = 0;}
      
      
      for (int i = startIndex; i < arrayLength-1; i++) {
        if (array[i] <= array[i+1]) {
            runLength++;
            //std::cout << runLength;
        }
        else {break;}
      }
      return runLength;
   }
   
   virtual void NaturalMergeSort(int* array, int arrayLength) {
      // TODO: Type your code here
// Start at index i=0
// Get the length of the first sorted run, starting at i
// Return if the first run's length equals the array length
// If the first run ends at the array's end, reassign i=0 and repeat step 2
// Get the length of the second sorted run, starting immediately after the first
// Merge the two runs with the provided Merge() function
// Reassign i with the first index after the second run, or 0 if the second run ends at the array's end
// Go to step 2

       for (int i = 0; i < arrayLength;) {
         int run1 = GetSortedRunLength(array,arrayLength,i);
         if (i == 0 && run1 == arrayLength) {
             return; //all elements are sorted
         }
         else {
            int startindex = i; //position of first sorted array's starting index
            int endindex = startindex + run1 - 1; //position of first sorted array's ending index
            int startindex2 = endindex + 1;


            if (startindex2 >= arrayLength) {
               i = 0;
               continue;
            }
            int run2 = GetSortedRunLength(array,arrayLength,startindex2); //second run length is the ending index of first run +1
            int endindex2 = startindex2 + run2 -1;
            Merge(array, startindex, endindex, endindex2); //merge 1st and 2nd runs
            i = endindex2 + 1;
         }
         if (i >= arrayLength) { //can be ==
            i = 0;

         }

      }
   }
   
   virtual void Merge(int* numbers, int leftFirst, int leftLast,
      int rightLast) {
      int mergedSize = rightLast - leftFirst + 1;
      int* mergedNumbers = new int[mergedSize];
      int mergePos = 0;
      int leftPos = leftFirst;
      int rightPos = leftLast + 1;
         
      // Add smallest element from left or right partition to merged numbers
      while (leftPos <= leftLast && rightPos <= rightLast) {
         if (numbers[leftPos] <= numbers[rightPos]) {
            mergedNumbers[mergePos] = numbers[leftPos];
            leftPos++;
         }
         else {
            mergedNumbers[mergePos] = numbers[rightPos];
            rightPos++;
         }
         mergePos++;
      }
         
      // If left partition isn't empty, add remaining elements to mergedNumbers
      while (leftPos <= leftLast) {
         mergedNumbers[mergePos] = numbers[leftPos];
         leftPos++;
         mergePos++;
      }
      
      // If right partition isn't empty, add remaining elements to mergedNumbers
      while (rightPos <= rightLast) {
         mergedNumbers[mergePos] = numbers[rightPos];
         rightPos++;
         mergePos++;
      }
      
      // Copy merged numbers back to numbers
      for (mergePos = 0; mergePos < mergedSize; mergePos++) {
         numbers[leftFirst + mergePos] = mergedNumbers[mergePos];
      }
      
      // Free temporary array
      delete[] mergedNumbers;
   }
};

#endif