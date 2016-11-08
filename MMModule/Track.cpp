#include "Track.h"

//Utilisation du namespace std pour standard
using namespace std;

Track::Track()
    : m_points(0)
{

}

Track::~Track()
{
    for (uint i=0 ; i < m_points.size(); ++i)
    {
        delete[] m_points[i];
    }
    m_points.clear(); //vector::clear() does not free memory allocated by the vector to store objects;
    // it calls destructors for the objects it holds.
}


void Track::readFromCSV(QString filename)
{
    // WARNING : This function doesn't check the correct extension (trust the user who puts a csv-format file)

    cout << "Le fichier " << filename.toStdString() << " va être lu."<< endl;


    // Declare file stream
    ifstream file(filename.toStdString().c_str()); // c_str() :http://stackoverflow.com/questions/32332/why-dont-the-stdfstream-classes-take-a-stdstring

    // Declaration
    string value; // Save the value of the line
    QString stringConverted;

    vector<int> correspondance(5); // Correpondance between the header and the parser :
    // correspondance :
    //  0 : # latitude column
    //  1 : # longitude column
    //  2 : # altitude column
    //  3 : # date column
    //  4 : # hour column
    for(uint i = 0; i < correspondance.size(); ++i)
    {
        correspondance[i]=-1;
    }


    // Read header
    if (file.good())
    {
        // Read the line
        getline(file, value);

        // Convert string to Qstring (easiest
        stringConverted = QString::fromStdString(value);

        // Split the line with separator
        QStringList text = stringConverted.split(",");
        //vector<string> text = split(value,',');

        // Parse header
        for(uint i = 0; i < text.size(); ++i)
        {
            cout << "Colonne " << text[i].toStdString() << endl;
            if (text[i].contains(QString::fromStdString("lati"),Qt::CaseInsensitive))
            {
                correspondance[0]=i;
                cout << "LATITUDE DETECTED at colonne : " << i << endl;
            }
            else if (text[i].contains(QString::fromStdString("longi"),Qt::CaseInsensitive))
            {
                correspondance[1]=i;
                cout << "LONGITUDE DETECTED at colonne : " << i << endl;
            }
            else if (text[i].contains(QString::fromStdString("alti"),Qt::CaseInsensitive))
            {
                correspondance[2]=i;
                cout << "ALTITUDE DETECTED at colonne : " << i << endl;
            }
            else if (text[i].contains(QString::fromStdString("date"),Qt::CaseInsensitive))
            {
                correspondance[3]=i;
                cout << "DATE DETECTED at colonne : " << i << endl;
            }
            else if (text[i].contains(QString::fromStdString("heure"),Qt::CaseInsensitive))
            {
                correspondance[4]=i;
                cout << "HEURE DETECTED at colonne : " << i << endl;
            }
            else
            {
                cout << "Colonne " << text[i].toStdString() << " non reconnue" << endl;
            }
        }
    }

    // Display the correspondance table
    cout << "BEGIN CORRESPONDANCE" << endl;
    for (int i = 0 ; i < correspondance.size(); ++i)
    {
        cout << correspondance[i] << endl;
    }
    cout << "END CORRESPONDANCE" << endl;


    // Parse the file
    float latitude(0), longitude(0), altitude(0);
    QDateTime timeStamp(QDateTime::currentDateTime());
    while ( file.good() )
    {
        // Reinitialize variables (default values)
        latitude=0;
        longitude=0;
        altitude=0;
        timeStamp=QDateTime::currentDateTime();
        vector<QString> specificDate(2);

        getline(file, value);
        // Convert string to Qstring (easiest
        stringConverted = QString::fromStdString(value);


        if (stringConverted.length() != 0) // Elimine les lignes vides
        {
            cout << "Read new point" << endl;
            QStringList text = stringConverted.split(",");
            for(uint i = 0; i < text.size(); ++i)
            {
                if (i == correspondance[0])
                {
                    // Traitement Latitude
                    // Read latitude from file
                    latitude = text[i].toFloat();

                    cout << "Latitude : " << latitude << " ";
                }
                else if (i == correspondance[1])
                {
                    // Traitement Longitude
                    // Read longitude from file
                    longitude = text[i].toFloat();

                    cout << "Longitude : " << longitude << " ";
                }
                else if (i == correspondance[2])
                {
                    // Traitement Altitude
                    // Read altitude from file
                    altitude = text[i].toFloat();

                    cout << "Altitude : " << altitude << " ";
                }
                else if (i == correspondance[3] && correspondance[4]==-1)
                {
                    // Traitement Date
                    // Read timeStamp from file
                    // If complete timestamp with date & time
                    if(text[i].length() == 19){
                        timeStamp = QDateTime::fromString(text[i],"yyyy-MM-dd hh:mm:ss");

                        cout << "Date time : " << timeStamp.toString().toStdString();
                    // If uncomplete timestamp with time & without date
                    }else if(text[i].length() == 8){
                        timeStamp = QDateTime::fromString(text[i],"hh:mm:ss");

                        cout << "Time : " << timeStamp.toString("hh:mm:ss").toStdString();
                    }
                }
                else if (correspondance[4]!=-1)
                {
                    if (i==correspondance[3])
                    {
                        // Traitement Date
                        specificDate[0]=text[i];
                    }
                    else if (i==correspondance[4])
                    {
                        // Traitement Hours
                        specificDate[1]=text[i];
                    }
                }
            }
            if (correspondance[4]!=-1) // if there are two columns for date and hours
            {
                timeStamp = QDateTime::fromString(specificDate[0]+specificDate[1],"yyyy/MM/ddhh:mm:ssa");
                cout << "Date time : " << timeStamp.toString().toStdString();
            }

            cout << endl;
            // Add the read point
            addPoint(latitude, longitude, altitude, timeStamp);
        }
        else{
            cout << "Ligne ignorée" << endl;
            continue;
        }
    }

    cout << "Le fichier " << filename.toStdString() << " a été lu."<< endl;
}



vector<PointTrack*> Track::getPoints()
{
    return m_points;
}


void Track::addPoint(float latitude, float longitude, float altitude, QDateTime timeStamp)
{
    m_points.push_back(new PointTrack(latitude, longitude, altitude, timeStamp));
}
