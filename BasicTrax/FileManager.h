#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

class FileManager
{
private:
  std::string file_name_;
public:
  void setFileName(const std::string& file_name);
  const std::string& getFileName() const;
  void writeToFile();
};

#endif // FILEMANAGER_H
