#include <map>
#include <vector>
#include <string>
#include <time.h>
#include "NFComm/NFPluginModule/NFIPluginManager.h"
#include "NFComm/NFCore/NFQueue.h"
#include "NFComm/RapidXML/rapidxml.hpp"
#include "NFComm/RapidXML/rapidxml_iterators.hpp"
#include "NFComm/RapidXML/rapidxml_print.hpp"
#include "NFComm/RapidXML/rapidxml_utils.hpp"
#include "NFComm/NFPluginModule/NFPlatform.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dirent.h"
#include <sys/stat.h>
#include <errno.h>
#ifdef WIN32

#else
#include <unistd.h>
#endif

bool GetPluginNameList(std::string& strPlugin, std::vector<std::string>& pluginList, std::string& configPath)
{
	rapidxml::file<> fdoc(strPlugin.c_str());
	rapidxml::xml_document<>  doc;
	doc.parse<0>(fdoc.data());

	rapidxml::xml_node<>* pRoot = doc.first_node();
	for (rapidxml::xml_node<>* pPluginNode = pRoot->first_node("Plugin"); pPluginNode; pPluginNode = pPluginNode->next_sibling("Plugin"))
	{
		const char* strPluginName = pPluginNode->first_attribute("Name")->value();
		const char* strMain = pPluginNode->first_attribute("Main")->value();
		pluginList.push_back(std::string(strPluginName));
	}

	rapidxml::xml_node<>* pPluginAppNode = pRoot->first_node("APPID");
	if (!pPluginAppNode)
	{
		//NFASSERT(0, "There are no App ID", __FILE__, __FUNCTION__);
		return false;
	}

	const char* strAppID = pPluginAppNode->first_attribute("Name")->value();
	if (!strAppID)
	{
		//NFASSERT(0, "There are no App ID", __FILE__, __FUNCTION__);
		return false;
	}

	rapidxml::xml_node<>* pPluginConfigPathNode = pRoot->first_node("ConfigPath");
	if (!pPluginConfigPathNode)
	{
		//NFASSERT(0, "There are no ConfigPath", __FILE__, __FUNCTION__);
		return false;
	}

	if (NULL == pPluginConfigPathNode->first_attribute("Name"))
	{
		//NFASSERT(0, "There are no ConfigPath.Name", __FILE__, __FUNCTION__);
		return false;
	}

	configPath = pPluginConfigPathNode->first_attribute("Name")->value();

	return true;
}

int CopyFile(std::string& SourceFile, std::string& NewFile)
{
	ifstream in;
	ofstream out;
	in.open(SourceFile.c_str(), ios::binary);//��Դ�ļ�
	if (in.fail())//��Դ�ļ�ʧ��
	{
		cout << "Error 1: Fail to open the source file." << endl;
		in.close();
		out.close();
		return 0;
	}
	out.open(NewFile.c_str(), ios::binary);//����Ŀ���ļ� 
	if (out.fail())//�����ļ�ʧ��
	{
		cout << "Error 2: Fail to create the new file." << endl;
		out.close();
		in.close();
		return 0;
	}
	else//�����ļ�
	{
		out << in.rdbuf();
		out.close();
		in.close();
		return 1;
	}
}

int find_directory(const char *dirname, std::vector<std::string>& fileList)
{
	DIR *dir;
	char buffer[PATH_MAX + 2];
	char *p = buffer;
	const char *src;
	char *end = &buffer[PATH_MAX];
	int result; //���ؽ��

				//copyĿ¼����buffer
	src = dirname;
	while (p < end  &&  *src != '\0') {
		*p++ = *src++;
	}
	*p = '\0';

	//��Ŀ¼
	dir = opendir(dirname);
	if (dir != NULL) {
		struct dirent *ent;

		while ((ent = readdir(dir)) != NULL) {//���ﷵ�ص��ǵ�ǰĿ¼.
			char *q = p;
			char c;

			//���Ŀ¼�����һ���ַ�
			if (buffer < q) {
				c = q[-1];
			}
			else {
				c = ':';
			}

			//�ڵ�ǰ������Ŀ¼�¼���/
			if (c != ':'  &&  c != '/'  &&  c != '\\') {
				*q++ = '/';
			}

			//���ļ��������ں���
			src = ent->d_name; //src Ϊ��Ŀ¼.
			while (q < end  &&  *src != '\0') {
				*q++ = *src++;
			}
			*q = '\0';

			//�����Ƿ����ļ�����Ŀ¼��ѡ�����
			switch (ent->d_type) {
			case DT_LNK:
			case DT_REG:
				//������ļ�
				fileList.push_back(std::string(buffer));
				//RemoveFile(buffer);
				break;

			case DT_DIR:
				//�����Ŀ¼
				if (strcmp(ent->d_name, ".") != 0
					&& strcmp(ent->d_name, "..") != 0) {
					find_directory(buffer, fileList);
				}
				break;

			default:
				/* Ignore device entries */
				/*NOP*/;
			}

		}

		closedir(dir);
		result = 0;

	}
	else {
		//Ŀ¼�򲻿�
		printf("Cannot open directory %s\n", dirname);
		result = -1;
	}

	return result;
}



void printResult(int result, std::string& strName)
{
	if (result == 1)
	{
		printf("Copy file: %s success!\n", strName.c_str());
	}
	else
	{
		printf("Copy file: %s failed!\n", strName.c_str());
	}
}

int main()
{
	std::vector<std::string> fileList;
#ifdef NF_DEBUG_MODE
	find_directory("../../Debug", fileList);
#else
	find_directory("../../Release", fileList);
#endif
	for (auto fileName : fileList)
	{
		if (fileName.find("Plugin.xml") != std::string::npos)
		{
			printf("Reading xml file: %s\n", fileName.c_str());

			std::vector<std::string> pluginList;
			std::string configPath = "";
			GetPluginNameList(fileName, pluginList, configPath);
			if (pluginList.size() > 0 && configPath != "")
			{
				pluginList.push_back("libprotobuf");
				pluginList.push_back("NFMessageDefine");
				pluginList.push_back("NFPluginLoader");

				configPath = "../" + configPath;
				configPath = fileName.substr(0, fileName.find_last_of("/")) + "/" + configPath;

				for (std::string name : pluginList)
				{
					std::string src = configPath + "Comm/Debug/" + name;
					std::string des = fileName.substr(0, fileName.find_last_of("/")) + "/" + name;
					int result = 0;
					if (name == "NFPluginLoader")
					{
						printResult(CopyFile(src + "_d.exe", des + "_d.exe"), src + "_d.exe");
						printResult(CopyFile(src + "_d.pdb", des + "_d.pdb"), src + "_d.pdb");
					}
					else
					{
						printResult(CopyFile(src + "_d.dll", des + "_d.dll"), src + "_d.dll");
						printResult(CopyFile(src + "_d.pdb", des + "_d.pdb"), src + "_d.pdb");
					}
				}
			}
		}
	}

	std::cin.ignore();
	return 0;
}