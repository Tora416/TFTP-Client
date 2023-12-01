#define _WINSOCK_DEPRECATED_NO_WARNINGS 1//vs使用winsock关闭警报
#define log_location "E:\\{111学校\\大二上\\计网\\Exp1\\log.txt"//日志文件log.txt存放位置
#define code_location_qt "file:///E:/111test" //Client文件存放位置,服务器可与这个文件夹的文件互传,下一行同
#define code_location "E:\\111test\\"



#include <iostream>
#include <stdio.h>
#include <WinSock2.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
#include "QtWidgetsApplication1.h"

int makeUDPsocket()
{
	WSADATA socdata;
	int Drev = WSAStartup(0x0202, &socdata);
	if (Drev) return -1;
	int udpsocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (udpsocket == INVALID_SOCKET) return -2;
	return udpsocket;
}

sockaddr_in makeAddress(const char* ip, int port)
{
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = inet_addr(ip);
	return addr;
}

char* makeRRQorWRQPack(int mode, char* filename, int& length, int type)
{
	int len_filename = strlen(filename);
	char* message = (char*)malloc(len_filename + 2 + 1 + type + 1);
	message[0] = 0;
	if (mode == 1) message[1] = 1;
	else if (mode == 2) message[1] = 2;
	strcpy(&message[2], filename);
	message[2 + len_filename] = '\0';
	if (type == 5) strcpy(&message[3 + len_filename], "octet");
	else if (type == 8) strcpy(&message[3 + len_filename], "netascii");
	message[2 + len_filename + 1 + type] = '\0';
	length = len_filename + 4 + type;
	return message;
}

char* makeACKPack(short blockno)
{
	char* message = (char*)malloc(4);
	message[0] = 0;
	message[1] = 4;
	blockno = htons(blockno);
	memcpy(message + 2, &blockno, 2);
	return message;
}

char* makeDATAPack(short blockno, FILE* f, int& length)
{
	char temp[512];
	int len = fread(temp, 1, 512, f);
	if (!ferror(f))
	{
		char* message = (char*)malloc(len + 4);
		message[0] = 0;
		message[1] = 3;
		blockno = htons(blockno);
		memcpy(message + 2, &blockno, 2);
		memcpy(message + 4, temp, len);
		length = len + 4;
		return message;
	}
	else return NULL;
}

void print_now_time(FILE* f)
{
	time_t timenow;
	time(&timenow);
	char* timestr = asctime(localtime(&timenow));
	int len = strlen(timestr);
	*(timestr - 1 + len) = '\0';
	fprintf(f, "%s        ", timestr);
	return;
}


QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
    QButtonGroup* block1 = new QButtonGroup(this);
    QButtonGroup* block2 = new QButtonGroup(this);
    block1->addButton(ui.radioButton1, 1);
    block1->addButton(ui.radioButton2, 2);
    block2->addButton(ui.radioButton3, 1);
    block2->addButton(ui.radioButton4, 2);
    connect(ui.pushButton,&QPushButton::clicked,this,&QtWidgetsApplication1::on_PushButton_clicked);
	connect(ui.pushButton_2, &QPushButton::clicked, this, &QtWidgetsApplication1::on_PushButton_2_clicked);
}

QtWidgetsApplication1::~QtWidgetsApplication1()
{}

void QtWidgetsApplication1::on_PushButton_2_clicked()
{
	QDesktopServices::openUrl(QUrl(code_location_qt, QUrl::TolerantMode));
}

