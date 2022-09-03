#include "for_logic.h"

#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <stdexcept>
#include <QDir>

using namespace std;

for_logic::for_logic(QObject *parent) :
    QObject(parent),
    position(0),
    sizeA(0),
    arraySize(0)
{
}

void for_logic::openFileA(QString filePath)
{
    QFile fileA (filePath);                     // создание файла А

    if (!fileA.open(QIODevice::ReadOnly))
    {
        throw QString("Ошибка открытия файла А");
    }

    sizeA = fileA.size();                       // размер файла А
    QFileInfo fileInfo (fileA.fileName());
    nameA = fileInfo.fileName();                // имя файла А
    nameB = ("result_" + nameA);                // имя файла Б
    QString filePathCopy = filePath;
    filePathNew = filePathCopy.remove(nameA);   // путь сохранения файла Б

    Array = fileA.readAll();
    fileA.close();
}

QByteArray for_logic::algorithm(QByteArray Array)
{
    for (int i = (Array.size() - 1); i >= 0; i--)   // читаем от конца до начала
    {
        if (Array.at(i) != 0x0)                     // ловим ненулевой элемент, 0x - для шестандцатеричной
        {
            position = i + 1; // запоминаем положение нулевого элемента после пойманного ненулевого
            break;
        }
    }

    if ((position)%2 == 0)
    {
        Array.remove(position, (Array.size() - position));
    }

    else
    {
        position++;
        Array.remove(position, (Array.size() - position));
    }

    arraySize = Array.size(); // чтобы сравнить, все ли записалось в файл
    return Array;
}

void for_logic::creationFileB()
{
    QString fullNameB = filePathNew + QDir::separator() + nameB;
    QFile fileB (filePathNew);
    fileB.setFileName(fullNameB);

    if (QFile::exists(fullNameB))
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(0, QStringLiteral("Внимание"), QStringLiteral("Файл с таким именем уже существует. Перезаписать?"),
                                      QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::No)
        {
            throw QString("Ошибка сохранения файла Б");
        }
    }

    if (!fileB.open(QIODevice::WriteOnly)) // файл Б не создался
    {
        throw QString("Ошибка открытия файла Б");
    }

    if(fileB.write(algorithm(Array)) && fileB.size() != arraySize) // при записи в файл Б произошла ошибка, записалось не все
    {
        fileB.close();
        throw QString("Ошибка сохранения файла Б");
    }

    fileB.close();

    QMessageBox::information(0, QStringLiteral("Информация"), QStringLiteral("Файл Б создан"));
}
