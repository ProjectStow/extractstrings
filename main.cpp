#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QCommandLineParser>
#include <iostream>
#include <QString>
#include <QTranslator>


void rcFile(QString& inputFile, QString& headerFile, QString& translationFile, bool appendOutput, bool silentMode, bool verboseMode)

{
    QFile input(inputFile);
    QTextStream inputStream(&input);

    if (!input.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Cannot open input file." << std::endl;
        return;
    }


    QFile header(headerFile);
    QTextStream headerStream(&header);

    if (header.open(QIODevice::Append | QIODevice::ReadWrite))
    {
        if (!header.open(QIODevice::Append | QIODevice::ReadWrite))
        {
            std::cerr << "Cannot open or create header file." << std::endl;
        }
        input.close();
        return;
    }


    QFile translation(translationFile);
    QTextStream translationStream(&translation);

    if (translation.open(QIODevice::Append | QIODevice::ReadWrite))
    {
        if (!translation.open(QIODevice::Append | QIODevice::ReadWrite))
        {
        std::cerr << "Cannot open or create translation file." << std::endl;
        }
        input.close();
        header.close();
        return;
    }


    bool readStringTable;

    while (!inputStream.atEnd()) {
        QString line = inputStream.readLine().trimmed();

        if (line.startsWith("STRINGTABLE")) {

            readStringTable = true;
            continue;
        }

        if (readStringTable) {

            std::cout << "String Table: " << line;
        }

        if (line == "BEGIN") {
            while (!inputStream.atEnd()) {
                line = inputStream.readLine().trimmed();



                if (line == "END") {
                    if (verboseMode)
                        std::cout << "END" << std::endl;
                    break;
                }

            }
        }

        QString convertStringName(QString& inputFile);
        QString identifier = inputFile.toLower();

            identifier.replace('_', '-');

        if (identifier.startsWith("ids"))
            {
                identifier.replace(0, 3, "str_id");

                    else if (identifier.startsWith("id(x)"))
                    identifier.replace(0, 5, "str_id_x" )


                    else if (identifier.startsWith("afx"))
                    identifier.replace(0, 3, "str_id_o" )
                        };



    input.close();
    header.close();
    translation.close();

}
}

int main(int argc, char *argv[]) {

    QCoreApplication app(argc, argv);

    QCoreApplication::setApplicationName("extractstrings");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Extract Strings from an RC file");
    //parser.addHelpOption();
    //parser.addVersionOption();


    QCommandLineOption inputFileOption(QStringList() << "i" << "input", "Input file name", "filename");
    parser.addOption(inputFileOption);

    QCommandLineOption headerFileOption(QStringList() << "header" << "header", "Header file name", "headerfilename");
    parser.addOption(headerFileOption);

    QCommandLineOption translationFileOption(QStringList() << "t" << "translation", "Translation file name", "translationfilename");
    parser.addOption(translationFileOption);

    QCommandLineOption appendOutputOption(QStringList() << "a" << "append", "Append output to target files");
    parser.addOption(appendOutputOption);

    QCommandLineOption silentModeOption(QStringList() << "s" << "silent", "Run in silent mode");
    parser.addOption(silentModeOption);

    QCommandLineOption verboseModeOption(QStringList() << "verbose" << "verbose", "Run in verbose mode");
    parser.addOption(verboseModeOption);

    parser.process(app);

    QString inputFile = parser.value(inputFileOption);
    QString headerFile = parser.value(headerFileOption);
    QString translationFile = parser.value(translationFileOption);
    bool appendOutput = parser.isSet(appendOutputOption);
    bool silentMode = parser.isSet(silentModeOption);
    bool verboseMode = parser.isSet(verboseModeOption);

    if (inputFile.isEmpty()) {
        std::cerr << "Input file unspecified." << std::endl;
        return 1;
    }

    if (headerFile.isEmpty() && translationFile.isEmpty()) {
        if (!silentMode)
            std::cout << "No output file found." << std::endl;
    }

    rcFile(inputFile, headerFile, translationFile, appendOutput, silentMode, verboseMode);

    return 0;
}
