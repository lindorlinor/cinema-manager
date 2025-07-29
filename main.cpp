#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   
    Catch::Session session;
   // Forziamo l'output in console, anche se tutto va bene
    const char* catch_argv[] = {
        "test-runner",        // nome fittizio del programma
        "--reporter", "console",
        "--success"           // <-- Mostra i test anche se passano!
    };

    int fake_argc = sizeof(catch_argv) / sizeof(catch_argv[0]);

    session.applyCommandLine(fake_argc, catch_argv);

    int result = session.run();

    if (result != 0)
        return result;

    MainWindow w;
    w.show();
    return a.exec();
}
