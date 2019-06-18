/* Compilación:
 *
 * g++ -Wall -g Controller.cpp server/Server.cpp client/Client.cpp -o Controller
 *
 * ./Controller port
 */

#include <iostream>
using namespace std;

#include "server/Server.h"
#include "client/Client.h"


int main (int argc , char *argv[]) {
  // Instanciación.
  
  if (argc < 2) {
      cout << "./Controller port" << endl;
      return 0;
  }
  
  int port = atoi(argv[1]);
  Server server(port);
  
  return 0;
}
