#include "Hub.h"
#include "HubAPI.h"
#include "safeQ.h"
#include "Agent.h"
#include "event.h"
#include "Loader.h"
#include "configure.h"
#include <string>
#include <memory>
#include <sstream>

Hub::Hub(){
}

Hub::~Hub(){
}

void Hub::Notify(){

	while(!(h_smq.GetQueue().empty())){

		shared_ptr<Event> receivedEvent = h_smq.ReadEvent();

		string eventKey = GenerateEventKey(receivedEvent);
		
		map<string, AgentsByRoom>::iterator it = h_subscribedAgents.find(eventKey);
	
		if(it == h_subscribedAgents.end()){
			return;
		}
		
		shared_ptr<multimap<string, shared_ptr<Agent>>> mmap;
		mmap = it->second;

		multimap<string, shared_ptr<Agent>>::iterator mmit = mmap->begin();
		
		while(((mmit->first).compare(receivedEvent->GetEventRoom()) == 0) ||((mmit->first).compare("0") == 0)){
			(mmit->second)->GetNotification(receivedEvent);
			++mmit;
		}		 
	}
}

string Hub::GenerateEventKey(shared_ptr<Event> event){
	string eventKey = event->GetEventFloor() + event->GetEventTopic();
	return eventKey;
}

void Hub::Publish(shared_ptr<Event> event){
	h_smq.SendEvent(event);
}

void Hub::Subscribe(shared_ptr<Agent> _agent){

	string agRoom, agFloor, agConf, Bigtoken, Bigevent, Bigfrom, token, event, from, tmp, longConf;

	agFloor = _agent->GetAgentFloor();
	agConf = _agent->GetAgentConfig();
	
	istringstream bigConf(agConf);
	while(bigConf){
		getline(bigConf, Bigtoken, ',');
		getline(bigConf, Bigevent, ',');
		getline(bigConf, Bigfrom, ',');
	}

	istringstream bigTokss(Bigtoken);
	while(bigTokss){
		getline(bigTokss, token, ':');
	}

	istringstream bigEvess(Bigevent);
	while(bigEvess){
		getline(bigEvess, event, ':');
	}
	
	istringstream bigFross(Bigfrom);
	while(bigFross){
		getline(bigFross, from, ':');
	}

	if(from.empty()){
		from = "0";
	}
	string eventKey = agFloor + event;

	shared_ptr<multimap<string, shared_ptr<Agent>>> mmap (new multimap<string, shared_ptr<Agent>>);
	mmap->insert(pair<string, shared_ptr<Agent>>(from, _agent));

	h_subscribedAgents.insert(pair<string, shared_ptr<multimap<string, shared_ptr<Agent>>>>(eventKey, mmap));
}

void Hub::HubRun(){

	Parser parser("config.txt");
	while(parser.m_configFilePath){
		shared_ptr<Configuration> configInfo = parser.ParseNextSection();
		if (!configInfo){
			continue;	
		}

		shared_ptr<Agent> agent = h_loader.CreateInitAgent(configInfo, this);
		h_agentsVec.push_back(agent);
	}

	for (size_t i = 0; i< h_agentsVec.size(); ++i){
		h_agentsVec[i]->Run();
	}

	while (1){
		Notify();
	}

}

