#include "configure.h"
#include "Agent.h"
#include "event.h"
#include "safeQ.h"
#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <time.h> 
#include <unistd.h>
#include <pthread.h>

using namespace std;

class PhilipsHueEvent: public Event{
	public:
		PhilipsHueEvent(){}
		~PhilipsHueEvent(){}
		void SetEventFloor(string _floor) {e_floor = _floor;}
		void SetEventRoom(string _room) {e_room = _room;}
		void SetEventTopic(string _topic) {e_topic = _topic;}
		void SetEventTime();
		bool SetEventOperation(bool _op);
		string GetEventFloor()const {return e_floor;}
		string GetEventRoom()const {return e_room;}
		string GetEventTopic()const {return e_topic;}
		string GetEventTime()const {return e_time;}
		string GetEventOperation()const {return e_operation;}

	private:
		string e_topic;
		string e_floor;
		string e_room;
		string e_time;
		string e_operation;
};

class PhilipsHue: public Agent{


	public:
		PhilipsHue();
		~PhilipsHue();
		void Initialize(shared_ptr<Configuration> _confInfo, HubAPI* _hub);
		void Run();
		void GetNotification(shared_ptr<Event> event);
		string GetAgentFloor()const {return a_floor;}
		string GetAgentConfig()const {return a_config;}
		string GetAgentRoom()const {return a_room;}
		string GetID()const {return a_id;}
		HubAPI* GetHub()const {return a_hub;}
		shared_ptr<Event> CreateEvent();

	private:
		HubAPI* a_hub;
		bool a_opFlag = false;
		string a_id;
		string a_type;
		string a_room;
		string a_floor;
		string a_log;
		string a_config;
		static void* RunThread(void* _agent); 

};


PhilipsHue:: PhilipsHue(){
}

PhilipsHue:: ~PhilipsHue(){
}

void PhilipsHue::Initialize(shared_ptr<Configuration> _confInfo, HubAPI* _hub){
	a_id = _confInfo->GetId();
	a_type = _confInfo->GetOriginalType();
	a_room = _confInfo->GetRoom();
	a_floor = _confInfo->GetFloor();
	a_log = _confInfo->GetLog();
	a_config = _confInfo->GetConfig();
	a_hub = _hub;
}

void PhilipsHue::Run(){

	pthread_t* pt = new pthread_t;
	pthread_create(pt, NULL, RunThread, this);
}

void* PhilipsHue::RunThread(void* _agent){

	PhilipsHue* agent = (PhilipsHue*)_agent;

	for(int i = 0; i < 3; ++i){
		sleep(4);
		shared_ptr<Event> event = agent->CreateEvent();
		agent->GetHub()->Publish(event);
		cout << "PhilipsHue id: " << agent->GetID() << " sent: " << event->GetEventOperation() << endl;
	}
	return NULL;
}


shared_ptr<Event> PhilipsHue::CreateEvent(){

	shared_ptr<PhilipsHueEvent> phEve(new PhilipsHueEvent());

	phEve->SetEventRoom(a_room);
	phEve->SetEventFloor(a_floor);
	phEve->SetEventTopic(a_type);
	phEve->SetEventTime();
	if(phEve->SetEventOperation(a_opFlag)){
		a_opFlag = true;
	}
	else{
		a_opFlag = false;		
	}

	return phEve;

}

void PhilipsHue::GetNotification(shared_ptr<Event> event){
}


//----------Functions for PhilipsHueEvent-------------//

void PhilipsHueEvent::SetEventTime(){
	time_t _tm =time(NULL);

	struct tm* curtime = localtime (&_tm);
	e_time = asctime(curtime);
}


bool PhilipsHueEvent::SetEventOperation(bool _op){
	if (_op){
		e_operation = "OFF";
		return false;
	}

	e_operation = "ON";
	return true;
}


//-----------Extern Functions for all S.O-------------//

extern "C" shared_ptr<PhilipsHue> create(){
	shared_ptr<PhilipsHue> philH(new PhilipsHue());
	return philH;
}





