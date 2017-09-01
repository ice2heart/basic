#include <QCoreApplication>
#include <QByteArray>
#include <QDebug>


enum {HALT, MOV, ADD, SUB, PRINT, PUT};
enum {ACC = 128, REG0 = 129, REG1=130};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QVector<quint16> ram(32767);
    //ram.reserve(32767);
    ram.fill(0);

    quint8 pos = 0;

    bool halt = true;


    ram[0] = ADD;
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

    ram[100] = 5;
    ram[101] = 2;
    ram[102] = 3;

    while (halt) {
        //qDebug()<<pos;
        switch (ram[pos]) {
        case HALT:
            halt = false;
            break;
        case MOV:
            //qDebug()<<(int)ram[pos+2]<<(int)ram[pos + 1];
            ram[ram[pos + 2]] = ram[ram[pos + 1]];
            pos += 3;
            break;
        case ADD:
            //я балда... тут адрес а не значение
            ram[ACC] = ram[pos + 1] + ram[pos + 2];
            pos += 3;
            break;
        case SUB:
            //я балда... тут адрес а не значение
            ram[ACC] = ram[pos + 1] - ram[pos + 2];
            pos += 3;
            break;
        case PRINT:
            qDebug() << ram[ram[pos + 1]];
            pos += 2;
            break;
        default:
            break;
        }
    }
    return 0;
    //return a.exec();
}
