#include <iostream>
#include <sstream>
#include <list>

#include <tinyXML/tinyxml.h>
#include "LogTool.h"

using namespace std;
using namespace log4cpp;

//const LogTool* LogTool::m_instance = new LogTool();
LogTool* LogTool::m_pInstance = NULL;
LogTool* pLog = NULL;

void ReadPanelNameConfig(string userID);
void WritePanelNameConfig(string userID, const list<string> requestStr);

void addPanelNameData(TiXmlDocument xmlDoc, const list<string> requestStr, TiXmlElement *pElement);
void addPanelUserData(TiXmlDocument xmlDoc, string userID, const list<string> requestStr, TiXmlElement *pRoot);

int main(int argc, char* argv[])
{
	cout << "Content-type:text/html\r\n\r\n";
	pLog = LogTool::getInstance();// ��־����
	
	// �ͻ��˲�������
	string requestMethod;
	char *pData = NULL;
	requestMethod = getenv("REQUEST_METHOD");
	if (requestMethod == "GET")
	{
		pData = getenv("QUERY_STRING");
	}
	else if (requestMethod == "POST")
	{
		char *tempLen = getenv("CONTENT_LENGTH");
		pData = new char[atoi(tempLen) + 1];
		cin >> pData;
	}
	
	// �������ת��
	string requestParam(pData);
	list<string> strParmList;
	istringstream istr(requestParam);
	int spanIndex = 0;
	string tempStr;

	if (requestParam.length() <= 0)
	{
		cout << "msg=error" << endl;
		return 0;
	}

	do
	{
		spanIndex = requestParam.find_first_of("&");
		if (spanIndex == string::npos)
		{
			tempStr = requestParam.substr(0, requestParam.length());
			requestParam = requestParam.erase(0, requestParam.length());
		}
		else
		{
			tempStr = requestParam.substr(0, spanIndex);
			requestParam = requestParam.erase(0, spanIndex + 1);
		}
		strParmList.push_back(tempStr);

	} while (requestParam.length() > 0 && spanIndex != string::npos);

	strParmList.sort();

	// ������
	string tempHandlerStr = strParmList.front();
	strParmList.pop_front();
	// �û�ID
	string tempUserIdStr = strParmList.front();
	strParmList.pop_front();

	pLog->info(tempHandlerStr + string("  <---->  ") + tempUserIdStr);
	spanIndex = tempHandlerStr.find_first_of("=");
	if (spanIndex != string::npos)
	{
		string handleIdxStr = tempHandlerStr.substr(spanIndex + 1, handleIdxStr.length() - spanIndex - 1);// ������
		int handleIdx = atoi(handleIdxStr.c_str());

		spanIndex = tempUserIdStr.find_first_of("=");
		string userID = tempUserIdStr.substr(spanIndex + 1, tempUserIdStr.length() - spanIndex - 1);// �û�ID

		pLog->info("============ Begin Switching ============");
		switch (handleIdx)
		{
		case 1://���澭���򿪵������
			WritePanelNameConfig(userID, strParmList);
			break;
		case 2://��ȡ�����򿪵������
			ReadPanelNameConfig(userID);
			break;
		default:
			cout << "<!DOCTYPE html>\n"
				"<html>\n"
				"<head>\n"
				"<title>Welcome to CGI testing!</title>\n"
				"<style>\n"
				"body{\n"
				"color:#00ff00;\n"
				"background-color:#000000;\n"
				"}\n"
				"</style>\n"
				"</head>\n"
				"<body>\n"
				"<h1>Welcome to seer cgi test</h1>\n"
				"<p>If you see this page, you have transformed nothing to server.</p>\n"
				"</body>\n"
				"</html>";
			break;
		}
		//cout << string("p0=") + userID << endl;
		cout << "a=b" << endl;
		pLog->info("============  End Switching  ============");
	}

	return 0;
}

void ReadPanelNameConfig(string userID)
{
}

void WritePanelNameConfig(string userID, const list<string> requestStr)
{
	TiXmlDocument configXml("..//SavePanelAndMap.xml");
	configXml.LoadFile();
	TiXmlElement *pSavePanel = configXml.RootElement()->FirstChildElement("SavePanelName");
	if (pSavePanel == NULL)
	{
		pLog->error("SavePanelAndMap.xml ������,��ȱ������Ԫ�أ������Զ����ɣ�����");
		return;
	}

	TiXmlElement *pUser = pSavePanel->FirstChildElement("User");
	while (pUser)
	{
		if (userID == string(pUser->Attribute("userID")))
		{
			break;
		}
		else
		{
			pUser = pUser->NextSiblingElement();
		}
	}

	if (pUser != NULL)
	{
		addPanelNameData(configXml, requestStr, pUser);
	}
	else
	{
		addPanelUserData(configXml, userID, requestStr, pSavePanel);
	}

	configXml.SaveFile();
}

void addPanelNameData(TiXmlDocument xmlDoc, const list<string> requestStr, TiXmlElement *pElement)
{
	list<string>::const_iterator cit = requestStr.begin();
	stringstream ssConvert;
	string id;
	string name;
	int spanIndex = string::npos;

	if (pElement->NoChildren() == false)
	{
		pElement->Clear();
	}

	while (cit != requestStr.end())
	{
		spanIndex = cit->find_first_of("=");
		id = cit->substr(1, spanIndex - 1);
		ssConvert << (atoi(id.c_str()) - 1);
		ssConvert >> id;
		ssConvert.clear();
		name = cit->substr(spanIndex + 1, cit->length() - spanIndex - 1);

		TiXmlElement pannelNode("panel");// ���� panel�ڵ�
		pannelNode.SetAttribute("id", id.c_str());
		pannelNode.SetAttribute("name", name.c_str());
		pannelNode.SetAttribute("comment", "");
		pElement->InsertEndChild(pannelNode);

		pLog->info("addPanelNameData add new panel element:" + name);
		
		cit++;
	}
}

void addPanelUserData(TiXmlDocument xmlDoc, string userID, const list<string> requestStr, TiXmlElement *pRoot)
{
	pLog->info("addPanelUserData -> add new User element");

	TiXmlElement pannelNode("User");// ���� panel�ڵ�
	pannelNode.SetAttribute("userID", userID.c_str());
	addPanelNameData(xmlDoc, requestStr, &pannelNode);
	pRoot->InsertEndChild(pannelNode);
}