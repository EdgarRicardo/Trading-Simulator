#include "menu.h"
#include "modeselection.h"

class Persona{
    QString m_nombre;
    int m_edad;
    double m_salario;
public:
    Persona(const QString &nombre, int edad, double salario): m_nombre(nombre), m_edad(edad), m_salario(salario){}
    Persona(){}
    QString getNom(){return m_nombre;}
    friend inline QDataStream &operator<<(QDataStream &ds, const Persona &p);
    friend inline QDataStream &operator>>(QDataStream &ds, Persona &p);
};



inline QDataStream &operator<<(QDataStream &ds, const Persona &p){
    return ds<<p.m_nombre<<p.m_edad<<p.m_salario;
}

inline QDataStream &operator>>(QDataStream &ds, Persona &p){
    return ds>>p.m_nombre>>p.m_edad>>p.m_salario;
}


using namespace std;

int main(int argc, char *argv[])
{

    QDataStream io;
    QFile fichierper;
    QDir pathf;
    Persona persona("Juan", 28, 4000);

    pathf.currentPath();
    pathf.cd("..");
    pathf.cd("OHLC");
    pathf.cd("Database");
    QString filename=pathf.path()+'/'+"datapersonas.txt";
    fichierper.setFileName(filename);
    fichierper.open(QIODevice::WriteOnly);
    io.setDevice(&fichierper);
    io.setVersion(QDataStream::Qt_4_8);
    io << 1;
    Persona persona4("Julion",30,5000);
    io << 2;
    io << 3;
    fichierper.flush();
    fichierper.close();
    //PARTIE DE LECTURE
    vector <int> r;
    r.push_back(1);
    Persona persona1, persona2, persona3;
    int a, b, c;
    fichierper.setFileName(filename);
    fichierper.open(QIODevice::ReadOnly);
    io.setDevice(&fichierper);
    io.setVersion(QDataStream::Qt_4_8);
    io >> a;
    io >> b;
    io >> c;
    fichierper.flush();
    fichierper.close();



    QApplication app(argc, argv);
    ModeSelection m;
    m.show();
    return app.exec();
}
