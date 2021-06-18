Required packages ubuntu
```
sudo apt install g++-7
```

compile
```
protoc --cpp_out=. --proto_path=. ssl_simulation_robot_control.proto

g++-7 ssl_simulation_robot_control.pb.cc test.cpp -o prgrm -lprotobuf -lpthread
```
Run the program
```
./prgrm
```
