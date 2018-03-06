#ifndef __HUB_H__
#define __HUB_H__

#include "HubAPI.h"
#include "event.h"
#include "Loader.h"
#include "safeQ.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <time.h> 
#include <unistd.h>
#include <pthread.h>
using namespace std;

typedef shared_ptr<multimap<string, shared_ptr<Agent>>> AgentsByRoom;

class Agent;
class Configuration;
class Parser;

class Hub: public HubAPI{

	public:
		Hub();
		~Hub();
		void Notify();
		void Publish(shared_ptr<Event> event);
		void Subscribe(shared_ptr<Agent> _agent);
		void HubRun();
		const SafeMsgQueue& GetQueue() {return h_smq;}
		string GenerateEventKey(shared_ptr<Event> event);
	
	private:

		vector<shared_ptr<Agent>> h_agentsVec;
		map <string, AgentsByRoom> h_subscribedAgents;

		Loader h_loader;
		SafeMsgQueue h_smq;
};



#endif /*__HUB_H__*/
