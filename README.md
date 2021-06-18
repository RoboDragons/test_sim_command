Required packages ubuntu
```
sudo apt install g++7 libprotobuf-dev libprotoc-dev protobuf-compiler
```

compile
```
protoc --cpp_out=. --proto_path=. ssl_simulation_robot_control.proto

g++-7 ssl_simulation_robot_control.pb.cc test.cpp -o prgrm -lprotobuf -lpthread

g++-7 ssl_simulation_robot_control.pb.cc test_receive.cpp -o prgrm2 -lprotobuf -lpthread
```
Run the program
```
./prgrm
```
