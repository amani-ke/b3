

#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sys/wait.h>
#include <signal.h>


using namespace std;

// Funktion zum Abfangen von Zombieprozessen
void handle_zombie(int sig) {
    wait(0);
    }


int main() {

    pid_t pid = fork();

    if (pid == -1) {
        cout << "Fehler beim Forken";
        return -1;
    }

    // Kindprozess
    if (pid == 0) {
        ofstream datei;
        datei.open("dateiVonKind.txt"); // Wählen Sie einen passenden Dateinamen
        datei << "Text.....";
        // Datei schließen
        datei.close();
    }

        // Elternprozess
    else
    {
        signal(SIGCHLD, handle_zombie); // Verwenden Sie SIGCHLD als Signal für den Kindprozess

        
        wait(NULL);

        string text;

        // Wenn eine Datei vom Kindprozess erzeugt wird, versuchen Sie die Datei mit dem
        //Elternprozess auszulesen
        ifstream datei("dateiVonKind.txt");

        // ist die Datei geöffnet?
        if (datei.is_open())
        {
            while ( getline(datei, text) )
            {
                // Datei ausgeben
                cout << text << endl;
            }
            datei.close();
        }

    }

    return 0;
}