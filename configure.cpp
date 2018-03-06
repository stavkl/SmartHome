#include "configure.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <string>
#include <stdio.h>

Configuration:: Configuration(){
}

Configuration:: ~Configuration(){
}


Parser:: Parser(){
}

Parser:: Parser(string _configFilePath){
	if(!m_configFilePath.is_open()){
		m_configFilePath.open(_configFilePath.c_str());
	}
}


Parser:: ~Parser(){
	if(m_configFilePath.is_open()){
		m_configFilePath.close();
	}
}

shared_ptr<Configuration> Parser::ParseNextSection(){

	shared_ptr<Configuration> configInfo(new Configuration());
	string line, id, tmp, type, room, floor, log, config, equal;

	getline(m_configFilePath, line, '[');

	istringstream iss(line);


	if(!(iss >> id >> tmp >> equal >> type >> tmp >> equal >> room >> 
	tmp >> equal >> floor >> tmp >> equal >> log >> tmp >> equal >> config)){
		return NULL;	
	}


	configInfo->SetId(id);
	string combType = "./opt/lib" + type + ".so.1.0";
	configInfo->SetType(combType);
	//cout<<combType<<endl;
	configInfo->SetOriginalType(type);
	//cout<<type<<endl;
	configInfo->SetRoom(room);
	//cout<<room<<endl;
	configInfo->SetFloor(floor);
	//cout<<floor<<endl;
	configInfo->SetLog(log);
	//cout<<log<<endl;
	configInfo->SetConfig(config);
	//cout<<config<<endl;

	return configInfo;		

}
