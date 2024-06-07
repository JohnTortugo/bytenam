#include <iostream>
#include <zip.h>
#include <cstring>
#include "parser.hpp"
using namespace std;

int main(int argc, char* argv[]) {

  zip* archive = zip_open(argv[1], 0, nullptr);

  if (!archive) {
    cerr << "Error opening archive" << endl;
    return 1;
  }

  int num_files = zip_get_num_entries(archive, 0);

  for (int i=0; i<num_files; i++) {
    struct zip_stat fileInfo;

    if (zip_stat_index(archive, i, 0, &fileInfo) == 0) {
      if (strlen(fileInfo.name) > 6 && (strcmp(fileInfo.name + strlen(fileInfo.name) - 6, ".class") == 0)) {
        cout << "File " << i << " name: " << fileInfo.name << endl;

        zip_file_t* file = zip_fopen_index(archive, i, 0);

        if (file) {
          char* buf = new char[fileInfo.size];
          if (zip_fread(file, buf, fileInfo.size) == fileInfo.size) {
            BytecodeParser parser(buf);
            ClassFile* cls = parser.parse();
          }
          delete[] buf;
          zip_fclose(file);
        }
      }
    }
  }
  zip_close(archive);


  return 0;
}