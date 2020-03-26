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
   std::cout<<"Insert the index:";
   std::cin>>ind;
   std::cout<<endl;


   std::cout<<"Insert the length:";
   std::cin>>leng;
   std::cout<<endl;

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