void QtWidgetsApplication1::on_PushButton_clicked()
{
    QString Sever = ui.IPlineEdit->text();
    QString File = ui.FilelineEdit->text();
	QByteArray Sever1 = Sever.toLatin1();
	QByteArray File1 = File.toLatin1();
    QString result;
    int mode1 = -1;
    int mode2 = -1;
    if (ui.radioButton1->isChecked()) mode1 = 1;
    else if(ui.radioButton2->isChecked())mode1 = 2;
    if (ui.radioButton3->isChecked()) mode2 = 1;
    else if (ui.radioButton4->isChecked()) mode2 = 2;
	FILE* logf = fopen(log_location, "a");
	char* sendtempspace = (char*)malloc(2000);
	sockaddr_in addr;
	SOCKET sock = makeUDPsocket();
	clock_t starttans, endtrans;
	char* Severadd = Sever1.data();
	int recvovertime = 1000;//设置超时时间 1s
	int sendovertime = 1000;
	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&recvovertime, sizeof(recvovertime));
	setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&sendovertime, sizeof(sendovertime));
	if (mode1 == 1)
	{
		addr = makeAddress(Severadd, 69);
		char* filename = File1.data();
		int type = mode2;
		if (type == 1) type = 8;
		else type = 5;
		//第一轮 RRQ
		int datalen = 0;
		char* sendp = makeRRQorWRQPack(mode1, filename, datalen, type);
		memcpy(sendtempspace, sendp, datalen);//进缓冲区以备重传
		int backcode = sendto(sock, sendtempspace, datalen, 0, (sockaddr*)&addr, sizeof(addr));
		starttans = clock();//开始计时
		int sendtonum = 1;//单轮发送次数
		while (backcode != datalen)
		{
			if (backcode == SOCKET_ERROR)
			{
				int errorcode = WSAGetLastError();
				result.sprintf("[ERROR]sendRRQerror    errorcode:%d\n", errorcode);
				ui.textBrowser->insertPlainText(result);
				ui.textBrowser->moveCursor(QTextCursor::End);
				QApplication::processEvents();
				print_now_time(logf);
				fprintf(logf, "[ERROR]sendRRQerror    errorcode:%d\n", errorcode);
				break;
			}
			if (sendtonum <= 5) //尝试5次，发不出去认为失败
			{
				backcode = sendto(sock, sendtempspace, datalen, 0, (sockaddr*)&addr, sizeof(addr));
				sendtonum++;
			}
			else
			{
				print_now_time(logf);
				fprintf(logf, "[ERROR]sendRRQerror    try too many times\n");
				result.sprintf("[ERROR]sendRRQerror    try too many times\n");
				ui.textBrowser->insertPlainText(result);
				ui.textBrowser->moveCursor(QTextCursor::End);
				QApplication::processEvents();
				break;
			}
		}//发送失败
		print_now_time(logf);
		fprintf(logf, "Downloading file : %s\n", filename);
		result.sprintf("Downloading file : %s\n", filename);
		ui.textBrowser->insertPlainText(result);
		ui.textBrowser->moveCursor(QTextCursor::End);
		QApplication::processEvents();
		QApplication::processEvents();
		//开始循环收发包
		char* urlfile = (char*)malloc(1000);
		strcpy(urlfile,code_location);
		strcat(urlfile,filename);
		FILE* targetf = fopen(urlfile, "wb");//创建下载文件
		if (targetf == NULL)
		{
			print_now_time(logf);
			fprintf(logf, "[ERROR]fail to create the file\n");
			result.sprintf("[ERROR]fail to create the file\n");
			ui.textBrowser->insertPlainText(result);
			ui.textBrowser->moveCursor(QTextCursor::End);
			QApplication::processEvents();
		}
		int totallen_file = 0;//统计文件长计算速度
		int resent = 0;//记录重传次数
		short blocknum = 0; //block number
		int nowlen = 0;//记录当前包内数据长
		while (1)
		{
			char* gettempspace = (char*)malloc(1024);
			memset(gettempspace, 0, 1024);
			sockaddr_in server;//端口获取
			int lengetaddr = sizeof(server);
			int recvcode = recvfrom(sock, gettempspace, 1024, 0, (sockaddr*)&server, &lengetaddr);
			if (recvcode == -1)//无回应
			{
				int backcode = sendto(sock, sendtempspace, datalen, 0, (sockaddr*)&addr, sizeof(addr));
				if (resent > 10)
				{
					print_now_time(logf);
					fprintf(logf, "[ERROR]Download failed! resent ACK too many times\n");
					result.sprintf("[ERROR]Download failed! resent ACK too many times\n");
					ui.textBrowser->insertPlainText(result);
					ui.textBrowser->moveCursor(QTextCursor::End);
					QApplication::processEvents();
					break;
				}
				resent++;
				print_now_time(logf);
				fprintf(logf, "resent ACK%hd (ACK0 means RRQ)", blocknum);
				result.sprintf("resent ACK%hd (ACK0 means RRQ)", blocknum);
				ui.textBrowser->insertPlainText(result);
				ui.textBrowser->moveCursor(QTextCursor::End);
				QApplication::processEvents();
				QApplication::processEvents();
				sendtonum = 1;
				while (backcode != datalen)
				{
					if (sendtonum <= 5) //尝试5次，发不出去认为失败
					{
						backcode = sendto(sock, sendtempspace, datalen, 0, (sockaddr*)&addr, sizeof(addr));
						sendtonum++;
					}
					else
					{
						print_now_time(logf);
						fprintf(logf, "[ERROR]resent error\n");
						result.sprintf("[ERROR]resent error\n");
						ui.textBrowser->insertPlainText(result);
						ui.textBrowser->moveCursor(QTextCursor::End);
						QApplication::processEvents();
						break;
					}
				}
				fprintf(logf, "			[SUCCESS]\n");
				result.sprintf("			[SUCCESS]\n");
				ui.textBrowser->insertPlainText(result);
				ui.textBrowser->moveCursor(QTextCursor::End);
				QApplication::processEvents();
				Sleep(1000);
				continue;
			}
			else if (recvcode > 0)//有回应
			{
				if (gettempspace[1] == 3)
				{
					short nowblocknumber = -1;
					memcpy(&nowblocknumber, gettempspace + 2, 2);
					nowblocknumber = ntohs(nowblocknumber);
					nowlen = recvcode - 4;
					totallen_file += nowlen;
					fwrite(gettempspace + 4, 1, nowlen, targetf);
					if (nowblocknumber == blocknum + 1)
					{
						if (blocknum)
						{
							fprintf(logf, "			[SUCCESS]\n");
							result.sprintf("			[SUCCESS]\n");
							ui.textBrowser->insertPlainText(result);
							ui.textBrowser->moveCursor(QTextCursor::End);
							QApplication::processEvents();
						}
						addr = server;
						blocknum++;
						sendp = makeACKPack(blocknum);
						datalen = 4;
						memcpy(sendtempspace, sendp, datalen);
						totallen_file += nowlen;
						resent = 0;
						if (sendp == NULL)
						{
							print_now_time(logf);
							fprintf(logf, "[ERROR]makeACKPack error\n");
							result.sprintf("[ERROR]makeACKPack error\n");
							ui.textBrowser->insertPlainText(result);
							ui.textBrowser->moveCursor(QTextCursor::End);
							QApplication::processEvents();
							break;
						}
						int backcode = sendto(sock, sendtempspace, datalen, 0, (sockaddr*)&addr, sizeof(addr));
						sendtonum = 1;
						while (backcode != datalen)
						{
							if (sendtonum <= 5) //尝试5次，发不出去认为失败
							{
								backcode = sendto(sock, sendtempspace, datalen, 0, (sockaddr*)&addr, sizeof(addr));
								sendtonum++;
							}
							else
							{
								print_now_time(logf);
								fprintf(logf, "[ERROR]sent error,  ACK number :%hd\n", blocknum);
								result.sprintf("[ERROR]sent error,  ACK number :%hd\n", blocknum);
								ui.textBrowser->insertPlainText(result);
								ui.textBrowser->moveCursor(QTextCursor::End);
								QApplication::processEvents();
								break;
							}
						}
						print_now_time(logf);
						fprintf(logf, "Downloading block % hd ......", blocknum);
						result.sprintf("Downloading block%hd ......", blocknum);
						ui.textBrowser->insertPlainText(result);
						ui.textBrowser->moveCursor(QTextCursor::End);
						QApplication::processEvents();
						if (nowlen < 512 && blocknum != 0)//传完了
						{
							fprintf(logf, "			[SUCCESS]\n");
							result.sprintf("			[SUCCESS]\n");
							ui.textBrowser->insertPlainText(result);
							ui.textBrowser->moveCursor(QTextCursor::End);
							QApplication::processEvents();
							endtrans = clock();
							double time_use = ((endtrans - starttans) / 1.0) / (CLOCKS_PER_SEC);//结束计时，精度1ms
							print_now_time(logf);
							fprintf(logf, "Download Finished!!!\nAverage transmission rate : %.2lf kb/s\n", (totallen_file / time_use) / 1024);
							result.sprintf("Download Finished!!!\nAverage transmission rate : %.2lf kb/s\n", (totallen_file / time_use) / 1024);
							ui.textBrowser->insertPlainText(result);
							ui.textBrowser->moveCursor(QTextCursor::End);
							QApplication::processEvents();
							break;
						}
					}
					else
					{
						datalen = 4;
						int backcode = sendto(sock, sendtempspace, datalen, 0, (sockaddr*)&addr, sizeof(addr));
						sendtonum = 1;
						while (backcode != datalen)
						{
							if (sendtonum <= 5) //尝试5次，发不出去认为失败
							{
								backcode = sendto(sock, sendtempspace, datalen, 0, (sockaddr*)&addr, sizeof(addr));
								sendtonum++;
							}
							else
							{
								print_now_time(logf);
								fprintf(logf, "[ERROR]sent error,  ACK number :%hd\n", blocknum);
								result.sprintf("[ERROR]sent error,  ACK number :%hd\n", blocknum);
								ui.textBrowser->insertPlainText(result);
								ui.textBrowser->moveCursor(QTextCursor::End);
								QApplication::processEvents();
								break;
							}
						}
					}
				}
				else if (gettempspace[1] == 5)
				{
					short errorcode = -1;
					memcpy(&errorcode, gettempspace + 2, 2);
					errorcode = ntohs(errorcode);
					char* errormessage = (char*)malloc(1024);
					strcpy(errormessage, gettempspace + 4);
					if (errorcode >= 0 && errorcode <= 7)
					{
						print_now_time(logf);
						fprintf(logf, "[ERROR]getERRORPack : %s\n", errormessage);
						result.sprintf("[ERROR]getERRORPack : %s\n", errormessage);
						ui.textBrowser->insertPlainText(result);
						ui.textBrowser->moveCursor(QTextCursor::End);
						QApplication::processEvents();
					}
					else
					{
						print_now_time(logf);
						fprintf(logf, "[ERROR]getERRORPack : wrong error pack\n");
						result.sprintf("[ERROR]getERRORPack : wrong error pack\n");
						ui.textBrowser->insertPlainText(result);
						ui.textBrowser->moveCursor(QTextCursor::End);
						QApplication::processEvents();
					}
					break;
				}
				else
				{
					result.sprintf("[ERROR]get wrong PACK\n");
					ui.textBrowser->insertPlainText(result);
					ui.textBrowser->moveCursor(QTextCursor::End);
					QApplication::processEvents();
					print_now_time(logf);
					fprintf(logf, "[ERROR]get wrong PACK\n");
					break;
				}
			}
		}
		fclose(targetf);
	}
	else if (mode1 == 2)
	{
		addr = makeAddress(Severadd, 69);
		char* filename = File1.data();
		int type = mode2;
		if (type == 1) type = 8;
		else type = 5;
		//第一轮 WRQ
		int datalen = 0;
		char* sendp = makeRRQorWRQPack(mode1, filename, datalen, type);
		memcpy(sendtempspace, sendp, datalen);//进缓冲区以备重传
		int backcode = sendto(sock, sendtempspace, datalen, 0, (sockaddr*)&addr, sizeof(addr));
		starttans = clock();//开始计时
		int sendtonum = 1;//单轮发送次数
		int errorswitch = 0;//跳出辅助
		while (backcode != datalen)
		{
			if (backcode == SOCKET_ERROR)
			{
				int errorcode = WSAGetLastError();
				result.sprintf("[ERROR]sendWRQerror    errorcode:%d\n", errorcode);
				ui.textBrowser->insertPlainText(result);
				ui.textBrowser->moveCursor(QTextCursor::End);
				QApplication::processEvents();
				print_now_time(logf);
				fprintf(logf, "[ERROR]sendWRQerror    errorcode:%d\n", errorcode);
				errorswitch = 1;
				break;
			}
			if (sendtonum <= 5) //尝试5次，发不出去认为失败
			{
				backcode = sendto(sock, sendtempspace, datalen, 0, (sockaddr*)&addr, sizeof(addr));
				sendtonum++;
			}
			else
			{
				print_now_time(logf);
				fprintf(logf, "[ERROR]sendWRQerror    try too many times\n");
				result.sprintf("[ERROR]sendWRQerror    try too many times\n");
				ui.textBrowser->insertPlainText(result);
				ui.textBrowser->moveCursor(QTextCursor::End);
				QApplication::processEvents();
				errorswitch = 1;
				break;
			}
		}//发送失败
		print_now_time(logf);
		fprintf(logf, "Uploading file : %s\n", filename);
		result.sprintf("Uploading file : %s\n", filename);
		ui.textBrowser->insertPlainText(result);
		ui.textBrowser->moveCursor(QTextCursor::End);
		QApplication::processEvents();
		//开始循环收发包
		char* urlfile = (char*)malloc(1000);
		strcpy(urlfile, code_location);
		strcat(urlfile, filename);
		FILE* targetf = fopen(urlfile, "rb");//打开传输文件
		if (targetf == NULL)
		{
			print_now_time(logf);
			fprintf(logf, "[ERROR]fail to open the file\n");
			result.sprintf("[ERROR]fail to open the file\n");
			ui.textBrowser->insertPlainText(result);
			ui.textBrowser->moveCursor(QTextCursor::End);
			QApplication::processEvents();
		}
		int totallen_file = 0;//统计文件长计算速度
		int resent = 0;//记录重传次数
		short blocknum = 0; //block number
		while (1)
		{
			char* gettempspace = (char*)malloc(1024);
			sockaddr_in server;//端口获取
			int lengetaddr = sizeof(server);
			int recvcode = recvfrom(sock, gettempspace, 1024, 0, (sockaddr*)&server, &lengetaddr);
			if (recvcode == -1)//无回应
			{
				if (resent > 10)
				{
					print_now_time(logf);
					fprintf(logf, "[ERROR]Upload failed! resent too many times\n");
					result.sprintf("[ERROR]Upload failed! resent too many times\n");
					ui.textBrowser->insertPlainText(result);
					ui.textBrowser->moveCursor(QTextCursor::End);
					QApplication::processEvents();
					errorswitch = 1;
					break;
				}
				int backcode = sendto(sock, sendtempspace, datalen, 0, (sockaddr*)&addr, sizeof(addr));
				backcode = sendto(sock, sendtempspace, datalen, 0, (sockaddr*)&addr, sizeof(addr));
				resent++;
				print_now_time(logf);
				fprintf(logf, "resent block%hd", blocknum);
				result.sprintf("resent block%hd", blocknum);
				ui.textBrowser->insertPlainText(result);
				ui.textBrowser->moveCursor(QTextCursor::End);
				QApplication::processEvents();
				sendtonum = 1;
				while (backcode != datalen)
				{
					if (sendtonum <= 5) //尝试5次，发不出去认为失败
					{
						backcode = sendto(sock, sendtempspace, datalen, 0, (sockaddr*)&addr, sizeof(addr));
						sendtonum++;
					}
					else
					{
						print_now_time(logf);
						fprintf(logf, "[ERROR]resent error\n");
						result.sprintf("[ERROR]resent errot\n");
						ui.textBrowser->insertPlainText(result);
						ui.textBrowser->moveCursor(QTextCursor::End);
						QApplication::processEvents();
						errorswitch = 1;
						break;
					}
				}
				fprintf(logf, "			[SUCCESS]\n");
				result.sprintf("			[SUCCESS]\n");
				ui.textBrowser->insertPlainText(result);
				ui.textBrowser->moveCursor(QTextCursor::End);
				QApplication::processEvents();
				Sleep(1000);
			}
			else if (recvcode > 0)//有回应
			{
				if (gettempspace[1] == 4)
				{
					short ACKnumber = -1;
					memcpy(&ACKnumber, gettempspace + 2, 2);
					ACKnumber = ntohs(ACKnumber);
					if (ACKnumber == blocknum)
					{
						if (blocknum)
						{
							fprintf(logf, "			[SUCCESS]\n");
							result.sprintf("			[SUCCESS]\n");
							ui.textBrowser->insertPlainText(result);
							ui.textBrowser->moveCursor(QTextCursor::End);
							QApplication::processEvents();
						}
						addr = server;
						if (datalen != 516 && blocknum != 0)//传完了
						{
							endtrans = clock();
							double time_use = ((endtrans - starttans) / 1.0) / (CLOCKS_PER_SEC);//结束计时，精度1ms
							print_now_time(logf);
							fprintf(logf, "Upload Finished!!!\nAverage transmission rate : %.2lf kb/s\n", (totallen_file / time_use) / 1024);
							result.sprintf("Upload Finished!!!\nAverage transmission rate : %.2lf kb/s\n", (totallen_file / time_use) / 1024);
							ui.textBrowser->insertPlainText(result);
							ui.textBrowser->moveCursor(QTextCursor::End);
							QApplication::processEvents();
							break;
						}
						blocknum++;
						sendp = makeDATAPack(blocknum, targetf, datalen);
						memcpy(sendtempspace, sendp, datalen);
						totallen_file += datalen - 4;
						resent = 0;
						if (sendp == NULL)
						{
							print_now_time(logf);
							fprintf(logf, "[ERROR]makeDATAPack error\n");
							result.sprintf("[ERROR]makeDATAPack error\n");
							ui.textBrowser->insertPlainText(result);
							ui.textBrowser->moveCursor(QTextCursor::End);
							QApplication::processEvents();
							errorswitch = 1;
							break;
						}
						int backcode = sendto(sock, sendtempspace, datalen, 0, (sockaddr*)&addr, sizeof(addr));
						sendtonum = 1;
						while (backcode != datalen)
						{
							if (sendtonum <= 5) //尝试5次，发不出去认为失败
							{
								backcode = sendto(sock, sendtempspace, datalen, 0, (sockaddr*)&addr, sizeof(addr));
								sendtonum++;
							}
							else
							{
								print_now_time(logf);
								fprintf(logf, "[ERROR]sent error,  blocknumber :%hd\n", blocknum);
								result.sprintf("[ERROR]sent error,  blocknumber :%hd\n", blocknum);
								ui.textBrowser->insertPlainText(result);
								ui.textBrowser->moveCursor(QTextCursor::End);
								QApplication::processEvents();
								errorswitch = 1;
								break;
							}
						}
						print_now_time(logf);
						fprintf(logf, "Uploading block%hd ......", blocknum);
						result.sprintf("Uploading block%hd ......", blocknum);
						ui.textBrowser->insertPlainText(result);
						ui.textBrowser->moveCursor(QTextCursor::End);
						QApplication::processEvents();
					}

				}
				else if (gettempspace[1] == 5)
				{
					short errorcode = -1;
					memcpy(&errorcode, gettempspace + 2, 2);
					errorcode = ntohs(errorcode);
					char* errormessage = (char*)malloc(1024);
					strcpy(errormessage, gettempspace + 4);
					if (errorcode >= 0 && errorcode <= 7)
					{
						print_now_time(logf);
						fprintf(logf, "[ERROR]getERRORPack : %s\n", errormessage);
						result.sprintf("[ERROR]getERRORPack : %s\n", errormessage);
						ui.textBrowser->insertPlainText(result);
						ui.textBrowser->moveCursor(QTextCursor::End);
						QApplication::processEvents();
					}
					else
					{
						print_now_time(logf);
						fprintf(logf, "[ERROR]getERRORPack : wrong error pack\n");
						result.sprintf("[ERROR]getERRORPack : wrong error pack\n");
						ui.textBrowser->insertPlainText(result);
						ui.textBrowser->moveCursor(QTextCursor::End);
						QApplication::processEvents();
					}
					errorswitch = 1;
					break;
				}
				else
				{
					result.sprintf("[ERROR]get wrong PACK\n");
					ui.textBrowser->insertPlainText(result);
					ui.textBrowser->moveCursor(QTextCursor::End);
					QApplication::processEvents();
					print_now_time(logf);
					fprintf(logf, "[ERROR]get wrong PACK\n");
					errorswitch = 1;
					break;
				}
			}
		}
		fclose(targetf);
	}
	fclose(logf);
	closesocket(sock);
}
