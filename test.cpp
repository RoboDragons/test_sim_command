#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//2021 ssl simulator用
#include "./ssl_simulation_robot_control.pb.h"

using namespace std;
#define PacketLength 1024

int main(){

  int sockfd_Sim; 
  
  struct sockaddr_in addr_Sim; // Sim address
  struct hostent *ptrh;
  string host;
  int port;
  
  // grSim用設定
  memset((char *)&addr_Sim, 0, sizeof(addr_Sim));
  addr_Sim.sin_family = AF_INET;
  // grSimを立ち上げているPCのIP．自分自身なら127.0.0.1でOK,そうでないならそのPCのIP.
  host = "127.0.0.1";
  //port = 10300;   // controller
  port = 10301;   // blue
  //port = 10302;   // yellow
  //addr_Sim.sin_port = htons(10301);
  addr_Sim.sin_addr.s_addr = inet_addr(host.c_str());
  addr_Sim.sin_port = htons((u_short) port);
  ptrh = gethostbyname(host.c_str());
  if ( ((char *)ptrh) == NULL ) {
    fprintf(stderr, "invalid host: %s\n", host.c_str());
    exit(1);
  }
  memcpy(&addr_Sim.sin_addr, ptrh->h_addr, ptrh->h_length);
  
  
  // solketを生成

  if ((sockfd_Sim = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    printf("socket error\n");
    return 0;
  }


  RobotControl packet2;
  //SSLSIMRobotControl packet2{new SSLSIM::RobotControl};

  RobotCommand* command2 =
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

  char buffer[packet2.ByteSize()];
  packet2.SerializeToArray(buffer, packet2.ByteSize());
  // sample 1:
  sendto(sockfd_Sim, buffer, packet2.ByteSize(), 0, (struct sockaddr *)&addr_Sim, sizeof(addr_Sim));
  // sample 2:
  //sendto(sockfd_Sim, buffer, sizeof(buffer), 0, (struct sockaddr *)&addr_Sim, sizeof(addr_Sim));

  return 0;
}




