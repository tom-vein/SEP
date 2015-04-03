#include "FileManager.h"

void FileManager::setFileName(const std::string& file_name)
{
  file_name_ = file_name;
}

const std::string& FileManager::getFileName() const
{
  return file_name_;
}
