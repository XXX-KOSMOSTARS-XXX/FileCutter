#ifndef FOR_LOGIC_H
#define FOR_LOGIC_H

#include <QObject>
#include <QVector>

class for_logic : public QObject
{
    Q_OBJECT
public:
    explicit for_logic(QObject *parent = nullptr);

signals:

public:

    void openFileA(QString file);           // функция открытия и записи в массив файла А
    void creationFileB();                   // функция создания файла Б

    QByteArray algorithm(QByteArray array); // функция преобразования массива из файла А

private:

    QByteArray Array = {};

    QString filePath;
    QString filePathNew;
    QString nameB;
    QString nameA;

    int position;
    int sizeA;
    int arraySize;
};

#endif // FOR_LOGIC_H
