#### Preview
As is the case with compiled languages, dependencies might take a while to set up.
Points to remember:
- The initial setup can take a while
- Subsequent builds, if they do not introduce external dependencies, are fast
- The docker build is separated into multi-stage builds. Be careful when purging old images, you might delete the multi-stage cache and trigger a long rebuild!


#### Initial setup
1. Clone this repo
2. Install prerequisites (may require sudo), one-time run ~20 minutes:
    - ```./scripts/sync_depends```

3. Build details:
    - full fresh build: run ```./scripts/full_rebuild```
    - ```mkdir build && cd build```
    - ```cmake ..``` this generates Makefile
    - ```cmake --build .``` or ```make -j <cores>``` cmake generates makefile so these are equivalent, the make one will be faster 
    - if you want to 'install' the artefacts ```cmake --install .``` will create an ```install``` folder in the root of the project with typical structure
    - additionaly you can opt for separates build of user code and framework binaries, setting ```-DUSER_CODE=OFF``` in the cmake configuration call default is ```ON``` for now
    - building user code separetely to simulate being an user of our product: go in ```sandbox``` directory and follow the same cmake flow, this assumes you have a valid ```install``` from where to load ```libkoala.so``` and ```koala.hpp```
    
4. Create the associated docker image:
    - ```cd ..``` (return to the root directory of the project)
    - ```docker build . -t map_reduce:0.0.1``` this will automatically pull the base from docker hub and use that to build the app, this is the fastest way by far, the compressed image is 300MB
5. Handle the base image yourself, this contains all depends
    - ```docker build -t map-reduce-base:0.0.1 -f Dockerfile.base .``` build the base image, not for the faint of heart, takes 40 minutes
    - ```docker pull aairinei/map-reduce-base:<tag>``` if you want to manually pull it 

#### Running locally
1. Make sure you have a successful local build (with all your modifications)
2. In the ```package/``` directory:
    - launch the master: ```./master```
    - launch the worker: ```./worker <address of master>```
        - ```<address of master>``` is of the form ```ip.ip.ip.ip:port```
    - launch the sample code (user code): ```./sample <address of master> <mode> <class>```
        - ```<address of master>``` is of the form ```ip.ip.ip.ip:port```
        - ```<mode>``` is one of ```user, mapper, reducer```
        - ```<class>``` is the name of the mapper/reducer you want to run if starting in mapper/reducer mode

#### Running in docker
1. Make sure you have a successful image build (with all your modifications)
2. Run the image: ```docker run map_reduce:0.0.1``` (this image just sleeps for 3000 seconds)
3. Open another terminal (or terminals) to launch the master, worker, or sample code:
    - ```docker ps -a``` (get the id of the running container)
    - ```docker exec -it <id_container> bash``` (opens a terminal inside the container - it should already be located in nfs/)
    - Use the same commands as above to launch the master, worker or sample code

#### Running in docker-compose
0. One-time only: ```mkdir nfs``` in the root of the project (this will be the shared volume between the containers)
1. Make sure you have a successful image build (with all your modifications)
2. ```docker compose up``` - this will bring up the master and worker nodes (by default 5)
3. Enter the user container: ```docker exec -it <user_container_id> bash``` and launch the sample code, for example ```./sample 172.7.0.10:50051 user -```. You can add more user containers by configuring ```replicas``` to be >1 (similar to the workers)
4. If you force kill docker compose (double CTRL+C), run ```docker compose down``` (I recommend force killing, it takes more to wait for containers to end gracefully)

#### How to build your changes?
- If you just modified the source code: ```cd build && cmake --build .```
- If you modified the source code and cmake configuration: ```cd build && cmake .. && cmake --build .```
- If you modified the definition of the protobufs (they need to be regenerated): make sure to add the files into the ./proto/CMakeLista.txt
- If you want to recreate the docker image: ```docker build . -t map_reduce:<version>```