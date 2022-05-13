#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <sstream>
using namespace std;

class HashEntry {
private:
      int key;
      string value;
public:
      HashEntry(int key, string value) {
            this->key = key;
            this->value = value;
      }

      int getKey() {
            return key;
      }

      string getValue() {
            return value;
      }
};

const int TABLE_SIZE = 26;

class HashMap {
private:
      HashEntry **table;
public:
      HashMap() {
            table = new HashEntry*[TABLE_SIZE];
            //if table[i]->key = 1 --> has key; if table[i]->key = -1 --> tomb key
            for (int i = 0; i < TABLE_SIZE; i++)
                  table[i] = NULL;
      }

      int getKeyToBeInserted(string value) {
            int tmp = value[value.length() - 1] - 97;
            if (table[tmp] == NULL || table[tmp]->getKey() == -1){
                  return tmp;
            }
            
            while (table[tmp] != NULL && table[tmp]->getKey() != -1) {
                  //duplicate element found
                  if (table[tmp]->getKey() == 1 && table[tmp]->getValue() == value) {
                        return -1;
                  }
                  
                  tmp = (tmp + 1) % 26;
            }
            
            return tmp;
      }
      
      void add (string value) {
            value = value.substr(1);
            int key = getKeyToBeInserted(value);
            if (key != -1) {
                  table[key] = new HashEntry(1, value);
            }
      }
      
      void remove (string value) {
            value = value.substr(1);
            int key = value[value.length() - 1] - 97;
            int tmpKey = key;
            
            if (table[tmpKey] == NULL) {
                  return;
            }
            
            while (table[tmpKey] != NULL && table[tmpKey]->getValue() != value) {
                  tmpKey = (tmpKey + 1) % 26;
                  
                  if (tmpKey == key) {
                        return;
                  }
            }
            
            table[tmpKey] = new HashEntry(-1, "tombstone");
      }
      
      void show() {
            for (int i = 0; i < TABLE_SIZE; i++) {
                  if (table[i] != NULL && table[i]->getKey() == 1) {
                        cout << table[i]->getValue() << " ";
                  }
            }
            
            cout << endl;
      }

      ~HashMap() {
            for (int i = 0; i < TABLE_SIZE; i++)
                  if (table[i] != NULL)
                        delete table[i];
            delete[] table;
      }

};

int main ()
{
      string str;
      string sTmp;
      getline(cin, str);
      istringstream istr(str);
      HashMap h;
      
      while( !istr.eof() )
      {
            istr >> sTmp ; //get a word
            if (sTmp[0] == 'A') {
                  h.add(sTmp);
            } else if (sTmp[0] == 'D'){
                  h.remove(sTmp);
            }
      }

      h.show();
      
      return 0;
}
