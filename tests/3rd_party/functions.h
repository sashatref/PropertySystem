#ifndef FUNCTIONS_H
#define FUNCTIONS_H

class QTranslator;
class QMainWindow;

#include <QFile>
#include <QVariant>
#include <QDir>
#include <QString>
#include <QVector>
#include <QDataStream>
#include <QBuffer>
#include <QVariantMap>
#include <QMetaEnum>


namespace SaveLoad
{
    void saveToByteArray(QByteArray &_data, const QVariantMap &_map);
    void loadFromByteArray(QByteArray &_data, QVariantMap &_map);

    bool loadLayout(const QDir &_path, QMainWindow *_mainWindow);
    bool saveLayout(const QDir &_path, QMainWindow *_mainWindow);

    QByteArray saveLayout(QMainWindow *_mainWindow);
    void loadLayout(const QByteArray &_data, QMainWindow *_mainWindow);

    template<typename T>
    bool loadSettings(const QString &_path, T &_settings)
    {
        QFile file(_path);

        if(file.open(QIODevice::ReadOnly))
        {
            QDataStream stream(&file);
            stream >> _settings;
            file.close();
            return true;
        }

        return false;
    }

    template<typename T>
    bool saveSettings(const QString &_path, const T &_settings)
    {
        QString mypath = _path;

        mypath.replace("\\", "/");
        if(mypath.contains("/"))
        {
            QString dir = mypath.left(mypath.lastIndexOf("/"));
            QDir().mkpath(dir);
        }

        QFile file(_path);

        if(file.open(QIODevice::WriteOnly))
        {
            QDataStream stream(&file);
            stream << _settings;
            file.close();
            return true;
        }

        return false;
    }
}

namespace Helper
{

    template <class From, class To>
    To* fastCast(From *obj)
    {
        static bool b = dynamic_cast<To*>(obj) != 0;
        if (b)
            return reinterpret_cast<To*>(obj);
        return 0;
    }

    template<class T>
    QVariantList toVariantList(const QList<T> &_list)
    {
        QVariantList resultList;
        for(int i = 0 ; i < _list.size(); i++)
        {
            resultList.append(QVariant::fromValue(_list[i]));
        }
        return resultList;
    }

    template<class T>
    QList<T> fromVariantList(const QVariantList &_list)
    {
        QList<T> resultList;
        for(int i = 0 ; i < _list.size(); i++)
        {
            resultList.append(_list[i].value<T>());
        }
        return resultList;
    }

    template<class T>
    QVector<QVariant> toVariantVector(const QVector<T> &_vec)
    {
        QVector<QVariant> resultVector;
        for(int i = 0 ; i < _vec.size(); i++)
        {
            resultVector.append(QVariant::fromValue(_vec[i]));
        }
        return resultVector;
    }

    template<class T>
    QVector<T> fromVariantVector(const QVector<QVariant> &_vec)
    {
        QVector<T> resultVector;
        for(int i = 0 ; i < _vec.size(); i++)
        {
            resultVector.append(_vec[i].value<T>());
        }
        return resultVector;
    }

    template<class T>
    QVariantMap toVariantMap(const QMap<QString, T> &_map)
    {
        QVariantMap resultMap;
        for(int i = 0 ; i < _map.keys().size(); i++)
        {
            resultMap.insert(_map.keys().at(i), QVariant::fromValue(_map[_map.keys().at(i)]));
        }
        return resultMap;
    }

    template<class T>
    QMap<QString, T> fromVariantMap(const QVariantMap &_map)
    {
        QMap<QString, T> resultMap;

        for(int i = 0 ; i < _map.keys().size(); i++)
        {
            resultMap.insert(_map.keys().at(i), _map[_map.keys().at(i)].value<T>());
        }
        return resultMap;
    }

    template<class T>
    void registerToQObjectConverter()
    {
        if(!QMetaType::hasRegisteredConverterFunction<T, QObject*>())
        {
            QMetaType::registerConverter<T, QObject*>([](const T &_value) -> QObject*
            {
                return const_cast<T*>(&_value);
            });
        }
    }


    template<class T>
    void registerToVectorConverter()
    {
        if(!QMetaType::hasRegisteredConverterFunction<QVariantList, QVector<T>>())
        {
            QMetaType::registerConverter<QVariantList, QVector<T>>([](const QVariantList &_list) -> QVector<T>
            {
                int _listSize =  _list.size();
                QVector<T> output;
                for(int i = 0 ; i < _listSize; i++)
                {
                    output.append(_list[i].value<T>());
                }
                return output;
            });
        }
    }
}

