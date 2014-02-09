duplicates
==========
TO DO:
TreeScanner:
    ==variables==
      -string directory // contains main directory;
      -vector <map <string,string> > // array of pairs of strings : left (file hash) ; right (subdirectory to file) ;
     /* -vector <vector> // array of pointers to vectors of grouped files; */ //only if full scan requested
      
    ==functions==
      -set();
      -get();
      -void DirScan() // scans through the directory pushing every file,hash into array 
      -string fileHashing(string) // uses hashing function from HashGenerator ; input filename ; outputs hash to array;
      -void FullScan() // scans byte by byte through each group of array outputs duplicates
      -void QuickScan() // version when only one array of unique hashes created ; scans only for duplicating hashes and outputs them
      
HashGenerator:
    *no variables*
    ==functions==
      - hashing functions - one for 1/10 file distribution one for unique hash per file;
      
UserInterface:
    number of functions for each functionality and including one just for output and several for different inputs
    
    OPTIONAL: second version for Qt GUI output and input form of the functions 
              third version for HTML output and input
              
Unit tests:
  - one for every functionality and scanning or hashing function
  
DoxyGen documentation for every function or variable
