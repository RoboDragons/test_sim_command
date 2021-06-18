#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>



#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

//2021 ssl simulator用
#include "./ssl_simulation_robot_control.pb.h"

using namespace std;
#define PacketLength 1024

int main(){
  int sockfd_Sim; 
  struct sockaddr_in addr_Sim; // Sim address
  unsigned char buffer[PacketLength];
  
  // grSim用設定
  memset(&addr_Sim, 0, sizeof(addr_Sim));
  addr_Sim.sin_family = AF_INET;
  // grSimを立ち上げているPCのIP．自分自身なら127.0.0.1でOK,そうでないならそのPCのIP.
  addr_Sim.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr_Sim.sin_port = htons(10301);
  
  
  // solketを生成

  if ((sockfd_Sim = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    printf("socket error\n");
    return 0;
  }


  RobotControl packet2;

  RobotCommand *command2 =
	      packet2.add_robot_commands();

  // set RobotCommand
  command2->set_id(2);
  command2->set_kick_speed(6.5);
  command2->set_kick_angle(45.0);
  command2->set_dribbler_speed(1200);
  

  MoveLocalVelocity *velcommand =
		  command2->mutable_move_command()->mutable_local_velocity();

  //set MoveLocalVelocity
  velcommand->set_forward(3.0);
  velcommand->set_left(1.0);
  velcommand->set_angular(1.0);
  
  packet2.SerializeToArray(buffer, PacketLength);
  printf("%s",buffer);
  
  sendto(sockfd_Sim,
           buffer,
           PacketLength,
             0,
           (struct sockaddr *)&addr_Sim,
           sizeof(addr_Sim)); 
        
}




