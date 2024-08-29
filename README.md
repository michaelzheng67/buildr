```
 ▄▄▄▄▄▄▄▄▄▄   ▄         ▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄            ▄▄▄▄▄▄▄▄▄▄   ▄▄▄▄▄▄▄▄▄▄▄ 
▐░░░░░░░░░░▌ ▐░▌       ▐░▌▐░░░░░░░░░░░▌▐░▌          ▐░░░░░░░░░░▌ ▐░░░░░░░░░░░▌
▐░█▀▀▀▀▀▀▀█░▌▐░▌       ▐░▌ ▀▀▀▀█░█▀▀▀▀ ▐░▌          ▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀█░▌
▐░▌       ▐░▌▐░▌       ▐░▌     ▐░▌     ▐░▌          ▐░▌       ▐░▌▐░▌       ▐░▌
▐░█▄▄▄▄▄▄▄█░▌▐░▌       ▐░▌     ▐░▌     ▐░▌          ▐░▌       ▐░▌▐░█▄▄▄▄▄▄▄█░▌
▐░░░░░░░░░░▌ ▐░▌       ▐░▌     ▐░▌     ▐░▌          ▐░▌       ▐░▌▐░░░░░░░░░░░▌
▐░█▀▀▀▀▀▀▀█░▌▐░▌       ▐░▌     ▐░▌     ▐░▌          ▐░▌       ▐░▌▐░█▀▀▀▀█░█▀▀ 
▐░▌       ▐░▌▐░▌       ▐░▌     ▐░▌     ▐░▌          ▐░▌       ▐░▌▐░▌     ▐░▌  
▐░█▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄█░▌ ▄▄▄▄█░█▄▄▄▄ ▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄█░▌▐░▌      ▐░▌ 
▐░░░░░░░░░░▌ ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░▌ ▐░▌       ▐░▌
 ▀▀▀▀▀▀▀▀▀▀   ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀   ▀         ▀ 
```                                                                             

# cli-based linux resource management tool

With Buildr, you can administrate resources for linux through your cli.

### Features

  - Define "users" and assign resources / processes to them
  - Monitoring interface to see overall usage and resource consumption across users
  - Persistence by savung state to disk
  - Docker container support

### How does it work?

Each "user" object maps 1-to-1 with a long running process. That process is then placed in 
corresponding cgroups as well as its own namespace to limit resource usage and isolation.
When tasks are assigned to a given user object, we place that task's process into the same
cgroups and namesapce as the long running process associated with the user object.

Buildr must first be started up by running its executable. This will start up the application
by mounting cgroups and creating namespaces based on admin configurations and saved user
states.

The Buildr application has it's own daemon thread which act as the "server-side" in order to
communicate information with all user processes. Each user object has its own process, which 
the daemon communicates using unix domain sockets in order to run commands.

Each user process is placed in corresponding cgroups and namespaces in order to limit resource
usage and have an isolated view of the machine. Only the daemon thread is able to have complete
view of what each user process is doing.

### Setting up build

- navigate to /build
- run 'cmake ..' to create build cache
- run 'cmake --build .' whenever you need to compile
- cd into /bin and run binary
