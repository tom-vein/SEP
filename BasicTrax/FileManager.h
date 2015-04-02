#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

class FileManager
{
private:
  std::string file_name_;
public:
  FileManager(std::string file_name);
  void writeToFile();
};

#endif // FILEMANAGER_H
