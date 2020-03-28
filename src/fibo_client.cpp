#include "ros/ros.h"
#include "ros_fibonacci/fibo_service.h"
#include <iostream>
#include <sstream>


using namespace std;

int main(int argc, char **argv){
 ros::init(argc, argv, "service_client");
 ros::NodeHandle n;
 ros::Rate loop_rate(10);
 ros::ServiceClient client= n.serviceClient<ros_fibonacci::fibo_service>("fibonacci");
 
 while(ros::ok()) {
   ros_fibonacci::fibo_service srv;
   
   int ind, leng;
   std::string input ;
   
   std::cout<<"Insert the index:";

// check if the input is valid
  do {
   
    while (true) {
       getline(cin, input);
       stringstream myStream(input);
       if (myStream >> ind)
          break;
       cout << "Invalid number, please try again" << endl;
   }
   if(ind < 0) cout << "The index you entered is negative. Please enter a positive number to continue.\n";
  
  }while(ind<0);



   std::cout<<"Insert the length:";

//check if the input isa valid
    do {
   
    while (true) {
       getline(cin, input);
       stringstream myStream(input);
       if (myStream >> leng)
          break;
       cout << "Invalid number, please try again" << endl;
   }
   if(leng < 0) cout << "The length you entered is negative. Please enter a positive number to continue.\n";
  
  }while(leng<0);

   srv.request.index =ind;
   srv.request.length =leng;
  
   if (client.call(srv)){
      cout<<"From Client: index is ["<< srv.request.index<< "],length of portion is ["<< srv.request.length<< "]"<<endl<<"Server says: the portion required is " <<endl;
   
      for (int j=ind; j<ind+leng; j++) {
      std::cout<<" f["<<j<<"]="<< srv.response.out[j]<<endl;
      }

    }
    else {
        ROS_ERROR ("Failed to call service");
        return 1;
    }
    ros::spinOnce();
    loop_rate.sleep();
   }
   return 0;
}

