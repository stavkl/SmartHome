# SmartHome
SmartHome system in C++.

The system reads a configuration file from which it loads shared objects for sensors and controllers. 
It then uses the Observer design pattern to subscribe each sensor to the notifications it needs to receive. 
Each agent is then run by the system on its own thread and sends messages over a thread-safe message queue, 
from which the system reads and notifies relevant agents.

Further development (in progress):
Include text-to-code module for Smart Home purposes
