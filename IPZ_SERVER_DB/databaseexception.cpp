#include "databaseexception.h"

DataBaseException::DataBaseException(const QString& err)
{
    error = err;
}

QString DataBaseException::what()
{
    return error;
}

DataBaseException::~DataBaseException()
{

}