namespace Translate
{
/*!
     * \brief устанавливает все файлы переводов из указанного каталога с указаннм префиксом, напр. ru_
     * \param _path - путь для загрузки файлов
     * \param _prefix - префикс в название файлов, которые нужно загрузить
     * \param _translatorList - список трансляторов, для того чтоб удалить неиспользуемые
     * \param parent
     */
    void installTranslator(const QString &_path, const QString &_prefix, QList<QTranslator *> &_translatorList, QObject *parent);
    void installTranslator(const QStringList &_translationFiles, const QString &_prefix, QList<QTranslator *> &_translatroList, QObject *parent);
}


QString getCommandLine();


namespace Numerics
{
    double getRandomeDouble(int max = 20);
    int &fixValue(int &_value, int _min, int _max);
}


namespace Text
{
    /*!
     * \brief unionList возвращает список значений которые есть в первом и втором списках
     * \param _list1
     * \param _list2
     * \return
     */
    QStringList unionList(const QStringList &_list1, const QStringList &_list2, Qt::CaseSensitivity _sensivity);

    QVariantMap parseJson(const QByteArray &_jsonData);
    QByteArray writeToJson(const QVariantMap &_map);

    QString enumToString(int _value,
                         const QMetaEnum &_metaEnum,
                         const QMap<QString, QString> &_namesMap = QMap<QString, QString>());

    QString enumToString(int _value,
                         const QMetaObject *_mo,
                         const QString &_enumName,
                         const QMap<QString, QString> &_namesMap = QMap<QString, QString>());

    QStringList flagsToString(int _value,
                         const QMetaEnum &_metaEnum,
                         const QMap<QString, QString> &_namesMap = QMap<QString, QString>());

    int idFromString(const QString &_valueToParse);

    QString getDateFormatString();
    QString getDateTimeFormatString();

    QString getTextWithSymbolAround(const QString &_text, int _totalLenght, const QString &_symbol);
    QString &addChars(QString &_text, const QString &_char, int _lenght);

    typedef enum {
        de1, de4, de10, deMAXSIZE
    }DigitEnding;

    QString getRandomString(int _minLenght = 8, int _maxLenght = 12);
    QDate getRandomDate();
    QTime getRandomTime();
    QDateTime getRandomeDateTime();

    bool writeToFile(const QString &_path, const QString &_text, bool _append = true, const QString &_codec = "UTF-8");
    QString readFromFile(const QString &_path, const QString &_codec = "UTF-8");

    QString textWithTimeStamp(const QString &_text);
    QString textWithDateTimeStamp(const QString &_text);


    DigitEnding GetDigitEnding(const int iValue); /* Определение склонения числа */
    QString getHourEnding(int _value);
    QString getMinuteEnding(int _value);
    QString getSecondEnding(int _value);

    /*!
     * \brief getTimeFormatted формирует текст указанного времени с склонениями: часов, минут, секунда
     * только для русского языка
     * \param _hour
     * \param _min
     * \param _sec
     * \param hideNullElements
     * \return
     */
    QString getTimeFormatted(int _hour, int _min, int _sec, bool hideNullElements = true);

    /*!
     * \brief getShortText вырезает из слова серидину и вставляет туда "...", чтоб слово стало указанной длины
     * \param _text
     * \param _size
     * \return
     */
    QString getShortText(const QString &_text, int _size);


    /*!
     * \brief getShortFilePath обрезает путь к файлу, чтоб он стал указанной длины.
     * Если строка меньше maxSize, будет возвращено без изменений.
     * Если строка не содержит пути, то будет вырезана середина слова и заменана на "..."
     * Если строка является путем, то будет заменена на "C:\...\folder1\folder2\file.name"
     * Указывая столько последних каталогов, сколько уместится в maxSize
     * Если строка является путем, но название файла больше чем maxSize, то будет заменена на
     * "C:\...\filen...end.txt"
     * \param fullPath
     * \param _maxSize
     * \return
     */
    QString getShortFilePath(const QString &fullPath, int _maxSize = 50);
}


namespace Files
{
    //методы zip/unzip стянуты с интернета и даже не протиестированны
    void zip(const QString &_filename , const QString &_zipfilename);
    void unZip(const QString &_zipfilename , const QString &_filename);

    /*!
     * \brief возвращает список свех файлов в указанном каталоге и подкаталогах, с заданным фильтром.
     * \param _path
     * \param _ext
     * \return
     */

    QStringList countDir(const QString &_path, const QStringList &_ext, bool *_stop = 0);


    /*!
     * \brief проверяет, существуют ли каталоги по заданному пути, если нет, то создает их
     * \param _filePath
     */
    void createDirForFile(const QString &_filePath);

    /*!
     * \brief calcHash считает хэш для массива байтов
     * \param _bData
     * \return
     */
    QString calcHash(const QByteArray &_bData);

    /*!
     * \brief calcHash считает хэш _firstBytes первых байтов файла _filePath
     * \param _filePath
     * \param _firstBytes
     * \return
     */
    QString calcHash(const QDir &_filePath, int _firstBytes = -1);
}

#endif //FUNCTIONS_H
