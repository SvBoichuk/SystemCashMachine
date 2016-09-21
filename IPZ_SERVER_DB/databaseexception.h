#ifndef DATABASEEXCEPTION_H
#define DATABASEEXCEPTION_H
#include <exception>
#include <QString>

using std::exception;

class DataBaseException : public exception
{
private:
    QString error;
public:
    DataBaseException(const QString& err);
    QString what();
    ~DataBaseException();
};

#endif // DATABASEEXCEPTION_H
