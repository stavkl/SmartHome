#ifndef __CONFIGURE_H__
#define __CONFIGURE_H__

#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <memory>

using namespace std;

class Configuration{
	public:
		~Configuration();
		Configuration();

		string GetId()const {return m_id;}
		string GetType()const {return m_type;}
		string GetOriginalType()const {return m_originalType;}
		string GetRoom()const {return m_room;}
		string GetFloor()const {return m_floor;}
		string GetLog()const {return m_log;}
		string GetConfig()const {return m_config;}

		void SetId(string _id) {m_id = _id.substr(0,_id.length()-1);}
		void SetType(string _type) {m_type = _type;}
		void SetOriginalType(string _type) {m_originalType = _type;}
		void SetRoom(string _room) {m_room = _room;}
		void SetFloor(string _floor){m_floor = _floor;}
		void SetLog(string _log) {m_log = _log;}
		void SetConfig(string _config) {m_config = _config;}

	private:
		string m_id;
		string m_type;
		string m_originalType;
		string m_room;
		string m_floor;
		string m_log;
		string m_config;
		
		Configuration(const Configuration& _conf);
		Configuration& operator=(const Configuration& _conf);
		
};

class Parser{

	public:
		~Parser();
		Parser();
		Parser(string _configFilePath);
		shared_ptr<Configuration> ParseNextSection();
		ifstream m_configFilePath;

	private:
		
		Parser(const Parser& _parser);
		Parser& operator=(const Parser& _parser);
	
};


#endif /*__CONFIGURE_H__*/



