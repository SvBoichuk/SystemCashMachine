#ifndef SAMELIB_H
#define SAMELIB_H

#include<QTableWidget>
#include<QThread>
#include<winsock2.h>
#include<QString>
#include<exception>
#include<QtCore/QCoreApplication>
#include<QDebug>
#include<QtSql>
#include<condition_variable>
#include<mutex>
static std::mutex mt1;
static std::mutex mt2;
static std::mutex mt3;
static std::mutex mt4;
static std::condition_variable var1;
static std::condition_variable var2;
static std::condition_variable var3;

#endif // SAMELIB_H
