#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <QApplication>
#include "GUI/MainWindow.h"
#include "Media.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /* Catch::Session session;

    // Configura gli argomenti per Catch2
    const char *catch_argv[] = {
        argv[0], // usa il nome reale dell'eseguibile
        "--reporter", "console",
        "--success" // mostra i test anche se passano
    };
    int catch_argc = sizeof(catch_argv) / sizeof(catch_argv[0]);

    // Esegui i test
    int test_result = session.run(catch_argc, const_cast<char **>(catch_argv));

    if (test_result != 0)
    {
        return test_result; // esci se i test falliscono
    } */
    // Avvia l'applicazione Qt solo se i test passano

    MainWindow w;
    w.show();

    return a.exec();
}