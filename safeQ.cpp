#include "safeQ.h"
#include "event.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <pthread.h>

SafeMsgQueue::SafeMsgQueue(){

		pthread_mutex_init(&m_lock, NULL);
		pthread_cond_init(&m_condSend, NULL);
		pthread_cond_init(&m_condRead, NULL);
}

SafeMsgQueue::~SafeMsgQueue(){

		pthread_mutex_destroy(&m_lock);
		pthread_cond_destroy(&m_condSend);
		pthread_cond_destroy(&m_condRead);
}

void SafeMsgQueue::SendEvent(shared_ptr<Event> _event){

	pthread_mutex_lock(&(m_lock));
	
	m_eventQ.push(_event);
	pthread_cond_signal(&(m_condRead));

	pthread_mutex_unlock(&(m_lock));

}

shared_ptr<Event> SafeMsgQueue::ReadEvent(){

	shared_ptr<Event> event;

	pthread_mutex_lock(&(m_lock));
	if(m_eventQ.empty()){
		pthread_cond_wait(&(m_condRead), &(m_lock));
	}
	
	event = m_eventQ.front();
	m_eventQ.pop();
	
	pthread_mutex_unlock(&(m_lock));
	return event;
}




