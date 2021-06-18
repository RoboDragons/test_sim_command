#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "./ssl_simulation_robot_control.pb.h"

//2021 ssl simulator用
#include "./ssl_simulation_robot_control.pb.h"

using namespace std;
#define PacketLength 1024


#include <netinet/in.h>
#include <arpa/inet.h>

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
  //addr_Sim.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr_Sim.sin_addr.s_addr = htonl(INADDR_ANY);
  addr_Sim.sin_port = htons(10301);
  

  // solketを生成

  if ((sockfd_Sim = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    printf("socket error\n");
    return 0;
  }
  
  
  if (bind(sockfd_Sim, (struct sockaddr *) &addr_Sim, sizeof(addr_Sim)) == -1) {
    printf("bind error\n");
    return 0;
  }
  

  int recnum;
  
  while(1){
    recnum = recvfrom(sockfd_Sim, buffer, PacketLength, 0, NULL, NULL);
    if(recnum == -1) {
      close(sockfd_Sim); 
      break; 
    }
    printf("received: %s\n", buffer);
  
    RobotControl packet2;
  
    packet2.ParseFromArray(&buffer, PacketLength);
  
    //printf("%s\n",packet2.DebugString());
    cout << packet2.DebugString() << endl;
  }

}






