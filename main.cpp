#include <QCoreApplication>
#include <QByteArray>
#include <QDebug>
#include <QFile>


enum {HALT, MOV, ADD, SUB, PRINT, PUT, JMP, JEZ};
enum {ACC = 128, REG0 = 129, REG1=130};

int main(int argc, char *argv[])
{

    //работа с 16 ричными числами!!! сейчас преобразование тупое
    QCoreApplication a(argc, argv);
    QVector<quint16> ram(32767);
    ram.fill(0);


    quint8 pos = 0;

    bool halt = true;


    QFile file("prog.bin");
    file.open(QIODevice::ReadOnly);
    QByteArray tmp(file.readAll());

    for (int i = 0; i < tmp.size(); i = i + 2) {
        int ramPos = i == 0 ? 0 : i / 2;
        //qDebug()<< ramPos << QString::number((quint16)tmp[i] << 1 | (quint16) tmp[i+1]);
        //qDebug()<<  QString::number(() tmp[i+1]);
        ram[ramPos] = (quint8) tmp[i] << 1 |(quint8) tmp[i+1] ;
        //qDebug()<< ram[ramPos];
    }


    /*ram[0] = ADD;
    ram[1] = 100;
    ram[2] = 101;
    ram[3] = MOV;
    ram[4] = ACC;
    ram[5] = REG0;
    ram[6] = SUB;
    ram[7] = REG0;
    ram[8] = 102;
    ram[9] = PRINT;
    ram[10] = ACC;
    ram[11] = JMP;
    ram[12] = 13;
    ram[13] = JEZ;
    ram[14] = 0;
    ram[15] = 9;

    ram[100] = 5;
    ram[101] = 2;
    ram[102] = 3;*/

    while (halt) {
        //qDebug()<<pos<<ram[pos];
        switch (ram[pos]) {
        case HALT:
            halt = false;
            break;
        case MOV:

            ram[ram[pos + 2]] = ram[ram[pos + 1]];
            //qDebug()<<(int)ram[pos+2]<<(int)ram[pos + 1]<< ram[ram[pos + 1]];
            pos += 3;

            //exit(0);
            break;
        case ADD:
            //я балда... тут адрес а не значение
            ram[ACC] = ram[ram[pos + 1]] + ram[ram[pos + 2]];
            pos += 3;
            break;
        case SUB:
            //я балда... тут адрес а не значение
            ram[ACC] = ram[ram[pos + 1]] - ram[ram[pos + 2]];
            pos += 3;
            break;
        case PRINT:
            qDebug() << ram[ram[pos + 1]];
            pos += 2;
            break;
        case JMP:
            pos = ram[pos + 1];
            break;
        case JEZ:
            if (ram[ram[pos + 1]] == 0) {
                pos = ram[pos + 2];
                break;
            }
            pos += 3;
            break;
        default:
            break;
        }
    }
    return 0;
    //return a.exec();
}
