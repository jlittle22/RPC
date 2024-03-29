#include <string>
using namespace std;

#ifndef STRUCTWITHARRAY_IDL
#define STRUCTWITHARRAY_IDL
#include "structwitharray.idl"
#endif

#include "rpcproxyhelper.h"

#include "c150debug.h"
#include "c150grading.h"
#include <fstream>

using namespace C150NETWORK;

void setUpDebugLogging(const char *logname, int argc, char *argv[]);

const int serverArg = 1;

int 
main(int argc, char *argv[]) {

     //
     //  Set up debug message logging
     //
     setUpDebugLogging("structwitharrayclientdebugging.txt",argc, argv);

     //
     // Make sure command line looks right
     //
     if (argc != 2) {
       fprintf(stderr,"Correct syntxt is: %s <servername> \n", argv[0]);
       exit(1);
     }

     //
     //  DO THIS FIRST OR YOUR ASSIGNMENT WON'T BE GRADED!
     //
     
     GRADEME(argc, argv);

     //
     //     Call the functions and see if they return
     //
     try {
       //
       // Set up the socket so the proxies can find it
       //
       rpcproxyinitialize(argv[serverArg]);

       ThreePeople test;
       Person jake;
       jake.firstname = "jake";
       jake.lastname = "Little";
       jake.age = 22;
       Person bella;
       bella.firstname = "Isabella";
       bella.lastname = "Urdahl";
       bella.age = 22;
       Person noah;
       noah.firstname = "Noah";
       noah.lastname = "Mendelsohn";
       noah.age = 22;

       test.p1 = jake;
       test.p2 = bella;
       test.p3 = noah;

       Person res = findPerson(test);
       cout << "Got: " << res.firstname << " " << res.lastname << ", Age: " << res.age << endl;

       StructWithArrays t;
       t.aNumber = 5;
       t.people[5] = bella;
       t.people[4] = noah;
       t.people[7] = jake;

       res = findOtherPerson(t);
       cout << "Got: " << res.firstname << " " << res.lastname << ", Age: " << res.age << endl;

       rectangle r;
       r.x = 100;
       r.y = 94588;

       cout << "Got Area: " << area(r) << endl;

       cout << "Calling a void func..." << endl;
       voidFuncThatTakesALot(1, (float)3.14, noah);

       res = nonVoidFuncThatTakesALot(1, (float)3.14, jake);
       cout << "Got: " << res.firstname << " " << res.lastname << ", Age: " << res.age << endl;

       int arr[10][10];
       for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            arr[i][j] = i * j;
        }
       }
       
       for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << "Remote: " << getValueAt(arr, i, j) << ", Local: " << arr[i][j] << endl;
        }
       }
       
       int arr1[1][2][3][4][5][6][7][8];
       arr1[0][1][2][3][2][4][2][3] = 1232423;
       cout << "Tough " << tough(arr1) << endl;


     }

     //
     //  Handle networking errors -- for now, just print message and give up!
     //
     catch (C150Exception& e) {
       // Write to debug log
       c150debug->printf(C150ALWAYSLOG,"Caught C150Exception: %s\n",
			 e.formattedExplanation().c_str());
       // In case we're logging to a file, write to the console too
       cerr << argv[0] << ": caught C150NetworkException: " << e.formattedExplanation() << endl;
     }

     return 0;
}



// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//
//                     setUpDebugLogging
//
//        For COMP 150-IDS, a set of standards utilities
//        are provided for logging timestamped debug messages.
//        You can use them to write your own messages, but 
//        more importantly, the communication libraries provided
//        to you will write into the same logs.
//
//        As shown below, you can use the enableLogging
//        method to choose which classes of messages will show up:
//        You may want to turn on a lot for some debugging, then
//        turn off some when it gets too noisy and your core code is
//        working. You can also make up and use your own flags
//        to create different classes of debug output within your
//        application code
//
//        NEEDSWORK: should be factored into shared code w/pingstreamserver
//        NEEDSWORK: document arguments
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
 
void setUpDebugLogging(const char *logname, int argc, char *argv[]) {

     //   
     //           Choose where debug output should go
     //
     // The default is that debug output goes to cerr.
     //
     // Uncomment the following three lines to direct
     // debug output to a file. Comment them
     // to default to the console.
     //
     // Note: the new DebugStream and ofstream MUST live after we return
     // from setUpDebugLogging, so we have to allocate
     // them dynamically.
     //
     //
     // Explanation: 
     // 
     //     The first line is ordinary C++ to open a file
     //     as an output stream.
     //
     //     The second line wraps that will all the services
     //     of a comp 150-IDS debug stream, and names that filestreamp.
     //
     //     The third line replaces the global variable c150debug
     //     and sets it to point to the new debugstream. Since c150debug
     //     is what all the c150 debug routines use to find the debug stream,
     //     you've now effectively overridden the default.
     //
     ofstream *outstreamp = new ofstream(logname);
     DebugStream *filestreamp = new DebugStream(outstreamp);
     DebugStream::setDefaultLogger(filestreamp);

     //
     //  Put the program name and a timestamp on each line of the debug log.
     //
     c150debug->setPrefix(argv[0]);
     c150debug->enableTimestamp(); 

     //
     // Ask to receive all classes of debug message
     //
     // See c150debug.h for other classes you can enable. To get more than
     // one class, you can or (|) the flags together and pass the combined
     // mask to c150debug -> enableLogging 
     //
     // By the way, the default is to disable all output except for
     // messages written with the C150ALWAYSLOG flag. Those are typically
     // used only for things like fatal errors. So, the default is
     // for the system to run quietly without producing debug output.
     //
     c150debug->enableLogging(C150ALLDEBUG | C150RPCDEBUG | C150APPLICATION | C150NETWORKTRAFFIC | 
			      C150NETWORKDELIVERY); 
}
