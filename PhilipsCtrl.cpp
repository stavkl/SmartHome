#include "configure.h"
#include "Agent.h"
#include "event.h"
#include "safeQ.h"

#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <time.h>
#include <ctime> 
#include <unistd.h>

using namespace std;

class PhilipsCtrlEvent: public Event{
	public:
		PhilipsCtrlEvent(){}
		~PhilipsCtrlEvent(){}
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

class PhilipsCtrl: public Agent{


	public:
		PhilipsCtrl();
		~PhilipsCtrl();
		void Initialize(shared_ptr<Configuration> _confInfo, HubAPI* _hub);
		void Run();
		string GetAgentFloor()const 			{return a_floor;}
		string GetAgentConfig()const 			{return a_config;}
		string GetAgentRoom()const 				{return a_room;}
		shared_ptr<Event> CreateEvent();
		void GetNotification(shared_ptr<Event> event);

	private:
		HubAPI*	a_hub;
		bool a_opFlag = false;
		string a_id;
		string a_type;
		string a_room;
		string a_floor;
		string a_log;
		string a_config;
		//SafeMsgQueue<shared_ptr<Event>> m_ctrlQ;
};


PhilipsCtrl:: PhilipsCtrl(){
}

PhilipsCtrl:: ~PhilipsCtrl(){
}

void PhilipsCtrl::Initialize(shared_ptr<Configuration> _confInfo, HubAPI* _hub){
	a_id = _confInfo->GetId();
	a_type = _confInfo->GetOriginalType();
	a_room = _confInfo->GetRoom();
	a_floor = _confInfo->GetFloor();
	a_log = _confInfo->GetLog();
	a_config = _confInfo->GetConfig();
	a_hub = _hub;
}

void PhilipsCtrl::Run(){
	
	shared_ptr<Agent>self(this);
	a_hub->Subscribe(self);
	sleep(2);
	cout << "Controller " << a_id << " - subscribed" << endl;
}



shared_ptr<Event> PhilipsCtrl::CreateEvent(){

	shared_ptr<PhilipsCtrlEvent> phEve(new PhilipsCtrlEvent());

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

void PhilipsCtrl::GetNotification(shared_ptr<Event> event){

	sleep(2);
	cout << "Philips Controller id: " << a_id << " received event: " << 
	event->GetEventOperation() << " " << event->GetEventTime() <<endl;

}


//----------Functions for PhilipsCtrlEvent-------------//

void PhilipsCtrlEvent::SetEventTime(){
	time_t _tm =time(NULL);

	struct tm* curtime = localtime (&_tm);
	e_time = asctime(curtime);
}


bool PhilipsCtrlEvent::SetEventOperation(bool _op){
	if (_op){
		e_operation = "OFF";
		return false;
	}

	e_operation = "ON";
	return true;
}


//-----------Extern Functions for all S.O-------------//

extern "C" shared_ptr<PhilipsCtrl> create(){
	shared_ptr<PhilipsCtrl> philH(new PhilipsCtrl());
	return philH;
}


