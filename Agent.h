#ifndef __AGENT_H__
#define __AGENT_H__

#include "event.h"
#include "HubAPI.h"
#include "configure.h"
#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>

using namespace std;

class Configuration;

class Agent{

	public:
		Agent(){}
		virtual ~Agent(){}
		virtual void Initialize(shared_ptr<Configuration> _confInfo, HubAPI* _hub) = 0;
		virtual void Run() = 0;
		virtual shared_ptr<Event> CreateEvent() = 0;
		virtual void GetNotification(shared_ptr<Event> event) = 0;
		virtual string GetAgentFloor()const = 0;
		virtual string GetAgentConfig()const = 0;
		virtual string GetAgentRoom()const = 0;
 

};



#endif /*__AGENT_H__*/
